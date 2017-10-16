#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

vector<float> roundNumber(vector<float> ary) {
  int sum = 0;
  int low_sum = 0;
  float tmp = 0.0;
  vector<pair<float, int>> diff;
  vector<float> ret;
  for (int i = 0; i < ary.size(); ++i) {
    tmp += ary[i];
    low_sum += floor(ary[i]);
    ret.push_back(floor(ary[i]));
    diff.push_back(make_pair(ary[i] - floor(ary[i]), i));
  }
  sum = round(tmp);
  int rem = sum - low_sum;

  // greedy algorithm
  sort(diff.begin(), diff.end());
  for (int i = 0; i < rem; ++i) {
    int idx = diff[i].second;
    ret[idx]++;
  }
  return ret;
}

int main() {
  {
    vector<float> data{0.02, 0.03, 0.05, 0.06, 0.07, 0.08,
                       0.09, 0.1,  0.11, 0.12, 0.13, 0.14};
    auto ret = roundNumber(data);
    for (auto n : ret) {
      cout << n << ", ";
    }
    cout << endl;
    cout << "Total : " << accumulate(ret.begin(), ret.end(), 0.0) << "("
         << round(accumulate(data.begin(), data.end(), 0.0)) << ")" << endl;
  }
  {
    vector<float> data{0.1, 0.3, 0.4, 0.4, 0.8};
    auto ret = roundNumber(data);
    for (auto n : ret) {
      cout << n << ", ";
    }
    cout << endl;
    cout << "Total : " << accumulate(ret.begin(), ret.end(), 0.0) << "("
         << round(accumulate(data.begin(), data.end(), 0.0)) << ")" << endl;
  }
  {
    vector<float> data{0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    auto ret = roundNumber(data);
    for (auto n : ret) {
      cout << n << ", ";
    }
    cout << endl;
    cout << "Total : " << accumulate(ret.begin(), ret.end(), 0.0) << "("
         << round(accumulate(data.begin(), data.end(), 0.0)) << ")" << endl;
  }
  {
    vector<float> data{0.4, 0.4, 0.4, 0.4, 9.2, 9.2};
    auto ret = roundNumber(data);
    for (auto n : ret) {
      cout << n << ", ";
    }
    cout << endl;
    cout << "Total : " << accumulate(ret.begin(), ret.end(), 0.0) << "("
         << round(accumulate(data.begin(), data.end(), 0.0)) << ")" << endl;
  }
  {
    vector<float> data{0.5, 0.5, 11};
    auto ret = roundNumber(data);
    for (auto n : ret) {
      cout << n << ", ";
    }
    cout << endl;
    cout << "Total : " << accumulate(ret.begin(), ret.end(), 0.0) << "("
         << round(accumulate(data.begin(), data.end(), 0.0)) << ")" << endl;
  }
}
