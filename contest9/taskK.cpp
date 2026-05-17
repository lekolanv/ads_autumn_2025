#include <iostream>
#include <vector>

struct Edge {
  int to;
  int capacity;
  int flow;
  int cost;
  int rev;
};

struct Queue {
  std::vector<int> data;
  int head = 0;
  int tail = 0;
  int size = 0;

  Queue(int n) : size(n + 1) { data.resize(size); }
  void Push(int val) {
    data[tail % size] = val;
    tail++;
  }
  void Pop() { head++; }
  int Front() { return data[head % size]; }
  bool Empty() const { return head == tail; }
};

class Graph {
  int n_nodes_;
  std::vector<std::vector<Edge>> adj_;
  std::vector<long long> dist_;
  std::vector<int> edge_from_node_;
  std::vector<int> edge_from_idx_;
  const long long cInf = 1e18;
  const int cInt = 2000000000;

  static long long Min(long long a, long long b) {
    if (a < b) {
      return a;
    }
    return b;
  }

 public:
  Graph(int n) : n_nodes_(n), adj_(n + 1) {}

  void AddEdge(int u, int v, int cap, int cost) {
    adj_[u].push_back({v, cap, 0, cost, (int)adj_[v].size()});
    adj_[v].push_back({u, 0, 0, -cost, (int)adj_[u].size() - 1});
  }

  long long Solve(int s, int t) {
    long long min_total_cost = 0;
    while (true) {
      dist_.assign(n_nodes_ + 1, cInf);
      edge_from_node_.assign(n_nodes_ + 1, -1);
      edge_from_idx_.assign(n_nodes_ + 1, -1);
      std::vector<bool> in_queue(n_nodes_ + 1, false);
      Queue q(n_nodes_ + 1);
      dist_[s] = 0;
      q.Push(s);
      in_queue[s] = true;
      while (!q.Empty()) {
        int u = q.Front();
        q.Pop();
        in_queue[u] = false;
        for (int i = 0; i < (int)adj_[u].size(); ++i) {
          Edge& e = adj_[u][i];
          if (e.capacity > e.flow && dist_[e.to] > dist_[u] + e.cost) {
            dist_[e.to] = dist_[u] + e.cost;
            edge_from_node_[e.to] = u;
            edge_from_idx_[e.to] = i;
            if (!in_queue[e.to]) {
              q.Push(e.to);
              in_queue[e.to] = true;
            }
          }
        }
      }
      if (dist_[t] == cInf) {
        break;
      }
      long long push = cInt;
      for (int v = t; v != s; v = edge_from_node_[v]) {
        int u = edge_from_node_[v];
        int idx = edge_from_idx_[v];
        push = Min(push, (long long)adj_[u][idx].capacity - adj_[u][idx].flow);
      }
      for (int v = t; v != s; v = edge_from_node_[v]) {
        int u = edge_from_node_[v];
        int idx = edge_from_idx_[v];
        int r_idx = adj_[u][idx].rev;
        adj_[u][idx].flow += (int)push;
        adj_[v][r_idx].flow -= (int)push;
        min_total_cost += push * adj_[u][idx].cost;
      }
    }
    return min_total_cost;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int c;
    int w;
    std::cin >> u >> v >> c >> w;
    g.AddEdge(u, v, c, w);
  }
  std::cout << g.Solve(1, n) << "\n";
}
