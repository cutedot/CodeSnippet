#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <random>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

enum Dir { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
const vector<string> dir_name{"UP", "DOWN", "LEFT", "RIGHT"};

class Puzzle {
public:            // constants
  const int D = 3; // dimension
  const vector<Dir> dirs{UP, DOWN, LEFT, RIGHT};
  const vector<vector<int>> pos{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
  Puzzle() {
    vector<int> nums;
    for (int i = 0; i < D * D; ++i) {
      nums.push_back(i);
    }
    // use D*D-1 as the marker for empty slot
    shuffle(nums.begin(), nums.end(), std::default_random_engine(time(NULL)));

    for (int i = 0; i < D; ++i) {
      board.push_back(vector<int>());
      for (int j = 0; j < D; ++j) {
        board[i].push_back(nums[i * D + j]);
        if (board[i][j] == (D * D - 1)) {
          x = i;
          y = j;
        }
      }
    }
  }

  Puzzle(int steps) {
    // start from a valid board
    for (int i = 0; i < D; ++i) {
      board.push_back(vector<int>());
      for (int j = 0; j < D; ++j) {
        board[i].push_back(i * D + j);
      }
    }
    // shuffle the board
    // generate random moves
    srand(time(NULL));
    int i = 0;
    while (i < steps) {
      Dir m = dirs[rand() % 4];
      if (this->move(m)) {
        ++i;
      }
    }
  }

  Puzzle(const Puzzle &that) {
    board = that.board;
    x = that.x;
    y = that.y;
  }

  Puzzle(string &s) {
    for (int i = 0; i < D; ++i) {
      board.push_back(vector<int>());
      for (int j = 0; j < D; ++j) {
        board[i].push_back(s[i * D + j] - '0');
        if (board[i][j] == (D * D - 1)) {
          x = i;
          y = j;
        }
      }
    }
  }

public:
  Puzzle &operator=(const Puzzle &that) {
    board = that.board;
    x = that.x;
    y = that.y;
    return *this;
  }

public: // play the game
  // try to move the empty slot, return if the empty slot is moved
  bool move(Dir d) {
    int xx = x + pos[d][0];
    int yy = y + pos[d][1];

    if (xx < 0 || yy < 0 || xx >= D || yy >= D) {
      // invalid move
      return false;
    }
    // otherwise swap <x,y> and <xx, yy>
    swap(board[x][y], board[xx][yy]);
    x = xx;
    y = yy;
    return true;
  }

public: // utility
  void printBoard() {
    cout << "=== Board ===" << endl;
    for (auto r : board) {
      for (auto i : r) {
        cout << i << " ";
      }
      cout << endl;
    }
    cout << "=============" << endl;
  }

  string boardToString() {
    string ret = "";
    for (auto r : board) {
      for (auto i : r) {
        ret += to_string(i);
      }
    }
    return ret;
  }

  bool validBoard() {
    for (int i = 0; i < D; ++i) {
      for (int j = 0; j < D; ++j) {
        if (board[i][j] != i * D + j) {
          return false;
        }
      }
    }
    return true;
  }

public: // puzzle solver
  // BRUTE-FORCE BFS SOLVER : get things done in a stupid way
  // solve the puzzle by moving the board back to the original state
  // TODO: quite a few places to improve:
  //        - too many object copy (but seems inevitable?)
  //        - can it be done in-place?
  vector<Dir> naive_solve() {
    // use try BFS to solve this problem
    queue<Puzzle> q; // put the string representation in the queue
    unordered_map<string, vector<Dir>>
        tbl; // keep track of all visited puzzle board
    q.push(*this);
    vector<Dir> cur;
    tbl[this->boardToString()] = cur;

    while (!q.empty()) {
      Puzzle p(q.front());
      q.pop();
      // cout << "POP  : " << p.boardToString() << endl;

      cur = tbl[p.boardToString()]; // path to current state
      // check if it is valid
      if (p.validBoard()) {
        return cur;
      }
      // try to move for different directions
      for (int i = 0; i < 4; ++i) {
        Puzzle next(p);
        if (next.move(dirs[i])) {
          string new_board = next.boardToString();
          if (tbl.find(new_board) == tbl.end()) {
            vector<Dir> new_path(cur);
            new_path.push_back(dirs[i]);
            // a new board, add to lookup table
            tbl[new_board] = new_path;
            // enqueue this board
            q.push(next);
            // cout << "PUSH : " << next.boardToString() << endl;
          }
        }
      }
    }
    return vector<Dir>();
  }
  // TODO: fix this ...
  // A* solver
  // the heuristics is the sum of square diff of each slot in board
  int distance() {
    // return (D - 1 - x) * (D - 1 - x) + (D - 1 - y) * (D - 1 - y);
    int dist = 0;
    for (int i = 0; i < D; ++i) {
      for (int j = 0; j < D; ++j) {
        int diff = board[i][j] - (i * D + j);
        dist += diff * diff;
      }
    }
    return dist;
  }
  // comparator function
  struct cmp {
    bool operator()(Puzzle &lhs, Puzzle &rhs) {
      return lhs.distance() > rhs.distance();
    }
  };
  // A* seach, using a priority queue instead of queue.
  // Every time pops up the item that has smaller distance from a valid board.
  vector<Dir> astar_solve() {
    // use try BFS to solve this problem
    priority_queue<Puzzle, vector<Puzzle>, cmp>
        q; // put the string representation in the queue
    unordered_map<string, vector<Dir>>
        tbl; // keep track of all visited puzzle board
    q.push(*this);
    vector<Dir> cur;
    tbl[this->boardToString()] = cur;

    while (!q.empty()) {
      Puzzle p(q.top());
      q.pop();
      // cout << "POP  : " << p.boardToString() << endl;

      cur = tbl[p.boardToString()]; // path to current state
      // check if it is valid
      if (p.validBoard()) {
        return cur;
      }
      // try to move for different directions
      for (int i = 0; i < 4; ++i) {
        Puzzle next(p);
        if (next.move(dirs[i])) {
          string new_board = next.boardToString();
          if (tbl.find(new_board) == tbl.end()) {
            vector<Dir> new_path(cur);
            new_path.push_back(dirs[i]);
            // a new board, add to lookup table
            tbl[new_board] = new_path;
            // enqueue this board
            q.push(next);
            // cout << "PUSH : " << next.boardToString() << endl;
          }
        }
      }
    }
    return vector<Dir>();
  }

private: // data
  // board
  vector<vector<int>> board;
  // position of the empty slot
  int x;
  int y;
};

int main() {
  {
    Puzzle pz(rand() % 10000000);
    // Puzzle pz;
    pz.printBoard();

    auto t0 = chrono::high_resolution_clock::now();
    vector<Dir> res1 = pz.naive_solve();
    auto t1 = chrono::high_resolution_clock::now();

    auto t2 = chrono::high_resolution_clock::now();
    vector<Dir> res2 = pz.astar_solve();
    auto t3 = chrono::high_resolution_clock::now();

    cout << "Time measured : " << endl;
    cout << "Naive BFS : Lenght " << res1.size() << " in "
         << std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count()
         << " seconds" << endl;
    cout << "Astar BFS : Lenght " << res2.size() << " in "
         << std::chrono::duration_cast<std::chrono::seconds>(t3 - t2).count()
         << " seconds" << endl;

    for (auto d : res1) {
      assert(pz.move(d));
    }
    if (pz.validBoard()) {
      cout << ">>> Solution <<<" << endl;
      for (auto d : res1) {
        cout << dir_name[d] << endl;
      }

      pz.printBoard();
    } else {
      cout << "UNSOLVABLE" << endl;
    }
  }
}
