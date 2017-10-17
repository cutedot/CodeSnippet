#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Point;
typedef pair<Point, Point> Rect;

bool isOverlapping(const Rect &a, const Rect &b) {
  bool apart =
      (a.first.first > b.second.first || a.first.second > b.second.second ||
       a.second.first < b.first.first || a.second.second < b.first.second);
  return !apart;
}

// union find
int root(vector<int> &id, int p) {
  int r = p;
  while (id[r] != r) {
    r = id[r];
  }
  return r;
}

int quickUnion(vector<int> &id, int p, int q) {
  int rp = root(id, p);
  int rq = root(id, q);
  if (rp != rq) {
    // add rp to rq
    id[rp] = rq;
    // cout << "Connect " << p << " and " << q << endl;
    return 1;
  }
  return 0;
}

bool isConnected(vector<int> &id, int p, int q) {
  int rp = root(id, p);
  int rq = root(id, q);

  return rp == rq;
}

int rectIntersect(vector<Rect> rects) {
  int cnt = rects.size();
  vector<int> id(cnt, 0);
  for (int i = 0; i < cnt; ++i) {
    id[i] = i;
  }
  for (int i = 0; i < rects.size(); ++i) {
    for (int j = i + 1; j < rects.size(); ++j) {
      if (isOverlapping(rects[i], rects[j])) {
        // connect them
        cnt -= quickUnion(id, i, j);
      }
    }
  }
  return cnt;
}

int main() {
  {
    vector<Rect> rects{{{0, 0}, {2, 2}}, {{1, 1}, {3, 3}}, {{1, 0}, {3, 4}}};
    cout << rectIntersect(rects) << endl;
  }
  {
    vector<Rect> rects{
        {{0, 0}, {2, 2}}, {{1, 1}, {3, 3}}, {{4, 4}, {6, 6}}, {{5, 5}, {7, 7}}};
    cout << rectIntersect(rects) << endl;
  }
}
