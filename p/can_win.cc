#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool canWin(const vector<int> &moves, int start) {
  queue<int> q;
  vector<bool> visited(moves.size(), false);

  q.push(start);
  visited[start] = true;

  while (!q.empty()) {
    int idx = q.front();
    q.pop();

    if (idx == 0) {
      return true;
    }
    // try jump left and right
    int step = moves[idx];
    int left = idx - step;
    int right = idx + step;

    if (left >= 0 && !visited[left]) {
      q.push(left);
      visited[left] = true;
    }
    if (right < moves.size() && !visited[right]) {
      q.push(right);
      visited[right] = true;
    }
  }
  return false;
}

int main() {
  vector<int> moves{1, 3, 2, 0, 5, 3, 8, 4, 1};
  for (int i = 0; i < moves.size(); ++i) {
    cout << i << " : " << canWin(moves, i) << endl;
  }
}
