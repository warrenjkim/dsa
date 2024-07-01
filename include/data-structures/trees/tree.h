#ifndef TREE_H
#define TREE_H

#include <stddef.h>

namespace tree {
class Node {};
}  // namespace tree

class Tree {
 public:
  virtual tree::Node *root() = 0;
  virtual size_t size() = 0;

 public:
  virtual void insert(const int data) = 0;
  virtual void remove(const int target) = 0;
  virtual tree::Node *find(const int target) = 0;
};

#endif  // !TREE_H
