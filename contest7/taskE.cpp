#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  struct Edge {
    int u;
    int v;
    int id;
  };
  struct AdjEdge {
    int to;
    int id;
  };
  std::vector<std::vector<AdjEdge>> adj_;
  std::vector<Edge> all_edges_;
  std::vector<bool> is_bridge_;
  int V_;
  int M_;
 public:
  Graph(int n, int m) : adj_(n), is_bridge_(m + 1, false), V_(n), M_(m) {}
  void AddEdge(int u, int v, int id) {
    adj_[u - 1].push_back({v - 1, id});
    adj_[v - 1].push_back({u - 1, id});
    all_edges_.push_back({u - 1, v - 1, id});
  }

  void FindBridges(int v, int p_edge_id, std::vector<int>& tin,
                   std::vector<int>& low, int& timer) {
    tin[v] = low[v] = timer++;
    for (auto& edge : adj_[v]) {
      if (edge.id == p_edge_id) {
        continue;
      }
      if (tin[edge.to] != -1) {
        low[v] = std::min(low[v], tin[edge.to]);
      } else {
        FindBridges(edge.to, edge.id, tin, low, timer);
        low[v] = std::min(low[v], low[edge.to]);
        if (low[edge.to] > tin[v]) {
          is_bridge_[edge.id] = true;
        }
      }
    }
  }

  void Decompose(int v, int c, std::vector<int>& comp) {
    comp[v] = c;
    for (auto& edge : adj_[v]) {
      if (!is_bridge_[edge.id] && comp[edge.to] == -1) {
        Decompose(edge.to, c, comp);
      }
    }
  }

  void Solve() {
    std::vector<int> tin(V_, -1), low(V_, -1);
    int timer = 0;
    for (int i = 0; i < V_; ++i) {
      if (tin[i] == -1) FindBridges(i, -1, tin, low, timer);
    }
    std::vector<int> comp(V_, -1);
    int comp_count = 0;
    for (int i = 0; i < V_; ++i) {
      if (comp[i] == -1) Decompose(i, comp_count++, comp);
    }
    if (comp_count <= 1) {
      std::cout << 0 << "\n";
      return;
    }
    std::vector<int> degree(comp_count, 0);
    for (const auto& e : all_edges_) {
      if (is_bridge_[e.id]) {
        degree[comp[e.u]]++;
        degree[comp[e.v]]++;
      }
    }
    int leaves = 0;
    for (int d : degree) {
      if (d == 1) leaves++;
    }
    std::cout << (leaves + 1) / 2 << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    g.AddEdge(u, v, i + 1);
  }
  g.Solve();
}
