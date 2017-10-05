#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void buildGraph(vector<string> &words,
                unordered_map<char, unordered_set<char>> &graph) {
  for (int i = 0; i < words.size() - 1; ++i) {
    // adding edge
    // comparing words[i] and words[i+1]
    for (int p = 0; p < words[i].size() && p < words[i + 1].size(); ++p) {
      if (words[i][p] != words[i + 1][p]) {
        // adding edge from words[i][p] -> words[i+1][p]
        graph[words[i][p]].insert(words[i + 1][p]);

        cout << words[i][p] << "->" << words[i + 1][p] << endl;

        break;
      } else {
        // XXX: this is tricky, what it actually does is insert and initialize
        // kv pair if key is present in the map. And this is VERY VERY important
        // to get the full vertex set
        graph[words[i][p]];
      }
    }
  }
}

string topoSort(unordered_map<char, unordered_set<char>> &graph) {
  string res = "";
  unordered_map<char, int> indeg;
  queue<char> q;
  // init
  for (auto m : graph) {
    // XXX: does the same initialize-if-not-present business
    indeg[m.first];
    for (auto v : m.second) {
      indeg[v]++;
    }
  }
  for (auto m : indeg) {
    cout << m.first << " : " << m.second << endl;
    if (m.second == 0) {
      q.push(m.first);
    }
  }

  while (!q.empty()) {
    char u = q.front();
    q.pop();
    res += u;
    for (auto i : graph[u]) {
      indeg[i]--;
      if (indeg[i] == 0) {
        q.push(i);
      }
    }
  }
  return res;
}

string alienOrder(vector<string> &words) {
  unordered_map<char, unordered_set<char>> graph;

  buildGraph(words, graph);
  return topoSort(graph);
}

// alien dictionary
int main() {
  {
    // TEST 1
    cout << "TEST 1" << endl;
    vector<string> words{"wrt", "wrf", "er", "ett", "rftt"};
    cout << alienOrder(words) << endl;
  }
  {
    // TEST 2
    cout << "TEST 2" << endl;
    vector<string> words{"z", "x"};
    cout << alienOrder(words) << endl;
  }
  {
    // TEST 3
    cout << "TEST 3" << endl;
    vector<string> words{"z", "x", "z"};
    cout << alienOrder(words) << endl;
  }
}
