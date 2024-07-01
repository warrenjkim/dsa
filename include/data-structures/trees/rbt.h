#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stddef.h>

#include "data-structures/trees/tree.h"

namespace rbt {
enum class Color { RED, BLACK };
class Node : public tree::Node {
 public:
  int data;
  Color color;
  Node *left;
  Node *right;
  Node *parent;

 public:
  Node(const int data)
      : data(data),
        color(Color::RED),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}
  ~Node() {
    delete left;
    delete right;
  }
};
}  // namespace rbt

class RBTree : public Tree {
 private:
  enum class DoubleRed { LEFT_LEFT, RIGHT_RIGHT, LEFT_RIGHT, RIGHT_LEFT };

 public:
  RBTree();
  ~RBTree();

 public:
  rbt::Node *root() override;
  size_t size() override;

 public:
  void insert(const int data) override;
  void remove(const int target) override;
  rbt::Node *find(const int target) override;

 private:
  rbt::Node *recursive_insert(rbt::Node *root, const int data, rbt::Node *&z);
  rbt::Node *recursive_remove(rbt::Node *target);
  rbt::Node *recursive_find(rbt::Node *root, const int target);
  rbt::Node *successor(rbt::Node *node);

 private:
  rbt::Node *double_red_fixup(rbt::Node *z);
  rbt::Node *double_black_fixup(rbt::Node *target, rbt::Node *replacement);
  rbt::Node *recolor(rbt::Node *node);
  rbt::Node *restructure(rbt::Node *node);

 private:
  rbt::Node *left_rotate(rbt::Node *root);
  rbt::Node *right_rotate(rbt::Node *root);

 private:
  rbt::Node *grandparent(rbt::Node *z);
  rbt::Node *uncle(rbt::Node *z);
  rbt::Node *sibling(rbt::Node *node);

 private:
  bool is_black(rbt::Node *node);
  bool is_red(rbt::Node *node);

 private:
  rbt::Node *root_;
  size_t size_;
};

#endif  // !RED_BLACK_TREE_H
