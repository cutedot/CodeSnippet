#include <boost/filesystem.hpp>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
//
// An implementation of mini file system that supports basic functionality
// NOTE: this is not POSIX compatible
//
using namespace std;
namespace fs = boost::filesystem;

class FileSystem {
public: // file system essentials
  enum TYPE { FILE_TYPE = 0, DIR_TYPE = 1 };

  struct iNode {
  public:
    iNode(TYPE t, const string &n) {
      type_ = t;
      name_ = n;
    }
    ~iNode() {}

    bool is_dir() const { return type_ == DIR_TYPE; }
    string &get_name() { return name_; }

  private:
    // type of the node
    TYPE type_;
    // name of the file or directory
    string name_;
  };

  // TODO: the File and Directory object should be ref-counted.
  struct File : public iNode {
  public:
    File(const string &filename)
        : iNode(FILE_TYPE, filename), size_(0), data_(NULL) {}

    ~File() {
      if (data_) {
        free(data_);
      }
    }

  public: // read/write the file
    // To simplify the return value, Read() API return a boolean to indicate if
    // the read succeeds. Same for the Write() API.
    // Read n bytes data at offset in ths file
    bool Read(uint64_t offset, size_t n, char *buf) const {
      if (offset + n > size_) {
        return false; // out of bound
      }
      char *p = data_ + offset;
      memcpy(buf, p, n);
      return true;
    }

    // Write n bytes to the file at offset
    // XXX: this is a very very STUPID design since everytime we append to the
    // end of the file, we reallocate a new data buffer and copy everything
    // over. But this is just for a simple demo. A better block management
    // sybsystem can help with this situation and usually a must-have on block
    // devices.
    bool Write(uint64_t offset, size_t n, char *buf) {
      if (data_ == NULL || size_ < offset + n) {
        // first time write
        char *new_data = new char[offset + n];
        // copy existing data over
        memcpy(new_data, data_, size_);

        // update the size
        size_ = offset + n;

        if (data_) {
          delete data_;
        }
        data_ = new_data;
      }
      // write new data
      memcpy(data_ + offset, buf, n);
      return true;
    }

  private:
    int size_;   // current file size
    char *data_; // content of the file
  };

  struct Dir : public iNode {
  public: // C-tor
    Dir(const string &dirname) : iNode(DIR_TYPE, dirname) {}
    ~Dir() {
      for (auto d : dir_tbl_) {
        if (d.second->is_dir()) {
          delete static_cast<Dir *>(d.second);
        } else {
          delete static_cast<File *>(d.second);
        }
      }
    }

  public:
    iNode *search(string name) {
      if (dir_tbl_.find(name) == dir_tbl_.end()) {
        return NULL;
      } else {
        return dir_tbl_[name];
      }
    }
    bool add(string name, iNode *item) {
      if (dir_tbl_.find(name) == dir_tbl_.end()) {
        cout << name << endl;
        dir_tbl_[name] = item;
        return true;
      } else {
        return false; // already exist
      }
    }
    // note that this del operation assumes all contents in the lower level are
    // taken care by the caller.
    bool del(string name) {
      if (dir_tbl_.find(name) == dir_tbl_.end()) {
        return false;
      } else {
        delete dir_tbl_[name];
        dir_tbl_.erase(name);
        return true;
      }
    }

  private:
    // directory table
    unordered_map<string, iNode *> dir_tbl_;
  };

private:
  // recursively destroy the file system
  //  - delete all files / directories
  void destroy(iNode *root) { delete static_cast<Dir *>(root_); }

  // navigate to a directory
  bool navigate(const string &dirname, iNode **leaf, iNode **parent_dir,
                bool create_if_missing) {
    fs::path dirpath(dirname);
    iNode *cur = root_;
    iNode *parent = NULL;
    for (auto f : dirpath) {
      if (f.string() == "/") {
        continue; // skip the leading '/'
      }
      iNode *p = NULL;
      if (cur->is_dir()) {
        p = static_cast<Dir *>(cur)->search(f.string());
      } else {
        return false;
      }
      if (p == NULL) {
        if (create_if_missing) {
          p = new Dir(f.string());
          static_cast<Dir *>(cur)->add(f.string(), p);
        } else {
          return false;
        }
      }
      parent = cur;
      cur = p;
    }
    *leaf = cur;
    *parent_dir = parent;
    return true;
  }

public:
  FileSystem() { root_ = new Dir("/"); }
  ~FileSystem() { this->destroy(root_); }

public: // public accessors
  // here to help with splitting the path string, I use the filesystem library.
  bool CreateDir(const string &dirname) {
    fs::path dirpath = dirname;
    iNode *cur = root_;
    iNode *parent = NULL;
    return navigate(dirname, &cur, &parent, true);
  }
  bool DeleteDir(const string &dirname) {
    fs::path dirpath = dirname;
    iNode *cur = root_;
    iNode *parent = NULL;
    bool st = navigate(dirpath.string(), &cur, &parent, false);
    if (st == false || !cur->is_dir()) {
      return false;
    }
    // delete the directory
    static_cast<Dir *>(parent)->del(cur->get_name());
    return true;
  }
  bool NewFile(const string &path) {
    fs::path filepath = path;
    fs::path dirpath = filepath.parent_path();
    fs::path filename = filepath.filename();

    iNode *dir;
    iNode *parent = NULL;
    bool st = navigate(dirpath.string(), &dir, &parent, true);

    if (st == true && dir->is_dir()) {
      File *fd = new File(filename.string());
      static_cast<Dir *>(dir)->add(filename.string(), fd);
      return true;
    } else {
      return false;
    }
  }
  bool DeleteFile(const string &path) {
    fs::path filepath = path;
    fs::path dirpath = filepath.parent_path();
    fs::path filename = filepath.filename();

    iNode *dir;
    iNode *parent = NULL;
    bool st = navigate(dirpath.string(), &dir, &parent, false);

    if (st == true && dir->is_dir()) {
      return static_cast<Dir *>(dir)->del(filename.string());
    } else {
      return false;
    }
  }
  File *OpenFile(const string &path) {
    iNode *f;
    iNode *parent = NULL;
    bool st = navigate(path, &f, &parent, false);
    if (st || f->is_dir()) {
      return NULL;
    }
    return static_cast<File *>(f);
  }

public:
  iNode *root_; // the root directory
};

int main() {
  {
    char input[128] = "1234567890ABCDEF";
    FileSystem fs;
    fs.CreateDir("/home/hluo/");
    fs.NewFile("/home/hluo/work");
    FileSystem::File *fd = fs.OpenFile("/home/hluo/work");
    assert(fd != NULL);
    fd->Write(0, 16, input);
    char rbuf[128] = {0};
    fd->Read(4, 8, rbuf);

    cout << rbuf << endl;
  }
}
