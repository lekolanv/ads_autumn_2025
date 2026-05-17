#include <iostream>
#include <vector>

struct Edge {
  int to;
  int capacity;
  int flow;
  int rev;
  int id;
};

struct Queue {
  std::vector<int> data;
  int head = 0;
  int tail = 0;
  Queue(int size) { data.resize(size); }
  void Push(int val) { data[tail++] = val; }
  void Pop() { head++; }
  int Front() { return data[head]; }
  bool Empty() const { return head == tail; }
};

class Graph {
  int n_;
  std::vector<std::vector<Edge>> adj_;
  std::vector<int> dist_;
  std::vector<int> back_edge_idx_;
  const int cInf = 2000000000;

  static int Min(int a, int b) {
    if (a < b) {
      return a;
    }
    return b;
  }

  bool FindPath(int s, int t) {
    dist_.assign(n_ + 1, cInf);
    back_edge_idx_.assign(n_ + 1, -1);
    Queue q(n_ + 1);
    dist_[s] = 0;
    q.Push(s);
    while (!q.Empty()) {
      int u = q.Front();
      q.Pop();
      for (int i = 0; i < (int)adj_[u].size(); ++i) {
        Edge& e = adj_[u][i];
        if (dist_[e.to] == cInf && e.capacity > e.flow) {
          dist_[e.to] = dist_[u] + 1;
          back_edge_idx_[e.to] = e.rev;
          q.Push(e.to);
        }
      }
    }
    return dist_[t] != cInf;
  }

  void MarkSide(int s, std::vector<bool>& vis) {
    Queue q(n_ + 1);
    vis[s] = true;
    q.Push(s);
    while (!q.Empty()) {
      int u = q.Front();
      q.Pop();
      for (const auto& e : adj_[u]) {
        if (!vis[e.to] && e.capacity > e.flow) {
          vis[e.to] = true;
          q.Push(e.to);
        }
      }
    }
  }

  void Print(const std::vector<bool>& vis, long long max_flow) {
    std::vector<int> cut_ids;
    for (int i = 1; i <= n_; ++i) {
      if (!vis[i]) {
        continue;
      }
      for (const auto& e : adj_[i]) {
        if (vis[e.to]) {
          continue;
        }
        bool dup = false;
        for (int id : cut_ids) {
          if (id == e.id) {
            dup = true;
            break;
          }
        }
        if (!dup) {
          cut_ids.push_back(e.id);
        }
      }
    }
    for (int i = 0; i < (int)cut_ids.size(); ++i) {
      for (int j = i + 1; j < (int)cut_ids.size(); ++j) {
        if (cut_ids[i] > cut_ids[j]) {
          int tmp = cut_ids[i];
          cut_ids[i] = cut_ids[j];
          cut_ids[j] = tmp;
        }
      }
    }
    std::cout << cut_ids.size() << " " << max_flow << "\n";
    for (int i = 0; i < (int)cut_ids.size(); ++i) {
      if (i > 0) {
        std::cout << " ";
      }
      std::cout << cut_ids[i];
    }
    std::cout << "\n";
  }

 public:
  Graph(int n) : n_(n), adj_(n + 1) {}

  void AddEdge(int u, int v, int cap, int id) {
    adj_[u].push_back({v, cap, 0, (int)adj_[v].size(), id});
    adj_[v].push_back({u, cap, 0, (int)adj_[u].size() - 1, id});
  }

  void Solve(int s, int t) {
    long long max_flow = 0;
    while (FindPath(s, t)) {
      int push = cInf;
      int curr = t;
      while (curr != s) {
        int r_idx = back_edge_idx_[curr];
        int u = adj_[curr][r_idx].to;
        int d_idx = adj_[curr][r_idx].rev;
        push = Min(push, adj_[u][d_idx].capacity - adj_[u][d_idx].flow);
        curr = u;
      }
      curr = t;
      while (curr != s) {
        int r_idx = back_edge_idx_[curr];
        int u = adj_[curr][r_idx].to;
        int d_idx = adj_[curr][r_idx].rev;
        adj_[u][d_idx].flow += push;
        adj_[curr][r_idx].flow -= push;
        curr = u;
      }
      max_flow += push;
    }
    std::vector<bool> vis(n_ + 1, false);
    MarkSide(s, vis);
    Print(vis, max_flow);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n);
  for (int i = 1; i <= m; ++i) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    if (u != v) {
      g.AddEdge(u, v, c, i);
    }
  }
  g.Solve(1, n);
}
