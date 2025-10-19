#include <iostream>
#include <vector>

long Partition(std::vector<long>& a, long l, long r) {
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

long FOS(std::vector<long>& a, long k, long n) {
  if (k > n) {
    k = n;
  };
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
  const long cT = 10;
  const long cW = cT * cT * cT * cT * cT * cT * cT;
  const long cL = 4321;
  const int cR = 123;
  const int cE = 45;
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
  long res = FOS(a, k, n);
  std::cout << res;
}
