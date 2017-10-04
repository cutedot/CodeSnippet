#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

//
// Here I intentionally use map and set to store the nodes because these nodes
// can be discrete.
//
int findRoot(unordered_map<int, int> &cc, int u) {
  int r = u;
  while (cc[r] != r) {
    r = cc[r];
  }
  return r;
}

bool quickUnion(unordered_map<int, int> &cc, int u, int v) {
  // union them by linking root of v to u
  int ru = findRoot(cc, u);
  int rv = findRoot(cc, v);
  if (ru == rv) {
    return false; // they are already in the same component
  }
  // otherwise, change the root of v to be root of u
  cc[rv] = ru;
  return true;
}
int connectedComponent(unordered_map<int, unordered_set<int>> &graph) {
  int num_component = graph.size();
  // first build a cc map from node -> it's parent
  unordered_map<int, int> cc;
  // initial state
  for (auto &p : graph) {
    int u = p.first;
    cc[u] = u;
  }

  // union find
  // traverse all edges
  for (auto &p : graph) {
    int u = p.first;
    for (auto &v : p.second) {
      bool st = quickUnion(cc, u, v);
      if (st) {
        --num_component;
      }
    }
  }
  return num_component;
}

int main() {
  {
    unordered_map<int, unordered_set<int>> graph{
        {0, {1, 6}}, {1, {0, 5, 6}}, {6, {0, 1}}, {5, {1}},
        {4, {}},     {10, {11}},     {11, {10}}};
    cout << connectedComponent(graph) << endl;
  }
}
