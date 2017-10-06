#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// TODO: read the list from file

// find the intersect of two lists
int intersect(vector<char> &l0, vector<char> &l1) {
  unordered_set<char> s;
  int ret = 0;
  for (auto i : l0) {
    s.insert(i);
  }
  for (auto i : l1) {
    if (s.find(i) != s.end()) {
      ++ret;
    }
  }
  return ret;
}

// find the diff of two lists, return items that are in l1 but not in l0
vector<char> diff(vector<char> &l0, vector<char> &l1) {
  unordered_set<char> s;
  vector<char> ret;
  for (auto i : l0) {
    s.insert(i);
  }
  for (auto i : l1) {
    if (s.find(i) == s.end()) {
      ret.push_back(i);
    }
  }
  return ret;
}

vector<char> buddyList(vector<char> self, vector<vector<char>> &traveler,
                       int max_sug) {
  // buddy list, each entry stores <num cities in common, buddy id>
  vector<pair<int, int>> buddy;
  vector<char> ret;
  for (int i = 0; i < traveler.size(); ++i) {
    int n = intersect(self, traveler[i]);
    buddy.push_back(make_pair(n, i));
  }

  sort(buddy.begin(), buddy.end(), greater<pair<int, int>>());

  for (auto i : buddy) {
    // get the diff
    auto d = diff(self, traveler[i.second]);
    for (auto c : d) {
      ret.push_back(c);
      if (ret.size() >= max_sug) {
        return ret;
      }
    }
  }
  return ret;
}

int travelBuddy(vector<char> self, vector<vector<char>> &traveler) {
  int common = 0;
  int ret = -1;
  for (int i = 0; i < traveler.size(); ++i) {
    int n = intersect(self, traveler[i]);
    if (n > common) {
      common = n;
      ret = i;
    }
  }
  return ret;
}

int main() {
  {
    // TEST 1
    vector<char> self{'a', 'b', 'c', 'd'};
    vector<vector<char>> traveler{{'a', 'b', 'e', 'f'}, {'a', 'c', 'd', 'g'}};
    cout << travelBuddy(self, traveler) << endl;
    for (auto i : buddyList(self, traveler, 2)) {
      cout << i << " ";
    }
    cout << endl;
  }
}
