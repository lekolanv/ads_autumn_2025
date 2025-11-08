#include <iostream>
#include <vector>
#include <cstdint>

void MergeOneArray(std::vector<std::pair<int, int>>& a, int l, int mid, int r) {
  int left = l;
  int right = mid + 1;
  std::vector<std::pair<int, int>> temp;
  while (left <= mid and right <= r) {
    if (a[left] <= a[right]) {
      temp.push_back(a[left]);
      left++;
    } else {
      temp.push_back(a[right]);
      right++;
    }
  }
  while (left <= mid) {
    temp.push_back(a[left++]);
  }
  while (right <= r) {
    temp.push_back(a[right++]);
  }
  for (int i = 0; i < (int)temp.size(); i++) {
    a[l + i] = temp[i];
  }
}

void MergeSort(std::vector<std::pair<int, int>>& a, int l, int r) {
  int mid = l + (r - l) / 2;
  if (l < r) {
    MergeSort(a, l, mid);
    MergeSort(a, mid + 1, r);
    MergeOneArray(a, l, mid, r);
  }
}

int ProcessSegments(std::vector<std::pair<int, int>>& a) {
  int c = 0;
  int curr_i = 0;
  for (int i = 1; i < (int)a.size(); i++) {
    if (a[curr_i].second >= a[i].first) {
      a[curr_i].second = a[i].second;
      c++;
    } else {
      curr_i++;
      a[curr_i] = a[i];
    }
  }
  a.resize(curr_i + 1);
  return c;
}

int32_t main() {
  int32_t n;
  std::cin >> n;
  std::vector<std::pair<int, int>> a;
  for (int i = 0; i < n; i++) {
    int a1;
    int a2;
    std::cin >> a1 >> a2;
    a.emplace_back(a1, a2);
  }
  if (n > 0) {
    MergeSort(a, 0, n - 1);
  }
  int c = ProcessSegments(a);
  std::cout << n - c << "\n";
  for (const auto& p : a) {
    std::cout << p.first << " " << p.second << "\n";
  }
}
