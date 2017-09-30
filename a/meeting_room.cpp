#include <iostream>
#include <vector>

using namespace std;

struct point {
  bool isStarting; // true if this is the starting point of a meeting
  int timestamp;   // time

  point(bool starting, int ts) : isStarting(starting), timestamp(ts) {}
};

bool Comparator(point &p0, point &p1) { return p0.timestamp < p1.timestamp; }

vector<pair<int, int>> meetingRoom(vector<vector<pair<int, int>>> sched) {
  vector<point> pool;
  vector<pair<int, int>> ret;
  for (auto p : sched) { // for each employee
    for (auto q : p) {   // for each meeting
      pool.emplace_back(true, q.first);
      pool.emplace_back(false, q.second);
    }
  }
  sort(pool.begin(), pool.end(), Comparator);

  // scan all starting and ending points, also keep track of the outstanding
  // meetings
  int outstanding = 0;
  int left = -1;
  for (auto p : pool) {
    if (p.isStarting) {
      if (left != -1 && outstanding == 0 && left < p.timestamp) {
        // marks the end of the available interval
        ret.emplace_back(left, p.timestamp);
        left = -1; // close the interval
      }
      ++outstanding;
    } else {
      --outstanding;
    }
    if (outstanding == 0) {
      // marks the start of the available interval
      left = p.timestamp;
    }
  }

  return ret;
}

void printInterval(vector<pair<int, int>> intervals) {
  for (auto p : intervals) {
    cout << "[ " << p.first << ", " << p.second << " ]  ";
  }
  cout << endl;
}
int main() {
  {
    cout << "TEST 1" << endl;
    vector<vector<pair<int, int>>> sched{{{0, 1}, {3, 4}}, {{4, 5}}, {{7, 8}}};

    printInterval(meetingRoom(sched));
  }
  { cout << "TEST 2" << endl; }
}
