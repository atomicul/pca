#include <iostream>
#include <memory>

struct Node {
  int value;
  std::shared_ptr<Node> left, right;

  friend std::ostream &operator<<(std::ostream &os, Node const &tree) {
    if (tree.left)
      os << *tree.left;
    os << tree.value << '\n';
    if (tree.right)
      os << *tree.right;
    return os;
  }
};

int main() {
  std::string str;
  std::cin >> str;
  str.pop_back();

  int i = 1;
  auto tree = std::make_shared<Node>(i++, nullptr, nullptr);
  auto n = tree;
  for (char c : str) {
    auto branch = c == 'l' ? &Node::left : &Node::right;
    (*n).*branch = std::make_shared<Node>(i++, nullptr, nullptr);
    n = (*n).*branch;
  }

  std::cout << *tree;
}
