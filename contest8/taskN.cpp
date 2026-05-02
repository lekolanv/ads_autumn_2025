#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int u;
  int v;
  int weight;
  bool operator<(const Edge& other) const { return weight < other.weight; }
};

class DSU {
  std::vector<int> parent_;

 public:
  DSU(int n) : parent_(n + 1) {
    for (int i = 0; i <= n; ++i) {
      parent_[i] = i;
    }
  }

  int Find(int i) {
    if (parent_[i] == i) {
      return i;
    }
    return parent_[i] = Find(parent_[i]);
  }

  bool Unite(int i, int j) {
    int root_i = Find(i);
    int root_j = Find(j);
    if (root_i != root_j) {
      parent_[root_i] = root_j;
      return true;
    }
    return false;
  }
};

class Graph {
  int n_;
  std::vector<Edge> edges_;

 public:
  Graph(int n) : n_(n) {}

  void AddEdge(int u, int v, int c) { edges_.push_back({u, v, c}); }

  long long GetMSTWeight() {
    std::sort(edges_.begin(), edges_.end());
    DSU dsu(n_);
    long long total_weight = 0;
    int edges_count = 0;
    for (const auto& edge : edges_) {
      if (dsu.Unite(edge.u, edge.v)) {
        total_weight += edge.weight;
        edges_count++;
        if (edges_count == n_ - 1) {
          break;
        }
      }
    }
    return total_weight;
  }
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    g.AddEdge(u, v, c);
  }
  std::cout << g.GetMSTWeight() << std::endl;
}
