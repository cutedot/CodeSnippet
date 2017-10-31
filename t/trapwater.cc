#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int trapRainWater(vector<vector<int>> &heightMap) {
  if (heightMap.size() == 0) {
    return 0;
  }
  int nrow = heightMap.size(), ncol = heightMap[0].size();
  vector<vector<bool>> visited(nrow, vector<bool>(ncol, false));
  priority_queue<pair<int, pair<int, int>>> pq;
  for (int i = 0; i < nrow; ++i) {
    for (int j = 0; j < ncol; ++j) {
      if (i == 0 || i == (nrow - 1) || j == 0 || j == (ncol - 1) ||
          visited[i][j] == false) {
        pq.push(make_pair(heightMap[i][j], make_pair(i, j)));
        visited[i][j] = true;
      }
    }
  }
  int height = INT_MIN;
  int water = 0;
  while (!pq.empty()) {
    auto item = pq.top();
    pq.pop();

    int h = item.first;
    int i = item.second.first;
    int j = item.second.second;
    // the max height of it's neighbors
    height = max(height, heightMap[i][j]);
    // visit neighbors
    vector<vector<int>> dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto d : dirs) {
      int x = i + d[0];
      int y = h + d[1];
      if (x < 0 || x > nrow || y < 0 || y > ncol || visited[x][y]) {
        continue; // skip this one
      }
      // add water to the neighbors
      if (height > heightMap[x][y]) {
        water += height - heightMap[x][y];
      }
      pq.push(make_pair(heightMap[x][y], make_pair(x, y)));
      visited[x][y] = true;
    }
  }
  return water;
}

int main() {
  vector<vector<int>> board{
      {1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}};

  cout << trapRainWater(board) << endl;
}
