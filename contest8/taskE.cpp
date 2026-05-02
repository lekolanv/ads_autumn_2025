#include <algorithm>
#include <iostream>
#include <vector>

const int cBig = 100000;

struct Edge {
  int u;
  int v;
  int weight;
};

class Graph {
  int n_;
  std::vector<Edge> edges_;

 public:
  Graph(int n) : n_(n) {}

  void AddEdge(int u, int v, int weight) { edges_.push_back({u, v, weight}); }

  void Solve() {
    std::vector<long long> dist(n_ + 1, 0);
    std::vector<int> parent(n_ + 1, -1);
    int last_v;
    last_v = -1;
    for (int i = 0; i < n_; ++i) {
      last_v = -1;
      for (const auto& edge : edges_) {
        if (dist[edge.v] > dist[edge.u] + edge.weight) {
          dist[edge.v] = dist[edge.u] + edge.weight;
          parent[edge.v] = edge.u;
          last_v = edge.v;
        }
      }
    }
    if (last_v == -1) {
      std::cout << "NO" << std::endl;
    } else {
      int start_node;
      start_node = last_v;
      for (int i = 0; i < n_; ++i) {
        start_node = parent[start_node];
      }
      std::vector<int> cycle;
      int current;
      current = start_node;
      while (true) {
        cycle.push_back(current);
        if (current == start_node && cycle.size() > 1) {
          break;
        }
        current = parent[current];
      }
      std::reverse(cycle.begin(), cycle.end());
      std::cout << "YES" << std::endl;
      std::cout << cycle.size() << std::endl;
      for (int i = 0; i < (int)cycle.size(); ++i) {
        std::cout << cycle[i] << " ";
      }
      std::cout << std::endl;
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  Graph g(n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int weight;
      std::cin >> weight;
      if (weight != cBig) {
        g.AddEdge(i, j, weight);
      }
    }
  }
  g.Solve();
}
