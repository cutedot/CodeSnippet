#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
//
// String pyramid transition matrix
//
// The tbl stores mapping

void getPerm(vector<string> &p, string cur, int idx, vector<string> &res) {
  if (idx == p.size()) {
    res.push_back(cur);
    return;
  }
  for (auto c : p[idx]) {
    getPerm(p, cur + c, idx + 1, res);
  }
  return;
}

// recursively nav up to the root to find the root
string getRoot(string &level, unordered_map<string, string> &tbl) {
  string ret = "";
  if (level.size() == 1) {
    return level;
  }
  vector<string> upper_level;
  vector<string> tmp;
  for (int i = 0; i < level.size() - 1; ++i) {
    string r = tbl[level.substr(i, 2)];
    if (r.empty()) {
      continue;
    }
    tmp.push_back(r);
  }
  // get all possible upper level
  getPerm(tmp, "", 0, upper_level);
  for (auto &u : upper_level) {
    string r = getRoot(u, tbl);
    assert(!r.empty());
    ret += r;
  }
  return ret;
}

string stringPyramidTransitionMatrix(string &leaf,
                                     unordered_map<string, string> &tbl) {
  string ret = "";
  string r = getRoot(leaf, tbl);
  unordered_set<char> root_set;
  for (auto c : r) {
    root_set.insert(c);
  }
  for (auto c : root_set) {
    ret += c;
  }
  return ret;
}

// recursively nav up to the root to find the root
string getRootwithMemorization(string &level,
                               unordered_map<string, string> &tbl,
                               unordered_map<string, string> &cache) {
  string ret = "";
  if (level.size() == 1) {
    return level;
  }
  vector<string> upper_level;
  vector<string> tmp;
  for (int i = 0; i < level.size() - 1; ++i) {
    string r = tbl[level.substr(i, 2)];
    if (r.empty()) {
      continue;
    }
    tmp.push_back(r);
  }
  // get all permutation of upper level
  getPerm(tmp, "", 0, upper_level);
  for (auto &u : upper_level) {
    string r;
    // speedup the search by memorization
    if (cache.find(u) == cache.end()) {
      r = getRoot(u, tbl);
      cache[u] = r;
      assert(!r.empty());
    } else {
      r = cache[u];
    }
    ret += r;
  }
  return ret;
}

string
stringPyramidTransitionMatrixMemorization(string &leaf,
                                          unordered_map<string, string> &tbl) {
  string ret = "";
  unordered_map<string, string> cache;
  string r = getRootwithMemorization(leaf, tbl, cache);
  unordered_set<char> root_set;
  for (auto c : r) {
    root_set.insert(c);
  }
  for (auto c : root_set) {
    ret += c;
  }
  return ret;
}

int main() {
  {
    string leaf = "ABCD";
    unordered_map<string, string> tbl{{"AA", "B"}, {"AB", "AC"}, {"AC", "D"},
                                      {"AD", "A"}, {"BA", "D"},  {"BB", "BC"},
                                      {"BC", "A"}, {"CD", "B"}};

    // cout << stringPyramidTransitionMatrix(leaf, tbl) << endl;
    cout << stringPyramidTransitionMatrixMemorization(leaf, tbl) << endl;
  }
}
