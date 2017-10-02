#include <iostream>
#include <vector>

using namespace std;

float absv(float v) { return v < 0.0 ? -v : v; }

void backtrack(vector<double> &prices, double target, int idx,
               vector<double> &cur, vector<vector<double>> &ret) {
  // it is very important that for double type, == should not be used when
  // comparing two items
  // XXX: another way to handle the comparison of floating point number is to
  // convert them into integer given the smallest unit is cents
  if (absv(target) < 0.0001) {
    ret.push_back(cur);
    return;
  } else if (target < 0.0) {
    return;
  }

  for (int i = idx; i < prices.size(); ++i) {
    cur.push_back(prices[i]);
    backtrack(prices, target - prices[i], i, cur, ret);
    cur.pop_back();
  }
}

void printResult(vector<vector<double>> res) {
  for (auto r : res) {
    cout << "[ ";
    for (auto p : r) {
      cout << p << " ";
    }
    cout << " ]" << endl;
  }
}

vector<vector<double>> menuCombSum(vector<double> &prices, double cash) {
  vector<vector<double>> ret;
  vector<double> cur;

  backtrack(prices, cash, 0, cur, ret);

  return ret;
}

int main() {

  {
    // TEST 1
    vector<double> prices{1.01, 2.12, 3.44, 5.32, 1.12};
    double cash = 6.57;
    vector<vector<double>> res = menuCombSum(prices, cash);
    printResult(res);
  }
}
