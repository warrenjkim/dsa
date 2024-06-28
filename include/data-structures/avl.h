#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stddef.h>

namespace avl {
struct Node {
  int data;
  size_t height;

  Node *left;
  Node *right;

  Node() : data(0), height(0), left(nullptr), right(nullptr) {}
  Node(const int data) : data(data), height(1), left(nullptr), right(nullptr) {}
  ~Node() {
    delete left;
    delete right;
  }
};
}  // namespace avl

class AVLTree {
 private:
  enum class Structure { LEFT_LEFT, RIGHT_RIGHT, LEFT_RIGHT, RIGHT_LEFT };

 public:
  AVLTree();
  ~AVLTree();

 public:
  avl::Node *root();
  size_t size();

 public:
  void insert(const int data);
  void remove(const int target);
  avl::Node *find(const int target);

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
