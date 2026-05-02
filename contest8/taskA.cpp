#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int to;
  int weight;
};

class Graph {
  int n_;
  std::vector<std::vector<Edge>> adj_;
  const long long cInf = 2009000999;

 public:
  Graph(int n) : n_(n), adj_(n) {}

  void AddEdge(int u, int v, int weight) {
    adj_[u].push_back({v, weight});
    adj_[v].push_back({u, weight});
  }

  void Solve(int s) {
    std::vector<long long> dist(n_, cInf);
    dist[s] = 0;
    std::priority_queue<std::pair<long long, int>,
                        std::vector<std::pair<long long, int>>,
                        std::greater<std::pair<long long, int>>>
        pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
      long long d = pq.top().first;
      int v = pq.top().second;
      pq.pop();
      if (d > dist[v]) {
        continue;
      }
      for (auto& edge : adj_[v]) {
        if (dist[v] + edge.weight < dist[edge.to]) {
          dist[edge.to] = dist[v] + edge.weight;
          pq.emplace(dist[edge.to], edge.to);
        }
      }
    }
    for (int i = 0; i < n_; ++i) {
      std::cout << dist[i] << " ";
    }
    std::cout << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t;
  std::cin >> t;
  while (t != 0) {
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
    int s;
    std::cin >> s;
    g.Solve(s);
    t--;
  }
}
