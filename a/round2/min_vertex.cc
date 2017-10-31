#include <iostream>
#include <set>
#include <vector>

using namespace std;

void dfs(const vector<vector<int>> &graph, int idx, vector<bool> &visited,
         set<int> starting) {
  // visit node idx
  visited[idx] = true;

  // visit its neighbors
  for (int i = 0; i < graph[idx].size(); ++i) {
    int v = graph[idx][i];
    if (visited[v]) {
      // if  is in starting set, we should remove it since we have a path to v
      // but not v to the startin point
      starting.erase(v);
    } else {
      // visit it
      dfs(graph, v, visited, starting);
    }
  }
}

vector<int> minVertex(const vector<vector<int>> &graph) {
  set<int> starting; // starting vertices
  vector<bool> visited(graph.size(), false);

  for (int i = 0; i < graph.size(); ++i) {
    if (visited[i] == false) {
      starting.insert(i);
      dfs(graph, i, visited, starting);
    }
  }
  vector<int> ret;
  for (auto i : starting) {
    ret.push_back(i);
  }
  return ret;
}

int main() {
  {
    vector<vector<int>> graph{{1}, {2}, {0, 3}, {}, {5}, {4}, {3}};
    vector<int> min_nodes = minVertex(graph);
    cout << "Minimum set of node : ";
    for (auto u : min_nodes) {
      cout << u << " ";
    }
    cout << endl;
  }
}
