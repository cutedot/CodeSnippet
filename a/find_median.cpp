#include <iostream>
#include <vector>

using namespace std;

int count(vector<int> &nums, int target) {
  // count the number of elements that are smaller than the target in the array
  // nums
  int ret = 0;
  for (auto i : nums) {
    if (i < target) {
      ++ret;
    }
  }
  return ret;
}

// return the smallest item that's greater than target
int upper_bound(vector<int> &nums, int target) {
  int ret = INT_MAX;
  for (auto i : nums) {
    if (i > target && i < ret) {
      ret = i;
    }
  }
  return ret;
}
// return the largest item that's no greater than target
int lower_bound(vector<int> &nums, int target) {
  int ret = INT_MIN;
  for (auto i : nums) {
    if (i < target && i > ret) {
      ret = i;
    }
  }
  return ret;
}
int findNth(vector<int> &nums, int n) {
  int lo = INT_MIN, hi = INT_MAX;
  // invariants : count(hi) > n/2
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    int cnt = count(nums, mid);
    if (cnt <= n) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }
  cout << "findNth : " << lo << ": " << hi << endl;
  return lower_bound(nums, lo);
}

int findMedian(vector<int> &nums) {
  int n = nums.size();
  if (n % 2) {
    return findNth(nums, n / 2);
  } else {
    /*cout << "DBG: "
         << " " << n / 2 << endl;
    cout << "DBG: " << findNth(nums, n / 2) << " " << findNth(nums, n / 2 + 1)
         << endl;
         */
    return (findNth(nums, n / 2) + findNth(nums, n / 2 + 1)) / 2;
  }
}

int main() {
  {
    // TEST 1
    cout << "TEST 1" << endl;
    vector<int> nums{1, 4, 23, 4321, 5231231};
    cout << findMedian(nums) << endl;
  }
  {
    // TEST 2: broken tests with duplicate items
    cout << "TEST 2" << endl;
    // vector<int> nums{1, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 44, 55, 66};
    // cout << findMedian(nums) << endl;
    cout << "BROKEN" << endl;
  }
  {
    // TEST 3
    cout << "TEST 2" << endl;
    vector<int> nums{1, 11, 111, 11111, 111111, 11111111};
    cout << findMedian(nums) << endl;
  }
}
