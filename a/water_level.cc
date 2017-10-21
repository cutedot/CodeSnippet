#include <iostream>
#include <list>
using namespace std;
// This is copied from http://www.1point3acres.com/bbs/thread-216807-1-1.html

struct Segment {
  int x;
  double h;
  Segment(int left = 0, double height = 0) : x(left), h(height) {}
};

list<Segment>::iterator mergeSegment(list<Segment>::iterator iter,
                                     list<Segment> &level) {
  if (prev(iter)->h == iter->h) {
    iter = prev(iter);
    level.erase(next(iter));
  }
  if (next(iter)->h == iter->h) {
    level.erase(next(iter));
  }
  return iter;
}

// Solution 1:
// ASSUMPTION: water will flow equally to the left and right if it's a local
// peak
void getWaterLevel(list<Segment> &level, int pos, double amount) {
  list<Segment>::iterator left, right;
  for (auto iter = level.begin(); iter != level.end() && iter->x <= pos;
       ++iter) {
    left = iter;
  }
  right = left;

  while (amount > 0) {
    while (prev(left)->h < left->h)
      --left;
    while (next(left)->h < left->h)
      ++left;
    while (next(right)->h < right->h)
      ++right;
    while (prev(right)->h < right->h)
      --right;

    int left_w = next(left)->x - left->x;
    int right_w = next(right)->x - right->x;

    double minleft_h = min(prev(left)->h, next(left)->h);
    double minright_h = min(prev(right)->h, next(right)->h);

    double left_cap = left_w * (minleft_h - left->h);
    double right_cap = right_w * (minright_h - right->h);

    double min_cap = min(left_cap, right_cap);

    auto min_pit = (left_cap <= right_cap) ? left : right;
    // auto max_pit = (left_cap > right_cap) ? left : right;

    if (left == right) {
      // has only one valley
      if (amount < min_cap) {
        left->h += amount / left_w;
        amount = 0;
      } else {
        left->h = minleft_h;
        left = mergeSegment(left, level);
        amount -= min_cap;
      }
      right = left;
    } else {
      // has two valley
      if (amount < min_cap * 2) {
        left->h += (amount / 2) / left_w;
        right->h += (amount / 2) / right_w;
        amount = 0;
      } else {
        // fill the smaller valley and goto next simulation iteration
        amount -= min_cap * 2;
        min_pit->h = min(prev(min_pit)->h, next(min_pit)->h);
        if (left_cap <= right_cap) {
          // fill the left cap
          left->h = minleft_h;
          left = mergeSegment(left, level);
          right->h = min(right->h + min_cap / right_w, minright_h);
          right = mergeSegment(right, level);
        } else {
          // fill the right cap
          right->h = minleft_h;
          right = mergeSegment(right, level);
          left->h = min(left->h + min_cap / right_w, minleft_h);
        }
      }
    }
  }
}

// Solution 2:
// ASSUMPTION: water always flows to the left valley
void getWaterLevel2(list<Segment> &level, int pos, double amount) {
  list<Segment>::iterator valley;
  for (auto it = level.begin(); it != level.end() && it->x <= pos; ++it) {
    valley = it;
  }
  while (amount > 0) {
    while (next(valley)->h < valley->h)
      ++valley;
    while (prev(valley)->h < valley->h)
      --valley;

    // now valley points to the local minimum
    int valley_width = next(valley)->x - valley->x;
    double valley_height = min(prev(valley)->h, next(valley)->h);
    double valley_depth = valley_height - valley->h;
    int valley_cap = valley_width * valley_depth;

    cout << valley->h << endl;
    cout << valley_width << " " << valley_depth << endl;

    if (valley_cap > amount) {
      // fill the valley and we are done
      valley->h += amount / valley_width;
      amount = 0;
    } else {
      // fill the valley and goto next iteration
      amount -= valley_cap;
      valley->h = valley_height;
      valley = mergeSegment(valley, level);
    }
  }
}

void printLevel(list<Segment> &level) {
  for (auto it = level.begin(); it != level.end(); ++it) {
    for (int i = it->x; i < next(it)->x; ++i) {
      cout << "||";
      for (double j = 0; j < it->h; j += 0.25) {
        cout << "#";
      }
      cout << "  " << it->h << endl;
      cout << endl;
    }
  }
}

int main() {
  /*
  {
    list<Segment> level{{0, 5},  {1, 0},  {2, 3},  {5, 4},  {7, 1},  {8, 3},
                        {9, 2},  {10, 0}, {12, 1}, {13, 3}, {14, 4}, {15, 3},
                        {16, 2}, {17, 4}, {18, 3}, {20, 6}};
    printLevel(level);
    getWaterLevel(level, 15, 3);

    cout << endl << "After droping 3 liter water" << endl;
    printLevel(level);

    getWaterLevel(level, 15, 3);

    cout << endl << "After droping another 3 liter water" << endl;
    printLevel(level);

    getWaterLevel(level, 15, 41);

    cout << endl << "After droping another 41 (47 total) liter water" << endl;
    printLevel(level);
  }
  */
  {
    list<Segment> level{{0, 5},  {1, 0},  {2, 3},  {5, 4},  {7, 1},  {8, 3},
                        {9, 2},  {10, 0}, {12, 1}, {13, 3}, {14, 4}, {15, 3},
                        {16, 2}, {17, 4}, {18, 3}, {20, 6}};
    printLevel(level);
    getWaterLevel2(level, 15, 3);

    cout << endl << "After droping 3 liter water" << endl;
    printLevel(level);

    getWaterLevel(level, 15, 26);

    cout << endl << "After droping another 26 (29 total) liter water" << endl;
    printLevel(level);
  }
}
