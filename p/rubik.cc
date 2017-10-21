#include <ctime>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

template <size_t W> class Board {
public:
  // initialize a random board
  Board() : pos_(0, 0) {
    for (int i = 0; i < W; ++i) {
      for (int j = 0; j < W; ++j) {
        board_[i][j] = i * W + j;
      }
    }
  }

  bool operator==(const Board<W> &that) const {
    for (int i = 0; i < W; ++i) {
      for (int j = 0; j < W; ++j) {
        if (board_[i][j] != that.board_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  long Hash() const {
    long ret = 0;
    const int kPrime = 37;
    for (int i = 0; i < W; ++i) {
      for (int j = 0; j < W; ++j) {
        ret = ret * kPrime + board_[i][j];
      }
    }
    return ret;
  }

  void Swap(int i, int j, int x, int y) { swap(board_[i][j], board_[x][y]); }

  bool isValid() {
    for (int i = 0; i < W; ++i) {
      for (int j = 0; j < W; ++j) {
        if (board_[i][j] != (i * W + j)) {
          return false;
        }
      }
    }
    return true;
  }

  string toString() {
    string ret;
    for (int i = 0; i < W; ++i) {
      for (int j = 0; j < W; ++j) {
        ret += to_string(board_[i][j]) + " ";
      }
    }
    return ret;
  }

private:
  int board_[W][W];
  pair<int, int> pos_;
};

const size_t kDim = 2;
typedef Board<kDim> Puzzle;

struct PuzzleHasher {
  long operator()(const Puzzle &b) const { return b.Hash(); }
};

int puzzleSolver(Puzzle &puz) {
  unordered_set<Puzzle, PuzzleHasher> visited;
  queue<pair<Puzzle, int>> q; // (board, steps)
  vector<pair<int, int>> dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  cout << 0 << " : " << puz.toString() << endl;
  q.push(make_pair(puz, 0));
  visited.insert(puz);

  while (!q.empty()) {
    Puzzle p = q.front().first;
    int step = q.front().second;
    q.pop();

    // cout << step << endl;
    // check if this is a valid board
    if (p.isValid()) {
      return step;
    }

    // keep moving
    for (int i = 0; i < kDim; ++i) {
      for (int j = 0; j < kDim; ++j) {
        // try swap with its four neighbors
        for (auto d : dirs) {
          int x = i + d.first;
          int y = j + d.second;

          if (x < 0 || x >= kDim || y < 0 || y >= kDim) {
            continue;
          }

          // cout << x << " " << y << endl;
          // swap (i, j) <-> (x, y)
          p.Swap(i, j, x, y);
          if (visited.find(p) == visited.end()) {
            // a new board, enqueue
            cout << step + 1 << " : " << p.toString() << endl;
            q.push(make_pair(p, step + 1));
            visited.insert(p);
          }
          p.Swap(x, y, i, j);
        }
      }
    }
  }
  return -1;
}

int main() {
  Puzzle p;
  p.Swap(0, 0, 0, 1);
  p.Swap(0, 1, 1, 1);
  cout << puzzleSolver(p) << endl;
}
