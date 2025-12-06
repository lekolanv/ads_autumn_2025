#include <iostream>
#include <tuple>
#include <vector>

class FT {
 public:
  FT(int n) : tree_(n + 1, 0) {}

  void Update(int idx, int delta) {
    int i = idx;
    while (i < static_cast<int>(tree_.size())) {
      tree_[i] += delta;
      i += i & -i;
    }
  }

  int Q(int idx) {
    int s = 0;
    int i = idx;
    while (i > 0) {
      s += tree_[i];
      i -= i & -i;
    }
    return s;
  }

  int RQ(int l, int r) {
    if (l > r) {
      return 0;
    }
    return Q(r) - Q(l - 1);
  }

 private:
  std::vector<int> tree_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  std::vector<std::tuple<int, int, int, int>> qr(q);
  std::vector<std::vector<std::pair<int, int>>> events(n + 1);
  for (int i = 0; i < q; i++) {
    int l;
    int r;
    int x;
    int y;
    std::cin >> l >> r >> x >> y;
    qr[i] = {l, r, x, y};
    events[l - 1].emplace_back(i, -1);
    events[r].emplace_back(i, 1);
  }
  FT fenw(n);
  std::vector<int> ans(q, 0);
  for (int k = 0; k <= n; k++) {
    if (k >= 1) {
      fenw.Update(a[k], 1);
    }
    for (auto [id, coef] : events[k]) {
      auto [l, r, x, y] = qr[id];
      int sum = fenw.RQ(x, y);
      ans[id] += coef * sum;
    }
  }
  for (int i = 0; i < q; i++) {
    std::cout << ans[i] << "\n";
  }
}
