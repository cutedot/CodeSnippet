#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// weight function
int getWeight(int u, int v) { return (u - v) * (u - v); }
// relax edge u->v
void relax(vector<int> &d, int u, int v) {
  if (d[v] > d[u] + getWeight(u, v)) {
    d[v] = d[u] + getWeight(u, v);
  }
}

// Bellman-Ford algorithm
// Complexity : O( V * E )
int bellmanFord(vector<vector<int>> wizards) {
  // initialization
  int nWizard = wizards.size();
  vector<int> d(nWizard, INT_MAX); // distance from 0
  d[0] = 0;

  for (int i = 0; i < nWizard; ++i) {
    // relax all edges
    for (int j = 0; j < wizards.size(); ++j) {
      // relax
      for (int k = 0; k < wizards[j].size(); ++k) {
        relax(d, j, wizards[j][k]);
      }
    }
  }

  return d[nWizard - 1];
}

int find_min(vector<int> &d, vector<bool> &visited) {
  int ret;
  int min_val = INT_MAX;

  for (int i = 0; i < d.size(); ++i) {
    if (visited[i] == false && d[i] < min_val) {
      ret = i;
      min_val = d[i];
    }
  }
  return ret;
}

// Dijkstra algorithm
// Complexity : O(V^2)
int dijkstra(vector<vector<int>> wizards) {
  int nWizard = wizards.size();
  vector<int> d(nWizard, INT_MAX);      // distance from 0
  int num_visited = 0;                  // number of nodes visited
  vector<bool> visited(nWizard, false); // tracking visited nodes
  // init
  d[0] = 0;

  while (num_visited <= nWizard) {
    int u = find_min(d, visited);
    visited[u] = true;
    ++num_visited;
    for (auto v : wizards[u]) {
      // relax u->v
      relax(d, u, v);
    }
  }
  return d[nWizard - 1];
}

int minDist(vector<vector<int>> wizards) {
  // return bellmanFord(wizards);
  assert(dijkstra(wizards) == bellmanFord(wizards));
  return dijkstra(wizards);
}

int main() {
  {
    // TEST1
    vector<vector<int>> wizards{{1, 3}, {2, 3}, {4}, {1, 2, 4}, {0, 2}};
    cout << minDist(wizards) << endl;
  }
}
