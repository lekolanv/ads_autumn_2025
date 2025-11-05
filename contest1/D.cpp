#include <cstdint>
#include <iostream>
#include <vector>

int const bC = 256;

int BytesCount(uint64_t d) {
    if (d == 0) {
      return 1;
    }
    int c = 0;
    while (d > 0) {
        c++;
        d >>= 8;
    }
    return c;
}

uint64_t getMax(const std::vector<uint64_t>& a) {
    uint64_t max = a[0];
    for (size_t i = 1; i < a.size(); ++i) {
      if (a[i] > max) {
        max = a[i];
      }
    }
    return max;
}

void ByteSort(std::vector<uint64_t>& a, int b_idx) {
    int n = static_cast<int>(a.size());
    std::vector<uint64_t> temp(n);
    std::vector<int> c(bC, 0);
    for (int i = 0; i < n; ++i) {
        int b_val = (a[i] >> (b_idx * 8)) & 0xFF;
        c[b_val]++;
    }
    for (int i = 1; i < bC; ++i) {
        c[i] += c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        int b_val = (a[i] >> (b_idx * 8)) & 0xFF;
        temp[c[b_val] - 1] = a[i];
        c[b_val]--;
    }
    for (int i = 0; i < n; ++i) {
        a[i] = temp[i];
    }
}

void LSD(std::vector<uint64_t>& a) {
    uint64_t max_val = getMax(a);
    int num_bytes = BytesCount(max_val);
    for (int byte = 0; byte < num_bytes; ++byte) {
        ByteSort(a, byte);
    }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<uint64_t> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  LSD(a);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i];
    if (i + 1 < a.size()){
      std::cout << " ";
    }
    std::cout << std::endl;
    return 0;
  }
}
