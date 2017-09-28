#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

bool backtrack(
    string s, // remaining string
    string p, // remaining pattern
    unordered_map<char, string>
        &tbl // pattern lookup table mapping form symbol in pattern -> string
) {
  if (s.size() == 0 && p.size() == 0) {
    return true;
  }
  if (s.size() == 0 || p.size() == 0) {
    return false;
  }
  char cur = p[0];
  if (tbl.find(cur) != tbl.end()) {
    // pattern already exist in the lookup table
    // try to match it
    string st = tbl[cur];

    // compare the prefix
    if (s.find(st) == 0) {
      // find a match, consume st
      return backtrack(s.substr(st.size(), s.size() - st.size()),
                       p.substr(1, p.size() - 1), tbl);
    }
  } else {
    // try to add a new pattern
    for (int i = 0; i < s.size(); ++i) {
      // try to match cur with st
      string st = s.substr(0, i + 1);
      // enter
      tbl[cur] = st; // insert
      // try exploring the rest of the string
      if (backtrack(s.substr(i + 1, s.size() - 1 - i),
                    p.substr(1, p.size() - 1), tbl)) {
        return true;
      }
      // exit
      tbl.erase(cur); // remove
    }
  }
  return false;
}

bool patternMatch(string s, string p) {
  unordered_map<char, string> tbl;
  return backtrack(s, p, tbl);
}

int main() {
  {
    // TEST 1
    cout << "Test 1" << endl;
    string s = "aabbcc";
    string t = "xyz";

    cout << patternMatch(s, t) << endl;
  }
  {
    // TEST 2
    cout << "Test 2" << endl;
    string s = "airbnbairbn";
    string t = "xyzxy";

    cout << patternMatch(s, t) << endl;
  }
}
