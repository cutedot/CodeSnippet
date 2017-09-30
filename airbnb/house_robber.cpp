#include <iostream>
#include <vector>

using namespace std;

// Airbnb version of House Robber. The difference is that we need to return the
// sequence of houses to rob.

vector<int> houseRobber(vector<int> houses) {
  vector<int> dp(houses.size(), 0);
  vector<int> ret;

  // dp[i] = max(dp[i-1], dp[i-2] + houses[i])
  dp[0] = houses[0];
  dp[1] = max(houses[0], houses[1]);

  for (int i = 2; i < houses.size(); ++i) {
    dp[i] = max(dp[i - 1], dp[i - 2] + houses[i]);
  }
  cout << "Max Profit : " << dp[houses.size() - 1] << endl;
  // reverse scan the array to find out the sequence
  // XXX: it is a bit tricky here: when wo traverse back, if we are at the first
  // item, we just add it, not need to check its predcessor (and it does not
  // have one)
  int i = houses.size() - 1;
  while (i >= 0) {
    if (i == 0 || dp[i] != dp[i - 1]) {
      // hosue i is robbed and house i-1 is not robbed
      ret.push_back(i);
      i = i - 2;
    } else {
      // house i is not robbed
      i = i - 1;
    }
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

void printSeq(vector<int> &sequence, vector<int> &houses) {
  int profit = 0;
  cout << "Rob Houses : ";
  for (auto i : sequence) {
    cout << i << " ";
    profit += houses[i];
  }
  cout << endl;
  cout << "Max Profit : " << profit << endl;
}

int main() {
  {
    // TEST1
    cout << "TEST 1" << endl;
    vector<int> houses{1, 1, 3, 6, 7, 10, 7, 1, 8, 5, 9, 1, 4, 4, 3};
    auto res = houseRobber(houses);
    printSeq(res, houses);
  }
  {
    // TEST2
    cout << "TEST 2" << endl;
    vector<int> houses{114, 117, 207, 117, 235, 82,  90,  67,  143, 146,
                       53,  108, 200, 91,  80,  223, 58,  170, 110, 236,
                       81,  90,  222, 160, 165, 195, 187, 199, 114, 235,
                       197, 187, 69,  129, 64,  214, 228, 78,  188, 67,
                       205, 94,  205, 169, 241, 202, 144, 240};
    auto res = houseRobber(houses);
    printSeq(res, houses);
  }
}
