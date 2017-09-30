#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool regexMatching(string s, string p) {
  // 2-d dp
  vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
  // initial state
  dp[0][0] = true; // empty string match empty pattern
  for (int j = 0; j < p.size(); ++j) {
    // dp[0][j + 1] : empty string match pattern p[0..j]
    if (p[j] == '*') {
      dp[0][j + 1] = dp[0][j - 1]; // a* match nothing
    }
  }
  // dp[i][0] = false for i in [0..s.size()+1] since empty pattern only matches
  // empty string
  //
  // try to match s and p
  for (int i = 0; i < s.size(); ++i) {
    for (int j = 0; j < p.size(); ++j) {
      // dp[i+1][j+1]
      if (s[i] == p[j] || p[j] == '.') {
        // match s[i] and p[j]
        dp[i + 1][j + 1] = dp[i][j];
      } else if (p[j] == '*') {
        if (s[i] == p[j - 1] || p[j - 1] == '.') {
          // three different cases: match nothing, match one, match many
          dp[i + 1][j + 1] = dp[i + 1][j - 1] || // match nothing
                             dp[i][j - 1] ||     // match one
                             dp[i][j + 1];       // match many
        } else {
          // the only possible case is match nothing
          dp[i + 1][j + 1] = dp[i + 1][j - 1];
        }
      }
    }
  }

  return dp[s.size()][p.size()];
}

int main() {
  {
    // TEST 1
    cout << "TEST 1" << endl;
    string s = "";
    string p = ".*a*c*";

    cout << regexMatching(s, p) << endl;
  }

  {
    // TEST 2
    cout << "TEST 2" << endl;
    string s = "aabbcc";
    string p = "a*b*c*";

    cout << regexMatching(s, p) << endl;
  }

  {
    // TEST 3
    cout << "TEST 2" << endl;
    string s = "aaabbcddde";
    string p = "a*bcd*e";

    cout << regexMatching(s, p) << endl;
  }
}
