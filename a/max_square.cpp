#include <iostream>
#include <vector>

using namespace std;

int maxSquare(vector<vector<int>> &matrix) {
  // dp
  if (matrix.size() == 0) {
    return 0;
  }
  int max_square = 0;
  vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 0));

  // initial state
  if (matrix[0][0] == 1) {
    dp[0][0] = 1;
    max_square = max(max_square, dp[0][0]);
  }
  for (int i = 1; i < matrix.size(); ++i) {
    dp[i][0] = matrix[i][0];
    max_square = max(max_square, dp[i][0]);
  }
  for (int j = 1; j < matrix[0].size(); ++j) {
    dp[0][j] = matrix[0][j];
    max_square = max(max_square, dp[0][j]);
  }

  // dp
  for (int i = 1; i < matrix.size(); ++i) {
    for (int j = 1; j < matrix.size(); ++j) {
      // dp[i][j]
      if (matrix[i][j] == 1) {
        dp[i][j] = min(min(dp[i - 1][j - 1], dp[i][j - 1]), dp[i - 1][j]) + 1;
      }

      max_square = max(max_square, dp[i][j]);
    }
  }

  return max_square * max_square;
}

int main() {
  {
    // TEST 1
    cout << "TEST 1" << endl;
    vector<vector<int>> mat{
        {1, 0, 1, 0, 0}, {1, 0, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 1, 0}};

    cout << maxSquare(mat) << endl;
  }
}
