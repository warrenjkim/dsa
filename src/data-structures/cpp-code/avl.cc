#include "data-structures/avl.h"

static size_t max(const size_t lhs, const size_t rhs) {
  return lhs < rhs ? rhs : lhs;
}

AVLTree::AVLTree() : root_(nullptr), size_(0) {}

AVLTree::~AVLTree() {
  if (root_) {
    delete root_;
  }
}

avl::Node *AVLTree::root() { return root_; }

size_t AVLTree::size() { return size_; }

void AVLTree::insert(const int data) { root_ = recursive_insert(root_, data); }

void AVLTree::remove(const int target) {
  root_ = recursive_remove(root_, target);
}

avl::Node *AVLTree::find(const int target) {
  return recursive_find(root_, target);
}

avl::Node *AVLTree::recursive_insert(avl::Node *root, const int data) {
  if (!root) {
    size_++;
    return new avl::Node(data);
  }

  if (data < root->data) {
    root->left = recursive_insert(root->left, data);
  } else if (data > root->data) {
    root->right = recursive_insert(root->right, data);
  } else {
    return root;
  }

  root->height = 1 + max(height(root->left), height(root->right));
  int height_diff = height_difference(root);
  if (height_diff >= -1 && height_diff <= 1) {
    return root;
  }

  Structure structure;
  if (height_diff > 1) {
    structure = data < root->left->data ? AVLTree::Structure::LEFT_LEFT
                                        : AVLTree::Structure::LEFT_RIGHT;
  } else {
    structure = data < root->right->data ? AVLTree::Structure::RIGHT_LEFT
                                         : AVLTree::Structure::RIGHT_RIGHT;
  }

  return rebalance(root, structure);
}

avl::Node *AVLTree::recursive_remove(avl::Node *root, const int target) {
  if (!root) {
    return nullptr;
  }

  if (target < root->data) {
    root->left = recursive_remove(root->left, target);
  } else if (target > root->data) {
    root->right = recursive_remove(root->right, target);
  } else {
    if (!root->left || !root->right) {
      avl::Node *del = root->left ? root->left : root->right;
      if (!del) {
        delete root;
        return nullptr;
      } else {
        *root = *del;
        delete del;
      }
    } else {
      avl::Node *del = successor(root);
      root->data = del->data;
      root->right = recursive_remove(root->right, del->data);
    }
  }

  root->height = 1 + max(height(root->left), height(root->right));
  int height_diff = height_difference(root);
  if (height_diff >= -1 && height_diff <= 1) {
    return root;
  }

  Structure structure;
  if (height_diff > 1) {
    structure = height_difference(root->left) >= 0
                    ? AVLTree::Structure::LEFT_LEFT
                    : AVLTree::Structure::LEFT_RIGHT;
  } else {
    structure = height_difference(root->right) > 0
                    ? AVLTree::Structure::RIGHT_LEFT
                    : AVLTree::Structure::RIGHT_RIGHT;
  }

  return rebalance(root, structure);
}

avl::Node *AVLTree::recursive_find(avl::Node *root, const int target) {
  if (!root) {
    return nullptr;
  }

  if (target < root->data) {
    return recursive_find(root->left, target);
  } else if (target > root->data) {
    return recursive_find(root->right, target);
  }

  return root;
}

avl::Node *AVLTree::left_rotate(avl::Node *node) {
  avl::Node *new_root = node->right;
  avl::Node *subtree = new_root->left;

  new_root->left = node;
  node->right = subtree;

  node->height = max(height(node->left), height(node->right) + 1);
  new_root->height = max(height(new_root->left), height(new_root->right) + 1);

  return new_root;
}

avl::Node *AVLTree::right_rotate(avl::Node *node) {
  avl::Node *new_root = node->left;
  avl::Node *subtree = new_root->right;

  new_root->right = node;
  node->left = subtree;

  node->height = max(height(node->left), height(node->right) + 1);
  new_root->height = max(height(new_root->left), height(new_root->right) + 1);

  return new_root;
}

avl::Node *AVLTree::rebalance(avl::Node *node, const Structure structure) {
  switch (structure) {
    case Structure::LEFT_LEFT:
      return right_rotate(node);
    case Structure::RIGHT_RIGHT:
      return left_rotate(node);
    case Structure::LEFT_RIGHT:
      node->left = left_rotate(node->left);
      return right_rotate(node);
    case Structure::RIGHT_LEFT:
      node->right = right_rotate(node->right);
      return left_rotate(node);
  }
}

size_t AVLTree::height(avl::Node *node) {
  if (!node) {
    return 0;
  }

  return node->height;
}

int AVLTree::height_difference(avl::Node *node) {
  return static_cast<int>(height(node->left) - height(node->right));
}

avl::Node *AVLTree::successor(avl::Node *root) {
  avl::Node *successor = root->right;
  while (successor && successor->left) {
    successor = successor->left;
  }

  return successor;
}
