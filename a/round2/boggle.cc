#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void bt(vector<vector<char>> &board, set<string> &dict,
        vector<pair<int, int>> &path, string &cur, int i, int j,
        vector<vector<bool>> &visited, vector<vector<pair<int, int>>> &res) {
  if (i < 0 || i >= board.size() || j < 0 || j >= board.size() ||
      visited[i][j]) {
    return;
  }
  // add board[i][j] to current
  path.push_back(make_pair(i, j));
  cur.push_back(board[i][j]);
  visited[i][j] = true;
  // check if we have string cur in dict
  if (dict.find(cur) != dict.end()) {
    // found it!
    res.push_back(path);
  }
  // keep moving
  bt(board, dict, path, cur, i + 1, j, visited, res);
  bt(board, dict, path, cur, i - 1, j, visited, res);
  bt(board, dict, path, cur, i, j + 1, visited, res);
  bt(board, dict, path, cur, i, j - 1, visited, res);
  // remove board[i][j]
  visited[i][j] = false;
  path.pop_back();
  cur.pop_back();
}

vector<vector<pair<int, int>>> findWords(vector<vector<char>> &board,
                                         set<string> &dict) {
  vector<vector<pair<int, int>>> res;
  vector<vector<bool>> visited(board.size(),
                               vector<bool>(board[0].size(), false));
  vector<pair<int, int>> path;
  string cur = "";
  for (int i = 0; i < board.size(); ++i) {
    for (int j = 0; j < board[0].size(); ++j) {
      bt(board, dict, path, cur, i, j, visited, res);
    }
  }
  return res;
}

void bt2(vector<vector<char>> &board, vector<vector<bool>> &used,
         vector<vector<pair<int, int>>> &words, int idx,
         vector<vector<pair<int, int>>> &cur,
         vector<vector<pair<int, int>>> &res) {
  if (idx >= words.size()) {
    return;
  }
  // other wise try to place next words
  auto w = words[idx];
  bool canPlace = true;
  for (auto pos : w) {
    if (used[pos.first][pos.second]) {
      canPlace = false;
      break;
    }
  }
  if (canPlace) {
    // place it!
    cur.push_back(w);
    for (auto pos : w) {
      used[pos.first][pos.second] = true;
    }
    if (res.size() < cur.size()) {
      res = cur;
    }
    // keep going
    bt2(board, used, words, idx + 1, cur, res);

    // undo those changes
    cur.pop_back();
    for (auto pos : w) {
      used[pos.first][pos.second] = false;
    }
  }
  // try skip this word
  bt2(board, used, words, idx + 1, cur, res);
}
vector<vector<pair<int, int>>>
placeWords(vector<vector<char>> &board, vector<vector<pair<int, int>>> &words) {
  vector<vector<bool>> used(board.size(), vector<bool>(board[0].size(), false));
  vector<vector<pair<int, int>>> cur, res;
  bt2(board, used, words, 0, cur, res);
  return res;
}
vector<string> boggle_game(vector<vector<char>> &board, set<string> dict) {
  auto words = findWords(board, dict);
  auto res = placeWords(board, words);
  vector<string> ret;
  for (auto w : res) {
    string tmp = "";
    for (auto p : w) {
      tmp += board[p.first][p.second];
    }
    ret.push_back(tmp);
  }
  return ret;
}

int main() {
  // Test cases:
  {
    cout << "Test 1" << endl;
    vector<vector<char>> board{{'o', 'a', 'a', 'n'},
                               {'e', 't', 'a', 'e'},
                               {'i', 'h', 'k', 'r'},
                               {'i', 'f', 'l', 'v'}};
    set<string> dict{"oath", "pea", "eat", "rain"};

    for (auto s : boggle_game(board, dict)) {
      cout << s << endl;
    }
  }

  {
    cout << "Test 2" << endl;
    vector<vector<char>> board{
        {'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}};
    set<string> dict{"abc", "cfi", "beh", "defi", "gh"};

    for (auto s : boggle_game(board, dict)) {
      cout << s << endl;
    }
  }
}
