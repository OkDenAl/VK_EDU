#include <iostream>
#include <unordered_set>
#include <utility>

const int PrimeForHash = 71;

struct Node {
  std::string productName;
  int color;
  int size;

  Node(std::string name, int col, int s);

  ~Node() = default;

  size_t operator()(const Node &node) const noexcept {
    size_t hash = 0;
    for (int i = 0; i < node.productName.size(); i++) {
      hash = hash * PrimeForHash + node.productName[i];
    }
    hash += node.size + node.color;
    return hash;
  };

  bool operator==(const Node &n1) const {
    return n1.size == size && n1.color == color &&
           n1.productName == productName;
  }
};

Node::Node(std::string name, int col, int s)
    : productName(std::move(name)), color(col), size(s) {}

template <>
struct std::hash<Node> {
  std::size_t operator()(const Node &p) const noexcept { return p(p); }
};

int main() {
  std::unordered_set<Node> set;
  char op;
  std::string name;
  int color, size;

  while (std::cin >> op >> name >> color >> size) {
    switch (op) {
      case '?': {
        std::cout << (set.find(Node(name, color, size)) != set.end() ? "OK"
                                                                     : "FAIL")
                  << std::endl;
        break;
      }
      case '+': {
        std::cout << (set.insert(Node(name, color, size)).second ? "OK"
                                                                 : "FAIL")
                  << std::endl;
        break;
      }
      case '-': {
        std::cout << (set.erase(Node(name, color, size)) ? "OK" : "FAIL")
                  << std::endl;
        break;
      }
      default: {
        return 0;
      }
    }
  }
  return 0;
}