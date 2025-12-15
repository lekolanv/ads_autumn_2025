#include <iostream>

const long long cMOD = 1000000000LL;

struct AVLNode {
  long long val;
  int count;
  int height;
  AVLNode* lch;
  AVLNode* rch;
  AVLNode(long long v)
      : val(v), count(1), height(1), lch(nullptr), rch(nullptr) {}
};

struct AVLTree {
  AVLNode* root = nullptr;
  static int Height(AVLNode* n) {
    if (n == nullptr) {
      return 0;
    }
    return n->height;
  }
  static int Count(AVLNode* n) {
    if (n == nullptr) {
      return 0;
    }
    return n->count;
  }
  static void Refresh(AVLNode* n) {
    if (n == nullptr) {
      return;
    }
    int hl = Height(n->lch);
    int hr = Height(n->rch);
    n->height = 1 + (hl > hr ? hl : hr);
    n->count = 1 + Count(n->lch) + Count(n->rch);
  }

  static AVLNode* RotateRight(AVLNode* y) {
    if (y == nullptr || y->lch == nullptr) {
      return y;
    }
    AVLNode* x = y->lch;
    AVLNode* t = x->rch;
    x->rch = y;
    y->lch = t;
    Refresh(y);
    Refresh(x);
    return x;
  }

  static AVLNode* RotateLeft(AVLNode* x) {
    if (x == nullptr || x->rch == nullptr) {
      return x;
    }
    AVLNode* y = x->rch;
    AVLNode* t = y->lch;
    y->lch = x;
    x->rch = t;
    Refresh(x);
    Refresh(y);
    return y;
  }

  static int BalanceFactor(AVLNode* n) {
    if (n == nullptr) {
      return 0;
    }
    return Height(n->lch) - Height(n->rch);
  }

  static AVLNode* Balance(AVLNode* n) {
    if (n == nullptr) {
      return n;
    }
    Refresh(n);
    int bf = BalanceFactor(n);
    if (bf > 1) {
      if (BalanceFactor(n->lch) < 0) {
        n->lch = RotateLeft(n->lch);
      }
      return RotateRight(n);
    }
    if (bf < -1) {
      if (BalanceFactor(n->rch) > 0) {
        n->rch = RotateRight(n->rch);
      }
      return RotateLeft(n);
    }
    return n;
  }

  AVLNode* Insert(AVLNode* node, long long key) {
    if (node == nullptr) {
      return new AVLNode(key);
    }
    if (key < node->val) {
      node->lch = Insert(node->lch, key);
    } else if (key > node->val) {
      node->rch = Insert(node->rch, key);
    } else {
      return node;
    }
    return Balance(node);
  }

  void Insert(long long key) { root = Insert(root, key); }

  static AVLNode* FindMin(AVLNode* n) {
    if (n == nullptr) {
      return nullptr;
    }
    while (n->lch != nullptr) {
      n = n->lch;
    }
    return n;
  }

  static AVLNode* FindMax(AVLNode* n) {
    if (n == nullptr) {
      return nullptr;
    }
    while (n->rch != nullptr) {
      n = n->rch;
    }
    return n;
  }

  AVLNode* Remove(AVLNode* node, long long key) {
    if (node == nullptr) {
      return nullptr;
    }
    if (key < node->val) {
      node->lch = Remove(node->lch, key);
      return Balance(node);
    }
    if (key > node->val) {
      node->rch = Remove(node->rch, key);
      return Balance(node);
    }
    if (node->lch == nullptr) {
      AVLNode* tmp = node->rch;
      delete node;
      return tmp;
    }
    if (node->rch == nullptr) {
      AVLNode* tmp = node->lch;
      delete node;
      return tmp;
    }
    AVLNode* min_node = FindMin(node->rch);
    node->val = min_node->val;
    node->rch = Remove(node->rch, min_node->val);
    return Balance(node);
  }

  void Remove(long long key) { root = Remove(root, key); }

  bool Contains(AVLNode* node, long long key) {
    if (node == nullptr) {
      return false;
    }
    if (key < node->val) {
      return Contains(node->lch, key);
    }
    if (key > node->val) {
      return Contains(node->rch, key);
    }
    return true;
  }

  bool Contains(long long key) { return Contains(root, key); }

  static long long Kth(AVLNode* root, int k) {
    AVLNode* cur = root;
    while (cur != nullptr) {
      int left_count = Count(cur->lch);
      if (k <= left_count) {
        cur = cur->lch;
      } else if (k == left_count + 1) {
        return cur->val;
      } else {
        k -= left_count + 1;
        cur = cur->rch;
      }
    }
    return -1;
  }

  long long LowerBound(AVLNode* node, long long key) {
    if (node == nullptr) {
      return -1;
    }
    if (key == node->val) {
      return node->val;
    }
    if (key < node->val) {
      long long left_res = LowerBound(node->lch, key);
      if (left_res != -1) {
        return left_res;
      }
      return node->val;
    }
    return LowerBound(node->rch, key);
  }

  long long LowerBound(long long key) { return LowerBound(root, key); }

  static void DeallocateTree(AVLNode* cur) {
    if (cur == nullptr) {
      return;
    }
    DeallocateTree(cur->lch);
    DeallocateTree(cur->rch);
    delete cur;
  }
  ~AVLTree() { DeallocateTree(root); }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  AVLTree tree;
  int q;
  std::cin >> q;
  long long last_answer = -1;
  bool last_was_query = false;
  for (int i = 0; i < q; ++i) {
    char op;
    long long x;
    std::cin >> op >> x;
    if (op == '+') {
      if (last_was_query) {
        x = (x + last_answer) % cMOD;
      }
      if (!tree.Contains(x)) {
        tree.Insert(x);
      }
      last_was_query = false;
    } else if (op == '?') {
      last_answer = tree.LowerBound(x);
      std::cout << last_answer << '\n';
      last_was_query = true;
    }
  }
}
