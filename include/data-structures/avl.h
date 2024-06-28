#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stddef.h>

struct AVLNode {
  int data;
  size_t height;

  AVLNode *left;
  AVLNode *right;

  AVLNode() : data(0), height(0), left(nullptr), right(nullptr) {}
  AVLNode(const int data)
      : data(data), height(1), left(nullptr), right(nullptr) {}
  ~AVLNode() {
    delete left;
    delete right;
  }
};

class AVLTree {
 private:
  enum class Structure { LEFT_LEFT, RIGHT_RIGHT, LEFT_RIGHT, RIGHT_LEFT };

 public:
  AVLTree();
  ~AVLTree();

 public:
  AVLNode *root();

 public:
  void insert(const int data);
  void remove(const int target);
  AVLNode *find(const int target);

 private:
  AVLNode *recursive_insert(AVLNode *root, const int data);
  AVLNode *recursive_remove(AVLNode *root, const int target);
  AVLNode *recursive_find(AVLNode *root, const int target);

 private:
  AVLNode *left_rotate(AVLNode *root);
  AVLNode *right_rotate(AVLNode *root);
  AVLNode *rebalance(AVLNode *node, const Structure structure);

 private:
  size_t height(AVLNode *node);
  int height_difference(AVLNode *node);
  AVLNode *successor(AVLNode *node);

 private:
  AVLNode *root_;
};

#endif  // !AVL_TREE_H
