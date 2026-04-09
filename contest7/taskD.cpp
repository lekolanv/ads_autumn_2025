#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  std::vector<std::vector<int>> adj_;
  std::vector<std::vector<int>> rev_adj_;
  std::vector<int> order_;
  std::vector<int> comp_;
  std::vector<bool> visited_;
  int V_;
  int comp_count_;

 public:
  Graph(int vertices)
      : adj_(vertices),
        rev_adj_(vertices),
        comp_(vertices, -1),
        visited_(vertices, false),
        V_(vertices),
        comp_count_(0) {}

  void Dfs1(int v) {
    visited_[v] = true;
    for (int to : adj_[v]) {
      if (!visited_[to]) {
        Dfs1(to);
      }
    }
    order_.push_back(v);
  }

  void AddEdge(int u, int v) {
    adj_[u - 1].push_back(v - 1);
    rev_adj_[v - 1].push_back(u - 1);
  }

  void Dfs2(int v, int c) {
    comp_[v] = c;
    for (int to : rev_adj_[v]) {
      if (comp_[to] == -1) {
        Dfs2(to, c);
      }
    }
  }

  void Solve() {
    for (int i = 0; i < V_; ++i) {
      if (!visited_[i]) {
        Dfs1(i);
      }
    }
    std::reverse(order_.begin(), order_.end());
    for (int v : order_) {
      if (comp_[v] == -1) {
        comp_count_++;
        Dfs2(v, comp_count_);
      }
    }
    std::cout << comp_count_ << "\n";
    for (int c : comp_) {
      std::cout << c << " ";
    }
    std::cout << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    g.AddEdge(u, v);
  }
  g.Solve();
}
