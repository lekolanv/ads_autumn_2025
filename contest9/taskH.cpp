#include <iostream>
#include <vector>

struct Edge {
  int to;
  long long capacity;
  long long flow;
  int rev;
  int id;
};

struct Queue {
  std::vector<int> data;
  int head = 0;
  int tail = 0;

  Queue(int n) { data.resize(n + 1); }
  void Push(int val) {
    data[tail] = val;
    tail++;
  }
  void Pop() { head++; }
  int Front() { return data[head]; }
  bool Empty() const { return head == tail; }
};

class Graph {
  int n_;
  std::vector<std::vector<Edge>> adj_;
  std::vector<int> level_;
  std::vector<int> ptr_;
  const long long cInf = 1e18;
  const int cMaxBit = 30;

  static long long Min(long long a, long long b) {
    if (a < b) {
      return a;
    }
    return b;
  }

  bool Bfs(int s, int t, long long lim) {
    level_.assign(n_ + 1, -1);
    level_[s] = 0;
    Queue q(n_);
    q.Push(s);
    while (!q.Empty()) {
      int u = q.Front();
      q.Pop();
      for (const auto& e : adj_[u]) {
        if (level_[e.to] == -1 && e.capacity - e.flow >= lim) {
          level_[e.to] = level_[u] + 1;
          q.Push(e.to);
        }
      }
    }
    return level_[t] != -1;
  }

  long long Dfs(int u, int t, long long pushed, long long lim) {
    if (pushed == 0 || u == t) {
      return pushed;
    }
    for (int& i = ptr_[u]; i < (int)adj_[u].size(); ++i) {
      int tr = adj_[u][i].to;
      int r_idx = adj_[u][i].rev;
      long long avail = adj_[u][i].capacity - adj_[u][i].flow;
      if (level_[u] + 1 != level_[tr] || avail < lim) {
        continue;
      }
      long long res = Dfs(tr, t, Min(pushed, avail), lim);
      if (res == 0) {
        continue;
      }
      adj_[u][i].flow += res;
      adj_[tr][r_idx].flow -= res;
      return res;
    }
    return 0;
  }

 public:
  Graph(int n) : n_(n), adj_(n + 1) {}

  void AddEdge(int u, int v, int cap, int id) {
    Edge dir = {v, (long long)cap, 0, (int)adj_[v].size(), id};
    Edge rev = {u, 0, 0, (int)adj_[u].size(), -1};
    adj_[u].push_back(dir);
    adj_[v].push_back(rev);
  }

  void Solve(int s, int t, int m) {
    long long total_flow = 0;
    for (long long lim = (1LL << cMaxBit); lim >= 1; lim >>= 1) {
      while (Bfs(s, t, lim)) {
        ptr_.assign(n_ + 1, 0);
        while (long long pushed = Dfs(s, t, cInf, lim)) {
          total_flow += pushed;
        }
      }
    }
    std::cout << total_flow << "\n";
    std::vector<long long> res_f(m);
    for (int u = 1; u <= n_; ++u) {
      for (const auto& e : adj_[u]) {
        if (e.id != -1) {
          res_f[e.id] = e.flow;
        }
      }
    }
    for (int i = 0; i < m; ++i) {
      std::cout << res_f[i] << "\n";
    }
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
    std::cin >> u >> v >> c;
    g.AddEdge(u, v, c, i);
  }
  g.Solve(1, n, m);
  return 0;
}
