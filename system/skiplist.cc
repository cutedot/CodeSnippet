#include <cstring>
#include <iostream>

using namespace std;

// Assumption
//  - int key
//  - int value
//  - max level

class SkipList {
 public:
  static const size_t kMaxLevel = 10;

 private:
  struct Node {
    Node() { memset(this, 0, sizeof(Node)); }
    ~Node() {}

    void SetNext(int lvl, Node* x) { next[lvl] = x; }

    Node* GetNext(int lvl) { return next[lvl]; }

    int key;
    int value;
    Node* next[kMaxLevel];
  };

 public:
  SkipList() { head_ = new Node(); }
  ~SkipList() {}

  void Insert(const int key, const int value) {
    // find the location to insert
    Node* prev[kMaxLevel];
    Node* x = FindGreaterOrEqual(key, prev);
    if (x != NULL && x->key == key) {
      // update the value
      x->value = value;
    } else {
      // insert
      Node* new_node = new Node();
      new_node->key = key;
      new_node->value = value;

      // update pointers from buttom up
      for (int i = 0; i < kMaxLevel; ++i) {
        // link prev[i] and the new node
        if (prev[i]) {
          new_node->SetNext(i, prev[i]->GetNext(i));
          prev[i]->SetNext(i, new_node);
        }
      }
    }
  }

  bool Find(const int key, int* value) {
    Node* x = FindGreaterOrEqual(key, NULL);
    if (x != NULL && x->key == key) {
      // found it
      *value = x->value;
      return true;
    }
    return false;
  }

  bool Delete(const int key) {
    // find the item to remove
    Node* prev[kMaxLevel];
    Node* x = FindGreaterOrEqual(key, prev);

    if (x != NULL && x->key == key) {
      // x is the node to remove
      // unlink it from to to buttom
      for (int i = kMaxLevel - 1; i >= 0; --i) {
        prev[i]->SetNext(i, x->GetNext(i));
      }
      delete x;
      return true;
    } else {
      return false;
    }
  }

 public:
  Node* FindGreaterOrEqual(int key, Node** prev) {
    Node* x = head_;
    int level = kMaxLevel - 1;
    while (true) {
      Node* next = x->GetNext(level);
      if (next != NULL && next->key < key) {
        // keep going right
        x = next;
      } else {
        // going down
        if (prev != NULL) {
          prev[level] = x;
        }
        if (level == 0) {
          // can't go down
          // invariant : next key in the list is greater than or equal to key,
          // and current node x is smaller than key
          return next;
        } else {
          // going down
          --level;
        }
      }
    }
  }

 private:
  Node* head_;  // dummy head
};

int main() {
  SkipList sl;
  sl.Insert(1, 1);
  sl.Insert(3, 3);
  sl.Insert(2, 2);
  sl.Insert(0, 0);

  int v = -1;
  sl.Find(1, &v);
  cout << v << endl;

  sl.Find(2, &v);
  cout << v << endl;

  sl.Delete(1);
  cout << sl.Find(1, &v) << endl;
  cout << sl.Find(2, &v) << " " << v << endl;
}
