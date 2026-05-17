#include <iostream>
#include <vector>

struct Edge {
  int to;
};

class Graph {
  int n_;
  int k_;
  std::vector<std::vector<Edge>> adj_;
  std::vector<int> match_;
  std::vector<bool> used_;

  bool Dfs(int u) {
    if (used_[u]) {
      return false;
    }
    used_[u] = true;
    for (const auto& edge : adj_[u]) {
      int v = edge.to;
      if (match_[v] == -1 or Dfs(match_[v])) {
        match_[v] = u;
        return true;
      }
    }
    return false;
  }

 public:
  Graph(int n, int k) : n_(n), k_(k), adj_(n), match_(k, -1), used_(n, false) {}

  void AddEdge(int u, int v) { adj_[u].push_back({v}); }

  void Solve() {
    for (int i = 0; i < n_; ++i) {
      used_.assign(n_, false);
      Dfs(i);
    }
    std::vector<std::pair<int, int>> result;
    for (int v = 0; v < k_; ++v) {
      if (match_[v] != -1) {
        result.push_back({match_[v] + 1, v + 1});
      }
    }
    std::cout << result.size() << "\n";
    for (const auto& edge : result) {
      std::cout << edge.first << " " << edge.second << "\n";
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  int k;
  std::cin >> n >> k;
  Graph g(n, k);
  for (int i = 0; i < n; ++i) {
    int v;
    while (std::cin >> v && v != 0) {
      g.AddEdge(i, v - 1);
    }
  }
  g.Solve();
}
