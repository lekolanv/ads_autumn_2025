#include <algorithm>
#include <iostream>
#include <vector>

struct Bord {
  int x;
  int y1;
  int y2;
  int t;
};

struct Node {
  int cnt;
  int len;
};

std::vector<Node> seg;
std::vector<int> ys;

void Build(int idx, int l, int r) {
  seg[idx] = {0, 0};
  if (l + 1 == r) {
    return;
  }
  int m = (l + r) / 2;
  Build(2 * idx + 1, l, m);
  Build(2 * idx + 2, m, r);
}

void Update(int idx, int l, int r, int ql, int qr, int v) {
  if (ql >= r or qr <= l) {
    return;
  }
  if (ql <= l and r <= qr) {
    seg[idx].cnt += v;
  } else {
    int m = (l + r) / 2;
    Update(2 * idx + 1, l, m, ql, qr, v);
    Update(2 * idx + 2, m, r, ql, qr, v);
  }
  if (seg[idx].cnt > 0) {
    seg[idx].len = ys[r] - ys[l];
  } else {
    if (l + 1 == r) {
      seg[idx].len = 0;
    } else {
      seg[idx].len = seg[2 * idx + 1].len + seg[2 * idx + 2].len;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<Bord> ev;
  std::vector<int> all_y;
  for (int i = 0; i < n; i++) {
    int x1;
    int y1;
    int x2;
    int y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    ev.push_back({x1, y1, y2, 1});
    ev.push_back({x2, y1, y2, -1});
    all_y.push_back(y1);
    all_y.push_back(y2);
  }
  std::sort(all_y.begin(), all_y.end());
  all_y.erase(std::unique(all_y.begin(), all_y.end()), all_y.end());
  ys = all_y;
  int m = ys.size();
  seg.resize(4 * m);
  Build(0, 0, m - 1);
  std::sort(ev.begin(), ev.end(),
            [](const Bord& a, const Bord& b) { return a.x < b.x; });
  long long res = 0;
  int px = ev[0].x;
  for (const auto& e : ev) {
    int dx = e.x - px;
    if (dx > 0) {
      res += (long long)dx * seg[0].len;
    }
    px = e.x;
    int i1 = std::lower_bound(ys.begin(), ys.end(), e.y1) - ys.begin();
    int i2 = std::lower_bound(ys.begin(), ys.end(), e.y2) - ys.begin();
    Update(0, 0, m - 1, i1, i2, e.t);
  }
  std::cout << res << std::endl;
}
