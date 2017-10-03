#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

//
// Find minimum number of node to reach all nodes in a directed graph.
// XXX: YOU REALLY EXPECT CANDIDATE TO FINISH IT BUG-FREE IN 30 MIN?
//
// first pass DFS on the reversed graph, to produce the post DFS order
void dfs0(vector<vector<int>> &graph, int u, vector<bool> &vis,
          stack<int> &st) {
  // visited u
  vis[u] = true;
  // visite neighbors
  for (auto v : graph[u]) {
    if (!vis[v]) {
      dfs0(graph, v, vis, st);
    }
  }
  st.push(u);
}

// second pass DFS on the original graph
void dfs1(vector<vector<int>> &graph, int u, vector<int> &cc, int cnt) {
  cc[u] = cnt;
  for (auto v : graph[u]) {
    if (cc[v] == -1) {
      dfs1(graph, v, cc, cnt);
    }
  }
}

void reverseGraph(vector<vector<int>> &graph, vector<vector<int>> &reversed) {
  for (int u = 0; u < graph.size(); ++u) {
    for (int i = 0; i < graph[u].size(); ++i) {
      int v = graph[u][i];
      // reverse u->v
      reversed[v].push_back(u);
    }
  }
}

vector<int> minNumNodes(vector<vector<int>> &graph) {
  vector<int> ret;
  // compute the reverse graph
  int num_nodes = graph.size();
  vector<int> cc(num_nodes, -1);
  vector<bool> vis(num_nodes, false);
  stack<int> st;
  int cnt = 0;

  // calculate the reversed graph
  vector<vector<int>> reversed(graph.size(), vector<int>());
  reverseGraph(graph, reversed);
  // first pass DFS
  for (int i = 0; i < reversed.size(); ++i) {
    if (!vis[i]) {
      dfs0(reversed, i, vis, st);
    }
  }

  // second pass DFS to calculate the connected component
  while (!st.empty()) {
    int u = st.top();
    st.pop();
    cout << u << endl;
    if (cc[u] == -1) {
      dfs1(graph, u, cc, cnt);
      ++cnt;
    }
  }

  cout << "# of SCC:  " << cnt << endl;

  // the new graph
  vector<set<int>> dag(cnt, set<int>());
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j) {
      int u = i;
      int v = graph[i][j];

      // add the edge to the new graph
      int uu = cc[u];
      int vv = cc[v];
      if (uu != vv) {
        // add edge uu -> vv
        dag[uu].insert(vv);
      }
    }
  }

  // no we have a dag, find all zero indegree nodes and those are the minimum
  // set of nodes
  vector<int> indeg(cnt, 0);
  for (int u = 0; u < cnt; ++u) {
    for (auto v : dag[u]) {
      ++indeg[v];
    }
  }

  for (int i = 0; i < cnt; ++i) {
    if (indeg[i] == 0) {
      // add all nodes in the SCC[i]
      for (int j = 0; j < graph.size(); ++j) {
        if (cc[j] == i) {
          ret.push_back(j);
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
