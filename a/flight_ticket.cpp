#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct ticket {
  int departure;
  int arrival;
  int cost;
  ticket(int d, int a, int c) : departure(d), arrival(a), cost(c) {}
};

struct info {
  int arrival;
  int cost;
  info() : arrival(-1), cost(-1) {}
};

void buildGraph(vector<ticket> &tickets,
                unordered_map<int, vector<info>> &graph) {
  for (auto t : tickets) {
    info t_info;
    t_info.arrival = t.arrival;
    t_info.cost = t.cost;

    graph[t.departure].push_back(t_info);
  }
}

// min cost from s -> t
int flighTicket(vector<ticket> &tickets, int k, int s, int t) {
  unordered_map<int, vector<info>> graph;
  buildGraph(tickets, graph);

  vector<info> stops[2];
  bool cur = false;
  info t_info;
  t_info.arrival = s;
  t_info.cost = 0;
  stops[cur].push_back(t_info);

  int min_cost = INT_MAX;
  for (int i = 0; i < k; ++i) {
    for (auto s : stops[cur]) {
      // find the next stop
      if (s.arrival == t) {
        // arrive at destination
        min_cost = min(min_cost, s.cost);
      } else {
        for (auto next : graph[s.arrival]) {
          info next_info;
          next_info.arrival = next.arrival;
          next_info.cost = s.cost + next.cost;
          stops[!cur].push_back(next_info);
        }
      }
    }
    // next level
    cur = !cur;
    stops[!cur].clear();
  }

  return min_cost;
}

int main() {
  {
    // Test 1
    cout << "Test 1" << endl;
    vector<ticket> tickets{
        {1, 2, 5}, {1, 3, 1}, {2, 3, 1}, {3, 4, 1}, {4, 2, 1}};

    cout << flighTicket(tickets, 4, 1, 2) << endl;
  }
}
