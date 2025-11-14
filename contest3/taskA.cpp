#include <iostream>
#include <vector>

struct Pair {
  int first;
  int second;
  Pair(int f = 0, int s = 0) : first(f), second(s) {}
};

Pair Combine(const Pair& a, const Pair& b) {
  int vals[4] = {a.first, a.second, b.first, b.second};
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (vals[j] < vals[i]) {
        int temp = vals[i];
        vals[i] = vals[j];
        vals[j] = temp;
      }
    }
  }
  int min1 = vals[0];
  int min2 = -1;
  for (int i = 1; i < 4; i++) {
    if (vals[i] != min1) {
      min2 = vals[i];
      break;
    }
  }
  return Pair(min1, min2);
}

class SparseTable {
 private:
  std::vector<std::vector<Pair>> st_;
  std::vector<int> log_;
  int n_;

 public:
  SparseTable(const std::vector<int>& arr) {
    n_ = arr.size();
    log_.resize(n_ + 1);
    log_[1] = 0;
    for (int i = 2; i <= n_; i++) {
      log_[i] = log_[i / 2] + 1;
    }
    int k = log_[n_] + 1;
    st_.resize(n_, std::vector<Pair>(k));
    for (int i = 0; i < n_; i++) {
      st_[i][0] = Pair(arr[i], arr[i]);
    }
    for (int j = 1; j < k; j++) {
      for (int i = 0; i + (1 << j) <= n_; i++) {
        st_[i][j] = Combine(st_[i][j - 1], st_[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  Pair Query(int l, int r) {
    int j = log_[r - l + 1];
    return Combine(st_[l][j], st_[r - (1 << j) + 1][j]);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  SparseTable st(arr);
  while (q != 0) {
    q--;
    int l;
    int r;
    std::cin >> l >> r;
    l--;
    r--;
    Pair result = st.Query(l, r);
    std::cout << result.second << "\n";
  }
}
