#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int freqNum(const vector<int> &nums) {
  for (int i = nums.size() / 4; i < nums.size(); i += nums.size() / 4) {
    int pivot = nums[i];
    int lower = i, upper = i;
    // search left
    int hi, lo;
    hi = i;
    lo = i - nums.size() / 4;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (nums[mid] < pivot) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    lower = hi;

    // search right
    hi = i + nums.size() / 4;
    lo = i;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (nums[mid] > pivot) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    upper = hi;

    if ((upper - lower) >= nums.size() / 4) {
      return pivot;
    }
  }
  return -1;
}

int main() {
  // prepare the data
  vector<int> nums;
  srand(time(NULL));
  int n = rand() % (1024);
  for (int i = 0; i < 3 * n; ++i) {
    nums.push_back(rand());
  }
  // push high freq number
  int f = abs(rand());
  for (int i = 0; i < n; ++i) {
    nums.push_back(f);
  }
  sort(nums.begin(), nums.end());

  // assert(freqNum(nums) == f);
  cout << f << " : " << freqNum(nums) << endl;
}
