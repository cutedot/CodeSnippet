#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/*
 * Given An array of strings where "L" indicates land and "W" indicates water,
 * and a coordinate marking a starting point in the middle of the ocean The
 * Challenge: Find and mark the ocean in the map by changing appropriate W's to
 * O's. An ocean coordinate is defined to be any coordinate directly adjacent
 * to any other ocean coordinate.
 *
 * Input:
 *      LLLLLLLLLLLLLLLLLLLL
 *      LLLLLLLLLLLLLLWLLLLL
 *      LLWWLLLLLLLLLLLLLLLL
 *      LLWWLLLLLLLLLLLLLLLL
 *      LLLLLLLLLLLLLLLLLLLL
 *      LLLLLLLWWLLLLLLLLLLL
 *      LLLLLLLLWWLLLLLLLLLL
 *      LLLLLLLLLWWWLLLLLLLL
 *      LLLLLLLLLLWWWWWWLLLL
 *      LLLLLLLLLLWWWWWWLLLL
 *      LLLLLLLLLLWWWWWWLLLL
 *      LLLLWWLLLLWWWWWWLLLL
 *      LLLLWWWLLLWWWWWWWWWW
 *      LLLLLWWWWWWWWWWWLLLL
 *      LLLLLLLLLLLLLLWWWWLL
 *      LLLLLLLLLLLLLLWLLLLL
 *      LLLLWLLLLLLLLLLLLWLL
 *      LLLLLLLLLLLLLLLLLLWL
 *
 * Ocean Coordinate:
 *      row = 10
 *      col = 12
 *
 * Expected Output:
 *      LLLLLLLLLLLLLLLLLLLL
 *      LLLLLLLLLLLLLLWLLLLL
 *      LLWWLLLLLLLLLLLLLLLL
 *      LLWWLLLLLLLLLLLLLLLL
 *      LLLLLLLLLLLLLLLLLLLL
 *      LLLLLLLOOLLLLLLLLLLL
 *      LLLLLLLLOOLLLLLLLLLL
 *      LLLLLLLLLOOOLLLLLLLL
 *      LLLLLLLLLLOOOOOOLLLL
 *      LLLLLLLLLLOOOOOOLLLL
 *      LLLLLLLLLLOOOOOOLLLL
 *      LLLLOOLLLLOOOOOOLLLL
 *      LLLLOOOLLLOOOOOOOOOO
 *      LLLLLOOOOOOOOOOOLLLL
 *      LLLLLLLLLLLLLLOOOOLL
 *      LLLLLLLLLLLLLLOLLLLL
 *      LLLLWLLLLLLLLLLLLWLL
 *      LLLLLLLLLLLLLLLLLLWL
 **/

void floodFill(vector<string> &board, int row, int col) {
  if (board.size() == 0) {
    return;
  }
  // fill the board
  queue<pair<int, int>> q;
  q.emplace(row, col);
  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    // fill position p
    int x = p.first;
    int y = p.second;
    board[x][y] = 'O';
    vector<pair<int, int>> neighbor{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (auto o : neighbor) {
      int new_x = x + o.first;
      int new_y = y + o.second;
      if (new_x > 0 && new_y > 0 && new_x < board.size() &&
          new_y < board[0].size() && board[new_x][new_y] == 'W') {
        q.emplace(new_x, new_y);
      }
    }
  }
}

void printBoard(vector<string> &board) {
  for (auto s : board) {
    cout << s << endl;
  }
}

int main() {
  {
    // TEST1
    cout << "TEST1" << endl;
    vector<string> board{
        "LLLLLLLLLLLLLLLLLLLL", "LLLLLLLLLLLLLLWLLLLL", "LLWWLLLLLLLLLLLLLLLL",
        "LLWWLLLLLLLLLLLLLLLL", "LLLLLLLLLLLLLLLLLLLL", "LLLLLLLWWLLLLLLLLLLL",
        "LLLLLLLLWWLLLLLLLLLL", "LLLLLLLLLWWWLLLLLLLL", "LLLLLLLLLLWWWWWWLLLL",
        "LLLLLLLLLLWWWWWWLLLL", "LLLLLLLLLLWWWWWWLLLL", "LLLLWWLLLLWWWWWWLLLL",
        "LLLLWWWLLLWWWWWWWWWW", "LLLLLWWWWWWWWWWWLLLL", "LLLLLLLLLLLLLLWWWWLL",
        "LLLLLLLLLLLLLLWLLLLL", "LLLLWLLLLLLLLLLLLWLL", "LLLLLLLLLLLLLLLLLLWL"};
    cout << "Before:" << endl;
    printBoard(board);
    floodFill(board, 10, 12);
    cout << "Fill <10, 12>" << endl;
    printBoard(board);
    cout << endl;
  }
  {
    // TEST2
    vector<string> board{
        "LLLLLLLLLLLLLLLLLLLL", "LLLLLLLLLLLLLLWLLLLL", "LLWWLLLLLLLLLLLLLLLL",
        "LLWWLLLLLLLLLLLLLLLL", "LLLLLLLLLLLLLLLLLLLL", "LLLLLLLWWLLLLLLLLLLL",
        "LLLLLLLLWWLLLLLLLLLL", "LLLLLLLLLWWWLLLLLLLL", "LLLLLLLLLLWWWWWWLLLL",
        "LLLLLLLLLLWWWWWWLLLL", "LLLLLLLLLLWWWWWWLLLL", "LLLLWWLLLLWWWWWWLLLL",
        "LLLLWWWLLLWWWWWWWWWW", "LLLLLWWWWWWWWWWWLLLL", "LLLLLLLLLLLLLLWWWWLL",
        "LLLLLLLLLLLLLLWLLLLL", "LLLLWLLLLLLLLLLLLWLL", "LLLLLLLLLLLLLLLLLLWL"};
    cout << "Before:" << endl;
    printBoard(board);
    floodFill(board, 17, 18);
    cout << "Fill <17, 18>" << endl;
    printBoard(board);
    cout << endl;
  }
  {
    // TEST2
    vector<string> board{
        "LLLLLLLLLLLLLLLLLLLL", "LLLLLLLLLLLLLLWLLLLL", "LLWWLLLLLLLLLLLLLLLL",
        "LLWWLLLLLLLLLLLLLLLL", "LLLLLLLLLLLLLLLLLLLL", "LLLLLLLWWLLLLLLLLLLL",
        "LLLLLLLLWWLLLLLLLLLL", "LLLLLLLLLWWWLLLLLLLL", "LLLLLLLLLLWWWWWWLLLL",
        "LLLLLLLLLLWWWWWWLLLL", "LLLLLLLLLLWWWWWWLLLL", "LLLLWWLLLLWWWWWWLLLL",
        "LLLLWWWLLLWWWWWWWWWW", "LLLLLWWWWWWWWWWWLLLL", "LLLLLLLLLLLLLLWWWWLL",
        "LLLLLLLLLLLLLLWLLLLL", "LLLLWLLLLLLLLLLLLWLL", "LLLLLLLLLLLLLLLLLLWL"};
    cout << "Before:" << endl;
    printBoard(board);
    floodFill(board, 2, 2);
    cout << "Fill <2, 2>" << endl;
    printBoard(board);
    cout << endl;
  }
}
