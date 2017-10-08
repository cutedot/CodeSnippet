#include <cassert>
#include <iostream>
#include <unordered_map>
using namespace std;

//
// An impl of LRU cache.
//
class LRUCache {
public:
  struct LRUHandle {
    LRUHandle() : prev(NULL), next(NULL) {}
    int key;
    int value;
    LRUHandle *prev;
    LRUHandle *next;
  };

public:
  LRUCache(int capacity) {
    cap_ = capacity;
    lru_.prev = &lru_;
    lru_.next = &lru_;
    tbl_.clear();
  }

  int get(int key) {
    if (tbl_.find(key) == tbl_.end()) {
      return -1;
    }
    LRUHandle *hdl = tbl_[key];
    LRURemove(hdl);
    LRUInsert(hdl);
    return hdl->value;
  }

  void put(int key, int value) {
    LRUHandle *hdl;
    if (tbl_.find(key) != tbl_.end()) {
      // set
      hdl = tbl_[key];
      LRURemove(hdl);
    } else {
      // insert
      if (tbl_.size() >= cap_) {
        // evict
        hdl = lru_.prev;
        LRURemove(hdl);
        tbl_.erase(hdl->key);
      } else {
        hdl = new LRUHandle();
      }
    }
    hdl->key = key;
    hdl->value = value;

    LRUInsert(hdl);
    tbl_[key] = hdl;
  }

private:
  void LRUInsert(LRUHandle *e) {
    // mark e as the newest
    e->next = lru_.next;
    e->prev = &lru_;
    e->prev->next = e;
    e->next->prev = e;
  }
  void LRURemove(LRUHandle *e) {
    e->prev->next = e->next;
    e->next->prev = e->prev;
  }

private:
  // dummy head of the LRU list
  //  - lru_.next points to the newest
  //  - lru_.prev points to the oldest
  LRUHandle lru_;
  unordered_map<int, LRUHandle *> tbl_;
  int cap_;
};

int main() {
  {
    LRUCache lru(10);
    for (int i = 0; i < 10; ++i) {
      lru.put(i, i);
    }

    for (int i = 0; i < 10; ++i) {
      int v = lru.get(i);
      assert(v == i);
    }

    lru.put(11, 11);
    int v = lru.get(0);
    assert(v == -1);
  }
}
