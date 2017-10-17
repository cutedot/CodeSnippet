#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

//
// mirror : (0, 0) -> (0, 1)
//          (1, 0) -> (0, 0)
//          (1, 1) -> (1, 0)
//          (0, 1) -> (1, 1)
//          (x, y) -> ()
int hilbertCurve(int x, int y, int iter) {
  if (iter == 0)
    return 1;
  int w = pow(2, iter - 1);

  if (x < w && y < w) {
    // buttom left
    // y=x mirror
    return hilbertCurve(y, x, iter - 1);
  } else if (x < w && y >= w) {
    // upper left
    return w * w + hilbertCurve(x, y - w, iter - 1) + w * w;
  } else if (x >= w && y < w) {
    // buttom right
    // y = -x mirror
    return 3 * w * w + hilbertCurve(w - 1 - y, 2w - 1 - x, iter - 1);
  } else {
    // upper right
    return 2 * w * w + hilbertCurve(x - w, y - w, iter - 1) + 3 * w * w;
  }
}

int main() {}
