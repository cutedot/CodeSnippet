#include "nested_array.h"
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class TwoDimIterator {
public:
  TwoDimIterator(vector<vector<int>> &data) : data_(data), x_(0), y_(0) {}

  int next() {
    int ret = data_[x_][y_];
    ++y_;
    return ret;
  }

  bool hasNext() {
    while (x_ < data_.size() && y_ >= data_[x_].size()) {
      ++x_;
      y_ = 0;
    }
    // cout << x_ << " " << y_ << endl;
    return x_ < data_.size();
  }

  void remove() {
    // remove data_[x_][y_-1]
    auto it = data_[x_].begin();
    data_[x_].erase(it + y_ - 1);
  }

private:
  vector<vector<int>> &data_;
  int x_; // outer index
  int y_; // inner index
};

int main() {
  {
    // TEST 1
    cout << "TEST 1" << endl;
    vector<vector<int>> data{{1, 2}, {3}, {}, {4, 5, 6, 7}, {8}};
    {
      TwoDimIterator it(data);
      while (it.hasNext()) {
        int item = it.next();
        if (item == 3 || item == 6) {
          it.remove();
        }
      }
    }

    TwoDimIterator it(data);
    while (it.hasNext()) {
      cout << it.next() << " ";
    }

    cout << endl;
  }
}
