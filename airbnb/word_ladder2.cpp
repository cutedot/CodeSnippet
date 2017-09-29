#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void buildGraph(string s, string t, vector<string> dict,
                unordered_map<string, vector<string>> &graph) {
  unordered_map<string, int> words; // word -> min distance from s to word
  for (auto w : dict) {
    words[w] = INT_MAX;
  }
  words[s] = INT_MAX;

  // do BFS
  queue<string> q;
  q.push(s);
  words[s] = 0; // 0 distance from s
  int max_dist = INT_MAX;

  while (!q.empty()) {
    string cur = q.front();
    q.pop();

    int dist = words[cur] + 1; // distance to its next neighbors
    if (dist > max_dist) {
      continue;
    }
    for (int i = 0; i < cur.size(); ++i) {
      for (int j = 0; j < 26; ++j) {
        // replace cur[i] with ('a'+j)
        string next = cur;
        next[i] = 'a' + j;
        if (cur[i] == next[i]) {
          continue;
        }
        // otherwise try to visit next
        if (words.find(next) != words.end()) {
          if (dist <= words[next]) {
            // add edge from cur -> next
            // cout << cur << " --> " << next << endl;
            graph[cur].push_back(next);
            if (dist < words[next]) {
              if (next.compare(t) == 0) {
                max_dist = dist;
              }
              words[next] = dist;
              q.push(next);
            }
          }
        }
      }
    }
  }
}

void backtrack(string &target, unordered_map<string, vector<string>> &graph,
               vector<string> &path, vector<vector<string>> &res) {
  string current = path.back();
  if (target.compare(current) == 0) {
    // found it
    res.push_back(path);
    return;
  }

  // try to explore more
  for (auto next : graph[current]) {
    path.push_back(next);
    backtrack(target, graph, path, res);
    path.pop_back();
  }
}

vector<vector<string>> findLadder(string s, string t, vector<string> dict) {
  unordered_map<string, vector<string>> graph;
  buildGraph(s, t, dict, graph);

  vector<vector<string>> res;
  vector<string> path;
  path.push_back(s);
  backtrack(t, graph, path, res);
  return res;
}

void printResult(vector<vector<string>> res) {
  for (auto p : res) {
    for (auto st : p) {
      cout << st << " ";
    }
    cout << endl;
  }
}

int main() {
  {
    cout << "Test 1" << endl;
    string s = "hit";
    string t = "cog";
    vector<string> dict{"hot", "dot", "dog", "lot", "log", "cog"};

    auto res = findLadder(s, t, dict);
    printResult(res);
  }
  {
    cout << "Test 2" << endl;
    string s = "hit";
    string t = "cog";
    vector<string> dict{"hot", "dot", "dog", "lot", "log"};

    auto res = findLadder(s, t, dict);
    printResult(res);
  }
}
