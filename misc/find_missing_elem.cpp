#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// Given a sorted array of size n-1, containing unique numbers from 1 to n,
// with 1 missing element, find that missing element
int findMissingElem(const vector<int> &array) {
  // do a binary search to find it
  int lo = 0, hi = array.size() - 1;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (array[mid] > mid) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  return lo;
}

int main() {
  static const int num_elem = 10000;
  for (int rep = 0; rep < 1000; ++rep) {
    // prepare the vector
    vector<int> array;
    // generate a random element, remove it
    int missing = rand() % num_elem;
    for (int i = 0; i < missing; ++i) {
      array.push_back(i);
    }
    for (int i = missing + 1; i < num_elem; ++i) {
      array.push_back(i);
    }

    // check if the item we found is the missing one
    assert(findMissingElem(array) == missing);
  }
}
