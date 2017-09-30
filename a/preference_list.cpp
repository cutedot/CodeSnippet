#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

void buildGraph(vector<vector<int>> preference, int n,
                unordered_map<int, vector<int>> &graph, vector<int> &indeg) {
  // for two consecutive item in one person's preference list, <u, v>, will have
  // an edge u -> v
  for (auto p : preference) {
    if (p.size() < 2) {
      continue;
    }
    for (int i = 0; i < p.size() - 1; ++i) {
      // add edge p[i] - > p[i+1]
      ++indeg[p[i + 1]];
      graph[p[i]].push_back(p[i + 1]);
    }
  }
}

vector<int> topoSort(unordered_map<int, vector<int>> &graph,
                     vector<int> &indeg) {
  vector<int> res;
  queue<int> q;

  // find all zero in-degree nodes and add to queue
  for (int i = 0; i < indeg.size(); ++i) {
    if (indeg[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    // remove cur
    res.push_back(cur);

    // remove all outgoing edges from cur
    for (auto dest : graph[cur]) {
      --indeg[dest];
      if (indeg[dest] == 0) {
        q.push(dest);
      }
    }
  }

  return res;
}

vector<int> preferenceList(vector<vector<int>> preference, int n) {
  // topological sort
  // 1. create graph
  unordered_map<int, vector<int>> graph;
  vector<int> indeg(n, 0);

  buildGraph(preference, n, graph, indeg);

  return topoSort(graph, indeg);
}

int main() {
  {
    // TEST 1
    cout << "Test 1" << endl;
    vector<vector<int>> prefList{{4, 1, 3}, {4, 0}, {5, 2, 3}};

    auto res = preferenceList(prefList, 6);

    for (auto i : res) {
      cout << i;
    }
    cout << endl;
  }
}
