#include <iostream>

const long cTableSize = 1 << 20;
const unsigned int cMult = 2654435761U;
const int cSA = 11;

struct Lnode {
  int value;
  Lnode* next;
  Lnode(int v) : value(v), next(nullptr) {}
};

struct HashTable {
  static Lnode* table[cTableSize];

  HashTable() {
    for (long i = 0; i < cTableSize; ++i) {
      table[i] = nullptr;
    }
  }

  static int Hash(int x) {
    unsigned int u = static_cast<unsigned int>(x);
    u *= cMult;
    u ^= u >> cSA;
    return static_cast<int>(u % cTableSize);
  }

  bool Contains(int x) {
    (void)this;
    int h = Hash(x);
    int matches = 0;
    Lnode* cur = table[h];
    while (cur != nullptr) {
      matches += static_cast<int>(cur->value == x);
      cur = cur->next;
    }
    return matches != 0;
  }

  void Insert(int x) {
    (void)this;
    if (Contains(x)) {
      return;
    }
    int h = Hash(x);
    Lnode* node = new Lnode(x);
    node->next = table[h];
    table[h] = node;
  }

  void Remove(int x) {
    (void)this;
    int h = Hash(x);
    if (table[h] == nullptr) {
      return;
    }
    if (table[h]->value == x) {
      Lnode* tmp = table[h];
      table[h] = tmp->next;
      delete tmp;
      return;
    }
    Lnode* cur = table[h];
    while (cur->next != nullptr && cur->next->value != x) {
      cur = cur->next;
    }
    if (cur->next != nullptr) {
      Lnode* tmp = cur->next;
      cur->next = tmp->next;
      delete tmp;
    }
  }
};

Lnode* HashTable::table[cTableSize];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  HashTable t;
  int q;
  std::cin >> q;
  while (q != 0) {
    q -= 1;
    char com;
    int x;
    std::cin >> com >> x;
    if (com == '+') {
      t.Insert(x);
    } else if (com == '-') {
      t.Remove(x);
    } else {
      if (t.Contains(x)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
  }
}
