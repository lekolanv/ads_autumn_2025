#include <iostream>

const long cTableSize = 1 << 20;
const unsigned int cMult = 2654435761U;
const int cSA = 11;

struct Lnode {
  int value;
  Lnode* next;
  Lnode() : value(0), next(nullptr) {}
  Lnode(int v) : value(v), next(nullptr) {}
};

template <typename Type>
class Memory {
 private:
  static const long cMaxNodes = cTableSize * 10;
  Type* nodes_array_;
  long current_index_;

 public:
  Memory() : nodes_array_(new Type[cMaxNodes]), current_index_(0) {}

  ~Memory() { delete[] nodes_array_; }

  Type* Allocate(const Type& data) {
    if (current_index_ >= cMaxNodes) {
      return nullptr;
    }
    Type* node = &nodes_array_[current_index_];
    node->value = data.value;
    node->next = nullptr;
    current_index_++;
    return node;
  }

  void Deallocate(Type* /*node*/) {}
};

class HashTable {
 private:
  Lnode* table_[cTableSize];
  Memory<Lnode>& memory_;

  static int Hash(int x) {
    unsigned int u = static_cast<unsigned int>(x);
    u *= cMult;
    u ^= u >> cSA;
    return static_cast<int>(u & (cTableSize - 1));
  }

 public:
  HashTable(Memory<Lnode>& memory) : memory_(memory) {
    for (long i = 0; i < cTableSize; ++i) {
      table_[i] = nullptr;
    }
  }

  bool Contains(int x) const {
    int h = Hash(x);
    const Lnode* cur = table_[h];
    while (cur != nullptr) {
      if (cur->value == x) {
        return true;
      }
      cur = cur->next;
    }
    return false;
  }

  void Insert(int x) {
    if (Contains(x)) {
      return;
    }
    int h = Hash(x);
    Lnode* node = memory_.Allocate(Lnode(x));
    if (node == nullptr) {
      return;
    }
    node->next = table_[h];
    table_[h] = node;
  }

  void Remove(int x) {
    int h = Hash(x);
    if (table_[h] == nullptr) {
      return;
    }
    if (table_[h]->value == x) {
      Lnode* tmp = table_[h];
      table_[h] = tmp->next;
      memory_.Deallocate(tmp);
      return;
    }
    Lnode* cur = table_[h];
    while (cur->next != nullptr && cur->next->value != x) {
      cur = cur->next;
    }
    if (cur->next != nullptr) {
      Lnode* tmp = cur->next;
      cur->next = tmp->next;
      memory_.Deallocate(tmp);
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Memory<Lnode> memory;
  HashTable t(memory);
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
