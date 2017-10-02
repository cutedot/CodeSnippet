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

// TODO: finish Dijkstra
/*
bool Comparator(pair<int, int> &a, pair<int, int> &b) {
  return a.second > b.second;
}

int dijkstra(vector<vector<int>> wizards) {
  vector<int> d(nWizard, INT_MAX); // distance from 0
  // min-heap
  priority_queue<pair<int, int>, vector<pair<int, int>>, Comparator>
      pq; // <wiz, dist> pair
  int nWizard = wizards.size();

  // init
  pq.push(make_pair<int, int>(0, 0));
  d[0] = 0;

  while (pq.size() > 0) {
    auto p = pq.top();
    pq.pop();

    int u = p.first;
    for (auto v : wizards[u]) {
      // relax u->v
      if (d[v] > d[u] + getWeight(u, v)) {
        d[v] = d[u] + getWeight(u, v);
      }
    }
  }
}
*/
int minDist(vector<vector<int>> wizards) { return bellmanFord(wizards); }

int main() {
  {
    // TEST1
    vector<vector<int>> wizards{{1, 3}, {2, 3}, {4}, {1, 2, 4}, {0, 2}};
    cout << minDist(wizards) << endl;
  }
}
