#include <iostream>
#include <string>
#include <vector>

using namespace std;

string getPermutation(int n, int k) {
  int total = 1;
  string ret = "";
  vector<char> nums;
  k--;
  for (int i = 1; i <= n; ++i) {
    nums.push_back(i + '0');
  }
  for (int i = 1; i < n; ++i) {
    total = total * i;
  }
  for (int i = n; i > 1; --i) {
    int idx = k / total;
    ret += nums[idx];
    nums.erase(nums.begin() + idx);
    k = k % total;
    if (k == 0) {
      break;
    }
    total = total / (i - 1);
  }
  for (auto c : nums) {
    ret += c;
  }
  return ret;
}

int main() { cout << getPermutation(3, 4) << endl; }
