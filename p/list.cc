#include <iostream>
#include <mutex>

using namespace std;

// XXX: this is not tested!!!
class ConcurrentList {
public:
  struct ListNode {
    mutex mu_;
    int value_;
    ListNode *next_;

    ListNode() : mu_(), value_(), next_(NULL) {}
  };

public:
  // insert into the head of the list
  void Insert(int i) {
    // the dummy head is immutable so we do not need to worry about it being
    // NULL
    head.mu_.lock();
    head.next_->mu_.lock();

    ListNode *new_node = new ListNode();
    new_node->value_ = i;
    new_node->next_ = head.next_;
    head.next_ = new_node;

    head.next_->mu_.unlock();
    head.mu_.unlock();
  }

  // remove from the tail of the list
  int Remove() {
    ListNode *prev = &head;
    prev->mu_.lock();
    ListNode *curr = prev->next_;

    while (curr == NULL) {
      curr->mu_.lock();
      if (curr_->next == NULL) {
        // reach the end
        break;
      } else {
        prev->mu_.unlock();
        prev = curr;
        curr = curr->next_;
      }
    }

    if (curr == NULL) {
      // nothing is removed
      // unlock prev
      prev->unlock();
      return -1;
    } else {
      // remove curr
      int ret = curr->value_;
      prev->next_ == NULL;
      delete curr;

      // unlock prev and curr
      prev->unlock();
      curr->unlock();
      return ret;
    }
  }

  // get the size of the list
  void Size() {
    ListNode *prev = &head;
    prev->mu_.lock();
    ListNode *curr = prev->next_;
    int ret = 0;
    while (curr) {
      // invariants : prev is locked, and curr is not locked
      curr->mu_.lock();
      // now we can safely unlock prev and proceed
      prev->mu_.unlock();

      // update the counter
      ++ret;

      // update prev and curr
      prev = curr;
      curr = curr->next; // with the curr being locked
    }
    // XXX: note that if we break from the loop we still have prev locked, so we
    // must unlock before we return
    prev->mu_.unlock();
    return ret;
  }

private:
  ListNode head; // dummy head
};
