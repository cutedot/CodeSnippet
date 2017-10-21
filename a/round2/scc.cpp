#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void reverseGraph(vector<vector<int>> &graph, vector<vector<int>> &rev) {
  for (int u = 0; u < graph.size(); ++u) {
    for (auto v : graph[u]) {
      // u->v --> v->u
      rev[v].push_back(u);
    }
  }
}

void preDfs(vector<vector<int>> &graph, vector<bool> &visited, int u,
            vector<int> &sequence) {
  if (visited[u])
    return;
  // visit u
  visited[u] = true;
  for (auto v : graph[u]) {
    preDfs(graph, visited, v, sequence);
  }
  sequence.push_back(u);
}

void Dfs(vector<vector<int>> &graph, vector<int> &scc, vector<bool> &visited,
         int u, int id) {
  if (visited[u])
    return;
  cout << u << " in cluster " << id << endl;
  scc[u] = id;
  visited[u] = true;
  for (auto v : graph[u]) {
    Dfs(graph, scc, visited, v, id);
  }
}

vector<int> minNumNodes(vector<vector<int>> &graph) {
  vector<vector<int>> rev(graph.size(), vector<int>());
  reverseGraph(graph, rev);
  vector<int> sequence;
  vector<bool> pre_vis(graph.size(), false);
  for (int i = 0; i < graph.size(); ++i) {
    preDfs(rev, pre_vis, i, sequence);
  }
  reverse(sequence.begin(), sequence.end());
  for (auto i : sequence) {
    cout << i << " ";
  }
  cout << endl;
  vector<int> scc(graph.size(), 0);
  vector<bool> visited(graph.size(), false);
  int id = 0;
  for (auto i : sequence) {
    if (visited[i]) {
      continue;
    }
    Dfs(graph, scc, visited, i, id);
    ++id;
  }

  // generate new graph
  vector<set<int>> new_graph(id, set<int>());
  for (int u = 0; u < graph.size(); ++u) {
    for (int v = 0; v < graph[u].size(); ++v) {
      if (scc[u] != scc[v]) {
        new_graph[scc[u]].insert(scc[v]);
      }
    }
  }

  cout << new_graph.size() << endl;
  // output a topo order
  vector<int> indeg(new_graph.size(), 0);
  for (int u = 0; u < new_graph.size(); ++u) {
    for (auto v : new_graph[u]) {
      // an edge u -> v
      indeg[v]++;
    }
  }
  vector<int> ret;
  for (int i = 0; i < new_graph.size(); ++i) {
    if (indeg[i] == 0) {
      for (int k = 0; k < scc.size(); ++k) {
        if (scc[k] == i) {
          ret.push_back(k);
          break;
        }
      }
    }
  }
  return ret;
}

int main() {
  {
    vector<vector<int>> graph{{1}, {2}, {0, 3}, {}, {5}, {4}, {3}};
    vector<int> min_nodes = minNumNodes(graph);
    cout << "Minimum set of node : ";
    for (auto u : min_nodes) {
      cout << u << " ";
    }
    cout << endl;
  }
}
