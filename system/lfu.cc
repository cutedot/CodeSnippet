#include <cassert>
#include <iostream>
#include <unordered_map>

using namespace std;

class LFUCache {
public:
  struct LFUHandle {
    int key;
    int value;
    int freq;
    LFUHandle *prev;
    LFUHandle *next;
  };

public:
  LFUCache(int capacity) {
    cap_ = capacity;
    lfu_.prev = &lfu_;
    lfu_.next = &lfu_;
  }

  int get(int key) {
    if (tbl_.find(key) == tbl_.end()) {
      return -1;
    }
    LFUHandle *hdl = tbl_[key];
    hdl->freq++;
    // move the item
    LFUHandle *p = hdl->prev;
    LFURemove(hdl);
    while (p != &lfu_ && p->freq <= hdl->freq) {
      p = p->prev;
    }
    LFUInsertAfter(hdl, p);
    return hdl->value;
  }

  void put(int key, int value) {
    LFUHandle *hdl;
    if (tbl_.size() >= cap_) {
      // cout << "evict " << lfu_.prev->key << endl;
      hdl = lfu_.prev;
      tbl_.erase(hdl->key);
      LFURemove(hdl);
    } else {
      hdl = new LFUHandle();
    }
    tbl_[key] = hdl;
    hdl->key = key;
    hdl->value = value;
    hdl->freq = 1;
    LFUHandle *p = lfu_.prev;
    while (p != &lfu_ && p->freq <= hdl->freq) {
      p = p->prev;
    }
    LFUInsertAfter(hdl, p);
  }

private:
  void LFURemove(LFUHandle *e) {
    e->prev->next = e->next;
    e->next->prev = e->prev;
  }

  // insert e after l
  void LFUInsertAfter(LFUHandle *e, LFUHandle *l) {
    e->prev = l;
    e->next = l->next;
    e->prev->next = e;
    e->next->prev = e;
  }

private:
  // dummy head of lfu list
  //  - lfu.next points to the most frequently accessed item
  //  - lfu.prev points to the least frequently accessed item
  LFUHandle lfu_;
  int cap_;
  unordered_map<int, LFUHandle *> tbl_;
};

int main() {
  {
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    assert(lfu.get(1) == 1);
    lfu.put(3, 3);
    assert(lfu.get(2) == -1);
  }
  {
    LFUCache lfu(3);
    for (int i = 1; i <= 4; ++i) {
      lfu.put(i, i);
    }
    for (int i = 4; i > 0; --i) {
      cout << lfu.get(i) << endl;
    }
    lfu.put(5, 5);
    for (int i = 1; i <= 5; ++i) {
      cout << lfu.get(i) << endl;
      ;
    }
  }
}
