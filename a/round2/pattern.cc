#include <iostream>
#include <map>
#include <string>

using namespace std;

//
// Given a pattern and a string str, find if str follows the same pattern.
//
// Here follow means a full match, such that there is a bijection between a
// letter in pattern and a non-empty substring in str.
//
// Examples:
// pattern = "abab", str = "redblueredblue" should return true.
// pattern = "aaaa", str = "asdasdasdasd" should return true.
// pattern = "aabb", str = "xyzabcxzyabc" should return false.
// Notes:
// You may assume both pattern and str contains only lowercase letters.
//

// backtracking
bool bt(string s, string p, map<char, string> &pTbl, map<string, char> &sTbl) {
  // Input
  //  - s : remaining string string
  //  - p : remaining pattern string
  //  - pTbl : pattern lookup table mapping from p -> s
  //  - pTbl : pattern lookup table mapping from s -> p
  if (s.empty() && p.empty()) {
    return true;
  }
  if (s.empty() || p.empty()) {
    return false;
  }
  // try match substring with the first character in pattern string
  if (pTbl.find(p[0]) != pTbl.end()) {
    string sub = pTbl[p[0]];
    if (sub == s.substr(0, sub.size())) {
      return bt(s.substr(sub.size(), s.size() - sub.size()),
                p.substr(1, p.size() - 1), pTbl, sTbl);
    } else {
      return false;
    }
  }
  for (int i = 1; i <= s.size(); ++i) {
    // substring of different length
    string prefix = s.substr(0, i);
    // if the prefix already assigned to other pattern, skip it
    if (sTbl.find(prefix) != sTbl.end()) {
      continue;
    }
    // add mapping for p[0] --> prefix and prefix --> p[0]
    pTbl[p[0]] = prefix;
    sTbl[prefix] = p[0];
    if (bt(s.substr(i, s.size() - i), p.substr(1, p.size() - 1), pTbl, sTbl)) {
      return true;
    }
    pTbl.erase(p[0]);
    sTbl.erase(prefix);
  }
  return false;
}

bool wordPatternMatch(string pattern, string str) {
  map<char, string> pTbl;
  map<string, char> sTbl;
  return bt(str, pattern, pTbl, sTbl);
}

int main() {
  string str = "asdasdasdasd";
  string pattern = "aaaa";
  cout << wordPatternMatch(pattern, str) << endl;
}
