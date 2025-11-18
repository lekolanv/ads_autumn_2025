#include <cstdint>
#include <iostream>
#include <vector>

const long cT = 10;
const long cW = 10'000'000;
const long cL = 4321;
const int cR = 123;
const int cE = 45;

long MedianFive(std::vector<long>& a, long l, long r) {
  for (long i = l + 1; i <= r; i++) {
    long key = a[i];
    long j = i - 1;
    while (j >= l and a[j] > key) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = key;
  }
  return l + (r - l) / 2;
}

long MedianMedians(std::vector<long>& a, long l, long r) {
  long n = r - l + 1;
  if (n <= 5) {
    long median_pos = MedianFive(a, l, r);
    return median_pos;
  }
  long numgr = 0;
  for (long i = l; i <= r; i += 5) {
    long sub_r = (i + 4 <= r) ? i + 4 : r;
    long median_pos = MedianFive(a, i, sub_r);
    std::swap(a[median_pos], a[l + numgr]);
    numgr++;
  }
  return MedianMedians(a, l, l + numgr - 1);
}

int32_t Partition(std::vector<long>& a, long l, long r) {
  long median_pos = MedianMedians(a, l, r);
  std::swap(a[median_pos], a[r]);

  long pivot = a[r];
  long i = l;
  for (long j = l; j < r; j++) {
    if (a[j] <= pivot) {
      std::swap(a[i++], a[j]);
    }
  }
  std::swap(a[i], a[r]);
  return i;
}

long FindKStatistic(std::vector<long>& a, long k, long n) {
  k = std::min(k, n);
  long l = 0;
  long r = n - 1;
  k--;
  while (true) {
    long p = Partition(a, l, r);
    if (p < k) {
      l = p + 1;
    } else if (p > k) {
      r = p - 1;
    } else if (p == k) {
      return a[k];
    }
  }
}

std::vector<long> MassiveComplete(std::vector<long>& a, long n) {
  for (long i = 2; i < n; i++) {
    a[i] = (a[i - 1] * cR + a[i - 2] * cE) % (cW + cL);
  }
  return a;
}

int main() {
  long n;
  std::cin >> n;
  long k;
  std::cin >> k;
  std::vector<long> a(n);
  std::cin >> a[0];
  std::cin >> a[1];
  MassiveComplete(a, n);
  long res = FindKStatistic(a, k, n);
  std::cout << res;
}
