#include <cstdint>
#include <iostream>
#include <vector>

int Findr(uint64_t d) {
  int c;
  c = 0;
  const int cW = 10;
  while (d != 0) {
    d /= cW;
    c++;
  }
  return c;
}

uint64_t FindMax(const std::vector<uint64_t>& a) {
  int n = a.size();
  uint64_t max = a[0];
  for (int i = 1; i < n; ++i) {
    if (a[i] > max) {
      max = a[i];
    }
  }
  return max;
}

void StableDigitSort(std::vector<uint64_t>& a, uint64_t divisor) {
  int n = a.size();
  const int cW = 10;
  std::vector<uint64_t> res(n);
  std::vector<int> count(cW, 0);
  for (int i = 0; i < n; i++) {
    int digit = (a[i] / divisor) % cW;
    count[digit]++;
  }
  for (int i = 1; i < cW; ++i) {
    count[i] += count[i - 1];
  }
  for (int i = n - 1; i >= 0; --i) {
    int digit = (a[i] / divisor) % cW;
    res[count[digit] - 1] = a[i];
    count[digit]--;
  }
  for (int i = 0; i < n; ++i) {
    a[i] = res[i];
  }
}

void LSD(std::vector<uint64_t>& a) {
  const int cW = 10;
  uint64_t max = FindMax(a);
  int r = Findr(max);
  uint64_t divisor = 1;
  for (int i = 0; i < r; ++i) {
    StableDigitSort(a, divisor);
    divisor *= cW;
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<uint64_t> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  LSD(a);
  for (auto x : a) {
    std::cout << x << " ";
  }
}
