#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// Boggle Game
//
// board:
// {'a', 'b', 'c'},
// {'d', 'e', 'f'},
// {'g', 'h', 'i'}
// dict:
// ["abc", "cfi", "beh", "defi", "gh"]

// Trie class
class Trie {
public:
  struct TrieNode {
    bool isWord;
    unordered_map<char, TrieNode *> child;
    TrieNode() : isWord(false) {}
  };

public:
  Trie() {}
  Trie(vector<string> words) {
    for (auto s : words) {
      this->insert(s);
    }
  }
  ~Trie() {}

  void insert(string s) {
    TrieNode *n = &head_;

    for (auto c : s) {
      if (n->child[c]) {
        n = n->child[c];
      } else {
        TrieNode *new_child = new TrieNode();
        n->child[c] = new_child;
        n = new_child;
      }
    }

    n->isWord = true;
    return;
  }

  bool hasPrefix(string s) {
    TrieNode *n = &head_;
    for (auto c : s) {
      if (n->child[c]) {
        n = n->child[c];
      } else {
        return false;
      }
    }

    return true;
  }

  bool find(string s) {
    TrieNode *n = &head_;
    for (auto c : s) {
      if (n->child[c]) {
        n = n->child[c];
      } else {
        return false;
      }
    }

    return n->isWord;
  }

private:
  TrieNode head_;
};

string pathToString(vector<vector<char>> &board, vector<pair<int, int>> path) {
  string res = "";
  for (auto p : path) {
    res += board[p.first][p.second];
  }
  return res;
}

// backtracking function for searching for words on board
void findWords(vector<vector<char>> &board,         // board
               Trie &dict,                          // dictionary
               vector<vector<bool>> &visited,       // visited points
               vector<vector<pair<int, int>>> &res, // words
               vector<pair<int, int>> &prefix,      // prefix
               int x, int y                         // location
) {
  // check validity of this position
  if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() ||
      visited[x][y] == true) {
    // invalid point, ignore
    return;
  }

  // visit this point
  prefix.emplace_back(x, y);
  visited[x][y] = true;
  string cur = pathToString(board, prefix);

  if (!dict.hasPrefix(cur)) {
    // if the prefix does exist, we can stop here
    // clean up
    visited[x][y] = false;
    prefix.pop_back();
    return;
  }
  if (dict.find(cur)) {
    res.push_back(prefix);
  }

  // visiting neighbors
  findWords(board, dict, visited, res, prefix, x + 1, y);
  findWords(board, dict, visited, res, prefix, x - 1, y);
  findWords(board, dict, visited, res, prefix, x, y + 1);
  findWords(board, dict, visited, res, prefix, x, y - 1);

  visited[x][y] = false;
  prefix.pop_back();
}

bool canPlace(vector<vector<bool>> &board, vector<pair<int, int>> path) {
  for (auto pos : path) {
    if (board[pos.first][pos.second]) {
      return false;
    }
  }
  return true;
}

void setPath(vector<vector<bool>> &board, vector<pair<int, int>> path,
             bool val) {
  for (auto pos : path) {
    board[pos.first][pos.second] = val;
  }
  return;
}

// backtracking function for placing words on board
//  - try to place as many words on board as possible
void placeWords(vector<vector<bool>> &board, // current board, cell used if true
                vector<vector<pair<int, int>>> &words, // all the words
                int i,                                 // current index
                vector<vector<pair<int, int>>> &cur,   // current set of strings
                vector<vector<pair<int, int>>> &ret    // resulting set of words
) {
  if (i == words.size()) {
    if (ret.size() < cur.size()) {
      ret = cur;
    }
    return;
  }

  // try to place words[i] on the board if possible
  if (canPlace(board, words[i])) {
    // place the words and keep trying
    setPath(board, words[i], true);
    cur.push_back(words[i]);
    placeWords(board, words, i + 1, cur, ret);
    cur.pop_back();
    setPath(board, words[i], false);
  }
  // try with no words[i]
  placeWords(board, words, i + 1, cur, ret);
}

// two pass backtracking
//  - first pass finds all words and its trail (the positions of all characters
//  in each word)
//  - second pass try to place as many string on the board as possible
vector<string> boggle_game(vector<vector<char>> &board, vector<string> dict) {
  vector<string> ret;
  if (board.size() == 0) {
    return ret;
  }
  vector<vector<pair<int, int>>> res;
  vector<vector<bool>> visited(board.size(),
                               vector<bool>(board[0].size(), false));
  Trie trie(dict);
  vector<pair<int, int>> prefix;

  for (int i = 0; i < board.size(); ++i) {
    for (int j = 0; j < board[0].size(); ++j) {
      findWords(board, trie, visited, res, prefix, i, j);
    }
  }

  // print out all the words from the board

  // try to place on board
  vector<vector<pair<int, int>>> cur_set;
  vector<vector<pair<int, int>>> result;

  placeWords(visited, res, 0, cur_set, result);
  for (auto p : result) {
    // cout << pathToString(board, p) << endl;
    ret.push_back(pathToString(board, p));
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
    vector<string> dict{"oath", "pea", "eat", "rain"};

    for (auto s : boggle_game(board, dict)) {
      cout << s << endl;
    }
  }

  {
    cout << "Test 2" << endl;
    vector<vector<char>> board{
        {'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}};
    vector<string> dict{"abc", "cfi", "beh", "defi", "gh"};

    for (auto s : boggle_game(board, dict)) {
      cout << s << endl;
    }
  }
}
