#include <cassert>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>

using namespace std;

/**
 * A filter interface
 **/
class Filter {
public: // public interface
  // add an item to the filter
  virtual void Add(int item) = 0;
  // check if we have the item in filter
  virtual bool Contain(int item) = 0;
  // number of items in the filter
  virtual int Size() const = 0;
  // size in bytes of the filter
  virtual int SizeInBytes() = 0;
};

/**
 * Bloom Filter implementation
 **/
class BloomFilter : public Filter {
public:
  // initial provisioning for nkeys
  BloomFilter(int bits_per_key, int nkeys) {
    // nprob_ = bits_per_key * 0.69;
    nprob_ = bits_per_key * 0.69;
    nbits_ = nprob_ * nkeys;
    nbytes_ = (nbits_ + 7) / 8;
    nkeys_ = 0;
    array_ = new uint8_t[nbytes_];
  }
  ~BloomFilter() { delete array_; }

public:
  virtual void Add(int item) {
    size_t h1 = BloomHash(item);
    size_t h2 = (h1 >> 17) | (h1 << 15);
    for (int i = 0; i < nprob_; ++i) {
      size_t pos = h1 % nbits_;
      array_[pos / 8] |= (1 << (pos % 8));
      h1 += h2;
    }
    ++nkeys_;
  }

  virtual bool Contain(int item) {
    size_t h1 = BloomHash(item);
    size_t h2 = (h1 >> 17) | (h1 << 15);
    for (int i = 0; i < nprob_; ++i) {
      size_t pos = h1 % nbits_;
      if ((array_[pos / 8] & (1 << (pos % 8))) == 0) {
        return false;
      }
      h1 += h2;
    }
    return true;
  }

  virtual int Size() const { return nkeys_; }

  virtual int SizeInBytes() { return nbytes_; }

private:
  size_t BloomHash(int item) { return hash<int>{}(item); }

private:
  uint8_t *array_;
  int nprob_;
  int nbits_;
  int nbytes_;
  int nkeys_;
};

int main() {
  Filter *filter = new BloomFilter(10, 1000);
  {
    // TEST 1
    cout << "TEST 1 : Basic Functionality" << endl;
    srand(time(NULL));
    for (int i = 0; i < 1000; ++i) {
      int key = rand();
      filter->Add(key);
      assert(filter->Contain(key));
    }

    cout << "Number of keys : " << filter->Size() << endl;
    cout << "Number of bytes used by BloomFilter : " << filter->SizeInBytes()
         << endl;
  }
  {
    // TEST 2
    cout << "TEST 2: Measure false-positive rate" << endl;
    const int nreps = 1000000;
    int fps = 0;
    for (int i = 0; i < nreps; ++i) {
      int k = rand();
      // find a random key that's not added to the filter
      while (k >= 0 && k < 1000) {
        k = rand();
      }
      if (filter->Contain(k)) {
        fps++;
      }
    }

    cout << "False-Positive Rate : " << 1.0 * fps / nreps << endl;
  }
}
