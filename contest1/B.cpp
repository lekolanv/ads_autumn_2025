#include <iostream>
#include <vector>

const int cW = 10000000;
const int cL = 4321;
const int cR = 123;
const int cE = 45;

int MedianOfFive(std::vector<int>& arr, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    int key = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
  return left + (right - left) / 2;
}

int MedianOfMedians(std::vector<int>& arr, int left, int right) {
  int n = right - left + 1;
  if (n <= 5) {
    return MedianOfFive(arr, left, right);
  }
  int group_count = 0;
  for (int i = left; i <= right; i += 5) {
    int sub_right = (i + 4 <= right) ? i + 4 : right;
    int median_pos = MedianOfFive(arr, i, sub_right);
    std::swap(arr[median_pos], arr[left + group_count]);
    ++group_count;
  }
  return MedianOfMedians(arr, left, left + group_count - 1);
}

int Partition(std::vector<int>& arr, int left, int right) {
  int median_pos = MedianOfMedians(arr, left, right);
  std::swap(arr[median_pos], arr[right]);
  int pivot = arr[right];
  int i = left;
  for (int j = left; j < right; ++j) {
    if (arr[j] <= pivot) {
      std::swap(arr[i], arr[j]);
      ++i;
    }
  }
  std::swap(arr[i], arr[right]);
  return i;
}

int FindKthStatistic(std::vector<int>& arr, int k, int n) {
  if (k > n) {
    k = n;
  }
  int target_index = k - 1;
  int left = 0;
  int right = n - 1;
  while (true) {
    int pivot_pos = Partition(arr, left, right);
    if (pivot_pos < target_index) {
      left = pivot_pos + 1;
    } else if (pivot_pos > target_index) {
      right = pivot_pos - 1;
    } else {
      return arr[target_index];
    }
  }
}

void CompleteArray(std::vector<int>& arr, int n) {
  for (int i = 2; i < n; ++i) {
    arr[i] = (arr[i - 1] * cR + arr[i - 2] * cE) % (cW + cL);
  }
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  std::vector<int> arr(n);
  std::cin >> arr[0] >> arr[1];
  CompleteArray(arr, n);
  int result = FindKthStatistic(arr, k, n);
  std::cout << result << std::endl;
}
