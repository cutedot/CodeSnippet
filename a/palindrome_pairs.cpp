#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool isPalindrome(string s) {
  int i = 0, j = s.size() - 1;
  while (i < j) {
    if (s[i] != s[j]) {
      return false;
    }
    ++i;
    --j;
  }
  return true;
}

vector<vector<int>> palindromePairs(vector<string> &words) {
  vector<vector<int>> ret;
  unordered_map<string, int> tbl;

  for (int i = 0; i < words.size(); ++i) {
    tbl[words[i]] = i;
  }

  for (int i = 0; i < words.size(); ++i) {
    string s = words[i];
    if (isPalindrome(s) && tbl.find("") != tbl.end()) {
      // find empty string
      if (tbl[""] != i) {
        // add <i, tbl[""]> and <tbl[""], i> to ret
        vector<int> p;
        p.push_back(i);
        p.push_back(tbl[""]);
        ret.push_back(p);
        reverse(p.begin(), p.end());
        ret.push_back(p);
      }
    } else {
      for (int j = 1; j <= s.size(); ++j) {
        string str0 = s.substr(0, j);
        string str1 = s.substr(j);

        // posible case: w + [str0, str1]
        if (isPalindrome(str0)) {
          reverse(str1.begin(), str1.end());
          if (tbl.find(str1) != tbl.end() && tbl[str1] != i) {
            // add <tbl[str1], i> to ret
            vector<int> p;
            p.push_back(tbl[str1]);
            p.push_back(i);
            ret.push_back(p);
          }
        }
        // possible case : [str0, str1] + w
        if (isPalindrome(str1)) {
          reverse(str0.begin(), str0.end());
          if (tbl.find(str0) != tbl.end() && tbl[str0] != i) {
            // add <i, tbl[str0]> to ret
            vector<int> p;
            p.push_back(i);
            p.push_back(tbl[str0]);
            ret.push_back(p);
          }
        }
      }
    }
  }
  return ret;
}

void printResult(vector<vector<int>> res) {
  for (auto v : res) {
    for (auto i : v) {
      cout << i << " ";
    }
    cout << endl;
  }
}

int main() {

  {
    // TEST 1
    cout << "TEST 1" << endl;
    vector<string> words{"bat", "tab", "cat"};
    vector<vector<int>> res = palindromePairs(words);
    printResult(res);
  }

  {
    // TEST 2
    cout << "TEST 2" << endl;
    vector<string> words{"abcd", "dcba", "lls", "s", "sssll"};
    vector<vector<int>> res = palindromePairs(words);
    printResult(res);
  }

  {
    // TEST 3
    cout << "TEST 3" << endl;
    vector<string> words{"a", ""};
    vector<vector<int>> res = palindromePairs(words);
    printResult(res);
  }

  {
    // TEST 3
    cout << "TEST 3" << endl;
    vector<string> words{"bb", "bababab", "baab", "abaabaa", "aaba",
                         "",   "bbaa",    "aba",  "baa",     "b"};
    vector<vector<int>> res = palindromePairs(words);
    printResult(res);
  }
}
