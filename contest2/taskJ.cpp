#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<long long, int>> heap;
std::vector<int> p;

void SiftUp(int idx) {
  while (idx > 0) {
    int pt = (idx - 1) / 2;
    if (heap[pt].first > heap[idx].first) {
      std::swap(heap[pt], heap[idx]);
      p[heap[idx].second] = idx;
      p[heap[pt].second] = pt;
      idx = pt;
    } else {
      break;
    }
  }
}

void SiftDown(int idx) {
  int n = heap.size();
  while (true) {
    int l = 2 * idx + 1;
    int r = 2 * idx + 2;
    int s = idx;
    if (l < n && heap[l].first < heap[s].first) {
      s = l;
    }
    if (r < n && heap[r].first < heap[s].first) {
      s = r;
    }
    if (s != idx) {
      std::swap(heap[idx], heap[s]);
      p[heap[idx].second] = idx;
      p[heap[s].second] = s;
      idx = s;
    } else {
      break;
    }
  }
}

void Insert(long long value, int q_num) {
  heap.push_back(std::make_pair(value, q_num));
  p[q_num] = heap.size() - 1;
  SiftUp(heap.size() - 1);
}

void ExtractMin() {
  if (heap.empty()) {
    return;
  }
  p[heap[0].second] = -1;
  int last = heap.size() - 1;
  if (last > 0) {
    heap[0] = heap[last];
    p[heap[0].second] = 0;
    heap.pop_back();
    SiftDown(0);
  } else {
    heap.pop_back();
  }
}

void DecreaseKey(int q_num, long long d) {
  int idx = p[q_num];
  heap[idx].first -= d;
  SiftUp(idx);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int q;
  std::cin >> q;
  p.resize(q + 1, -1);
  std::cin.ignore();
  for (int i = 1; i <= q; i++) {
    std::string l;
    std::getline(std::cin, l);
    size_t fs = l.find(' ');
    std::string c = l.substr(0, fs);
    if (c == "insert") {
      long long value = std::stoll(l.substr(fs + 1));
      Insert(value, i);
    } else if (c == "getMin") {
      std::cout << heap[0].first << "\n";
    } else if (c == "extractMin") {
      ExtractMin();
    } else if (c == "decreaseKey") {
      size_t sp = l.find(' ', fs + 1);
      int p = std::stoi(l.substr(fs + 1, sp - fs - 1));
      long long d = std::stoll(l.substr(sp + 1));
      DecreaseKey(p, d);
    }
  }
}
