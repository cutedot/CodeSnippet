#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

const size_t W = 3;

class Puzzle {
public:
  Puzzle() : board_(W, vector<int>(W, 0)) {
    for (int i = 0; i < W; ++i) {
      for (int j = 0; j < W; ++j) {
        board_[i][j] = i * W + j;
      }
    }
    loc_ = make_pair(W - 1, W - 1);
  }
  Puzzle(string &s) {
    int pos = 0;
    for (int i = 0; i < W; ++i) {
      for (int j = 0; j < W; ++j) {
        board_[i][j] = stoi(s[pos]);
        ++pos;
        if (board_[i][j] == (W * W - 1)) {
          loc_ = make_pair(i, j);
        }
      }
    }
  }

private:
  vector<vector<int>> board_;
  pair<int, int> loc_; // location of bock W*W-1
};

int main() { unordered_set<string> q; }
