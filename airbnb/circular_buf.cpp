#include <iostream>
#include <vector>

using namespace std;

class CircularBuffer {
public:
  CircularBuffer(int capacity) {
    data_ = new int[capacity];
    memset(data_, 0, sizeof(int) * capacity);
    head_ = 0;
    len_ = 0;
    cap_ = capacity;
  }
  ~CircularBuffer() { delete data_; }

public: // public API
  void push(int item) {
    // insert item to the tail of the buffer
    if (len_ >= cap_) {
      return;
    }

    int idx = (head_ + len_) % cap_;
    data_[idx] = item;
    ++len_;
  }
  int pop() {
    // pop item from the head of the buffer
    if (len_ <= 0) {
      return -1;
    }
    int ret = data_[head_];
    head_ = (head_ + 1) % cap_;
    --len_;
    return ret;
  }
  int peek() { return data_[head_]; }

private:
  int cap_;
  int *data_;
  int head_;
  int len_;
};

// TODO: a concurrent single consumer single producer circular buffer
// implementation.

int main() {
  {
    // TEST1
    CircularBuffer circbuf(8);
    circbuf.push(1);
    circbuf.push(2);
    circbuf.push(5);
    cout << circbuf.pop() << endl;
    cout << circbuf.pop() << endl;
    cout << circbuf.pop() << endl;
    cout << circbuf.pop() << endl;
    for (int i = 0; i < 10; ++i) {
      circbuf.push(i);
    }
    for (int i = 0; i < 10; ++i) {
      cout << circbuf.peek() << endl;
      cout << circbuf.pop() << endl;
    }
  }
}
