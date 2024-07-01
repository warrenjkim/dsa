#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stddef.h>

#include "tree.h"

namespace avl {
class Node : public tree::Node {
 public:
  int data;
  size_t height;

  Node *left;
  Node *right;

 public:
  Node(const int data) : data(data), height(1), left(nullptr), right(nullptr) {}
  ~Node() {
    delete left;
    delete right;
  }
};
}  // namespace avl

class AVLTree : public Tree {
 private:
  enum class Structure { LEFT_LEFT, RIGHT_RIGHT, LEFT_RIGHT, RIGHT_LEFT };

 public:
  AVLTree();
  ~AVLTree();

 public:
  avl::Node *root() override;
  size_t size() override;

 public:
  void insert(const int data) override;
  void remove(const int target) override;
  avl::Node *find(const int target) override;

 private:
  avl::Node *recursive_insert(avl::Node *root, const int data);
  avl::Node *recursive_remove(avl::Node *root, const int target);
  avl::Node *recursive_find(avl::Node *root, const int target);

 private:
  avl::Node *left_rotate(avl::Node *root);
  avl::Node *right_rotate(avl::Node *root);
  avl::Node *rebalance(avl::Node *node, const Structure structure);

 private:
  size_t height(avl::Node *node);
  int height_difference(avl::Node *node);
  avl::Node *successor(avl::Node *node);

 private:
  avl::Node *root_;
  size_t size_;
};

#endif  // !avl::_TREE_H
