#include <cstdint>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class KVStore {
public:
  typedef int Snapshot;

public:
  KVStore() {
    cur_snap_ = -1;
    timestamp_ = 0;
  }
  ~KVStore() {}

public:
  string Get(string key, Snapshot snap) {
    if (data_.find(key) == data_.end()) {
      // return empty string if key is not found
      return string();
    }
    int ts_bound = snap_tbl_[snap];
    // it is the current snap so we just search for the largest ts
    if (ts_bound == -1) {
      ts_bound = INT_MAX;
    }
    // find the value with timestamp < ts_bound
    auto it = data_[key].lower_bound(ts_bound);
    if (it == data_[key].begin()) {
      // item is not present in this snapshot (e.g., inserted in a later
      // snapshot)
      return string();
    }

    --it;
    if (it->second.size() == 0) {
      // return empty string if it is deleted
      return string();
    } else {
      return it->second;
    }
  }
  void Put(string key, string value) {
    data_[key][timestamp_] = value;
    ++timestamp_;
  }
  void Del(string key) {
    data_[key][timestamp_] = DELETE_MARKER;
    ++timestamp_;
  }
  Snapshot takeSnapshot() {
    ++cur_snap_;
    if (cur_snap_ > 0) {
      snap_tbl_[cur_snap_ - 1] = timestamp_;
      ++timestamp_;
    }
    snap_tbl_[cur_snap_] = -1; // opening timestamp
    return cur_snap_;
  }
  void deleteSnapshot(Snapshot snap) {
    snap_tbl_.erase(snap);
    // TODO: background cleaning job should be triggered to remove the invalid
    // value
  }

private:
  // use empty string to mark a key as deleted
  static const string DELETE_MARKER;

private:
  int cur_snap_;
  int timestamp_;
  map<string, map<int, string>> data_;
  map<Snapshot, int> snap_tbl_;
};

const string KVStore::DELETE_MARKER = "";

int main() {
  KVStore kvs;
  auto snap1 = kvs.takeSnapshot();
  kvs.Put("a", "av1");
  kvs.Put("b", "bv1");
  kvs.Put("c", "cv1");

  auto snap2 = kvs.takeSnapshot();
  kvs.Del("b");
  kvs.Put("a", "av2");

  auto snap3 = kvs.takeSnapshot();
  kvs.Put("c", "cv2");

  cout << kvs.Get("c", snap1) << endl;
  cout << kvs.Get("c", snap2) << endl;
  cout << kvs.Get("c", snap3) << endl;
  cout << kvs.Get("b", snap2) << endl;
  kvs.deleteSnapshot(snap2);
  cout << kvs.Get("a", snap3) << endl;
  cout << kvs.Get("b", snap3) << endl;
  /*
    put (a, av1)
    put (b, bv1)
    put (c, cv1)
    snap2 = takeSnapshot()
    delete(b)
    put (a, av2)
    snap3 = takeSnapshot()
    put (c, cv2)

    get(c, snap1) => cv1
    get(c, snap2) => cv1
    get(c, snap3) => cv2
    get(b, snap2) => null
    deleteSnapshot(snap2)
    get(a, snap3) => av1
    get(b, snap3) => bv1

*/
}
