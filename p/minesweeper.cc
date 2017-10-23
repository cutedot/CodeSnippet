#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// You are given a 2D char matrix representing the game board.
//  - 'M' represents an
// unrevealed mine,
//  - 'E' represents an unrevealed empty square,
//  - 'B' represents a revealed blank square that has no adjacent (above,
//    below, left, right, and all 4 diagonals) mines,
//  - digit ('1' to '8') represents how many mines are adjacent to this
//    revealed square,
//  - 'X' represents a revealed mine.
//
// Now given the next click position (row and column indices) among all the
// unrevealed squares ('M' or 'E'), return the board after revealing this
// position according to the following rules:
//
//  - If a mine ('M') is revealed, then the game is over - change it to 'X'.
//  - If an empty square ('E') with no adjacent mines is revealed, then change
//    it to revealed blank ('B') and all of its adjacent unrevealed squares
//    should be revealed recursively.
//  - If an empty square ('E') with at least one adjacent mine is revealed,
//    then change it to a digit ('1' to '8') representing the number of adjacent
//    mines. Return the board when no more squares will be revealed.

class MineSweper {
public:
  const vector<pair<int, int>> neighbors{{-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
                                         {1, 1},   {1, 0},  {1, -1}, {0, -1}};

public:
  MineSweper(const vector<string> &board) : board_(board) {}

  void PrintBorad() {
    for (auto s : board_) {
      cout << s << endl;
    }
  }

  // return the number of mines surround position
  int checkMine(const pair<int, int> &pos) {
    int num_mine = 0;
    for (auto d : neighbors) {
      int x = pos.first + d.first;
      int y = pos.second + d.second;
      if (x < 0 || x >= board_.size() || y < 0 || y >= board_[0].size() ||
          board_[x][y] != 'M') {
        continue;
      }
      ++num_mine;
    }
    return num_mine;
  }

  // return true if we can continue (e.g., did not clieck a mine), otherwise
  // return false
  bool ClickBoard(const pair<int, int> &click) {
    if (board_[click.first][click.second] == 'M') {
      board_[click.first][click.second] = 'X';
      return false;
    }

    // otherwise update the board
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(board_.size(),
                                 vector<bool>(board_[0].size(), false));

    // first item
    q.push(make_pair(click.first, click.second));
    visited[click.first][click.second] = true;

    while (!q.empty()) {
      pair<int, int> p = q.front();
      q.pop();

      // check this location
      int num_mine = checkMine(p);
      if (num_mine > 0) {
        board_[p.first][p.second] = ('0' + num_mine);
      } else {
        board_[p.first][p.second] = 'B';
        // check it's surrounding neighbors
        for (auto d : neighbors) {
          int x = p.first + d.first;
          int y = p.second + d.second;
          if (x < 0 || x >= board_.size() || y < 0 || y >= board_[0].size() ||
              visited[x][y] == true || board_[x][y] != 'E') {
            continue;
          }
          // enqueue (x, y)
          q.push(make_pair(x, y));
          visited[x][y] = true;
        }
      }
    }
    return true;
  }

private:
  vector<string> board_;
};

int main() {
  {
    MineSweper ms{{"EEEEE", "EEMEE", "EEEEE", "EEEEE"}};
    ms.ClickBoard(make_pair(3, 0));
    ms.PrintBorad();

    cout << "=============" << endl;

    ms.ClickBoard(make_pair(1, 2));
    ms.PrintBorad();
  }
}
