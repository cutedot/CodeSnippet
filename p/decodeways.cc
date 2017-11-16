#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool validSingle(string s) {
  int i = stoi(s);
  return i > 0 && i <= 9;
}

bool validDouble(string s) {
  int i = stoi(s);
  return i >= 10 && i <= 26;
}

char decode(string s) {
  int i = stoi(s);
  return 'A' + i - 1;
}

void bt(string s, string dec, set<string> words) {
  if (s.size() == 0) {
    words.insert(dec);
    cout << dec << endl;
    return;
  }

  // try to consume one digit
  string one = s.substr(0, 1);
  if (validSingle(one)) {
    bt(s.substr(1, s.size() - 1), dec + decode(one), words);
  }
  string two = s.substr(0, 2);
  // try to consume two digit
  if (s.size() > 1 && validDouble(two)) {
    bt(s.substr(2, s.size() - 2), dec + decode(two), words);
  }
  return;
}

vector<string> DecodeWays(int num) {
  // backtracking
  set<string> words;
  vector<string> ret;
  string s = to_string(num);
  bt(s, "", words);
  for (auto w : words) {
    ret.push_back(w);
  }
  return ret;
}

int main() {
  auto words = DecodeWays(1234);
  for (auto w : words) {
    cout << w << endl;
  }
}
