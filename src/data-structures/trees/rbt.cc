#include "data-structures/trees/rbt.h"

#include <stdio.h>

using rbt::Node;

RBTree::RBTree() : root_(nullptr), size_(0) {}

RBTree::~RBTree() {
  if (root_) {
    delete root_;
  }
}

Node *RBTree::root() { return root_; }

size_t RBTree::size() { return size_; }

void RBTree::insert(const int data) {
  Node *z = nullptr;
  size_t size = size_;
  root_ = recursive_insert(root_, data, z);
  if (size_ == size) {
    return;
  }

  root_ = double_red_fixup(z);
}

void RBTree::remove(const int target) {
  Node *del = find(target);
  if (!del) {
    return;
  }

  root_ = recursive_remove(del);
}

Node *RBTree::find(const int target) { return recursive_find(root_, target); }

Node *RBTree::recursive_insert(Node *root, const int data, Node *&z) {
  if (!root) {
    size_++;
    z = new Node(data);
    return z;
  }

  if (data < root->data) {
    root->left = recursive_insert(root->left, data, z);
    if (root->left == z) {
      z->parent = root;
    }
  } else if (data > root->data) {
    root->right = recursive_insert(root->right, data, z);
    if (root->right == z) {
      z->parent = root;
    }
  }

  return root;
}

Node *RBTree::recursive_remove(Node *target) {
  if (target->left && target->right) {
    Node *replacement = successor(target);
    target->data = replacement->data;
    return recursive_remove(replacement);
  }

  auto relink_parent_child = [](Node *&node, Node *res) -> void {
    if (node->parent->left == node) {
      node->parent->left = res;
    } else {
      node->parent->right = res;
    }
  };

  Node *replacement = nullptr;
  Node *parent = target->parent;
  if (!target->left && !target->right) {
    relink_parent_child(target, nullptr);
    rbt::Color target_color = target->color;
    delete target;
    if (target_color == rbt::Color::RED) {
      return root_;
    } else {
      Node *z = double_black_fixup(nullptr, parent);
      while (z->parent) {
        z = z->parent;
      }

      z->color = rbt::Color::BLACK;
      return z;
    }
  }

  replacement = target->left ? target->left : target->right;
  relink_parent_child(replacement, target);
  replacement->parent = target->parent;
  *target = *replacement;
  delete replacement;
  target->color = rbt::Color::BLACK;
  while (target->parent) {
    target = target->parent;
  }

  target->color = rbt::Color::BLACK;
  return target;
}

Node *RBTree::recursive_find(Node *root, const int target) {
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

Node *RBTree::successor(Node *node) {
  Node *successor = node->right;
  while (successor && successor->left) {
    successor = successor->left;
  }

  return successor;
}

Node *RBTree::double_red_fixup(Node *z) {
  if (!z->parent) {
    z->color = rbt::Color::BLACK;
    return z;
  }

  if (is_black(z) || is_black(z->parent)) {
    return double_red_fixup(z->parent);
  }

  Node *u = uncle(z);
  if (is_black(u)) {
    z = restructure(z);
    z->color = rbt::Color::BLACK;
    z->left->color = rbt::Color::RED;
    z->right->color = rbt::Color::RED;
    return double_red_fixup(z);
  }

  return double_red_fixup(recolor(z));
}

Node *RBTree::double_black_fixup(Node *replacement, Node *parent) {
  if (!parent) {
    return replacement;
  }

  Node *sibling = parent->left == replacement ? parent->right : parent->left;
  if (is_red(sibling)) {
    Node *z = parent->left == sibling ? sibling->left : sibling->right;
    z = restructure(z);
    z->color = rbt::Color::BLACK;
    parent->color = rbt::Color::RED;
    return double_black_fixup(replacement, parent);
  }

  if (is_black(sibling->left) && is_black(sibling->right)) {
    sibling->color = rbt::Color::RED;
    if (is_red(parent)) {
      parent->color = rbt::Color::BLACK;
      return parent;
    } else {
      return double_black_fixup(parent, parent->parent);
    }
  }

  Node *z = nullptr;
  if (is_red(sibling->left) && is_red(sibling->right)) {
    z = parent->left == sibling ? sibling->left : sibling->right;
  } else {
    z = is_red(sibling->left) ? sibling->left : sibling->right;
  }

  z = restructure(z);
  z->color = rbt::Color::RED;
  z->left->color = rbt::Color::BLACK;
  z->right->color = rbt::Color::BLACK;

  return z;
}

Node *RBTree::recolor(Node *z) {
  z->parent->color = rbt::Color::BLACK;
  uncle(z)->color = rbt::Color::BLACK;
  grandparent(z)->color = rbt::Color::RED;

  return grandparent(z);
}

Node *RBTree::restructure(Node *z) {
  Structure structure;
  if (grandparent(z)->left == z->parent) {
    structure = z->parent->left == z ? RBTree::Structure::LEFT_LEFT
                                     : RBTree::Structure::LEFT_RIGHT;
  } else {
    structure = z->parent->left == z ? RBTree::Structure::RIGHT_LEFT
                                     : RBTree::Structure::RIGHT_RIGHT;
  }

  switch (structure) {
    case Structure::LEFT_LEFT:
      z = right_rotate(grandparent(z));
      break;
    case Structure::LEFT_RIGHT:
      z = right_rotate(left_rotate(z->parent)->parent);
      break;
    case Structure::RIGHT_LEFT:
      z = left_rotate(right_rotate(z->parent)->parent);
      break;
    case Structure::RIGHT_RIGHT:
      z = left_rotate(grandparent(z));
      break;
  }

  return z;
}

Node *RBTree::left_rotate(Node *node) {
  Node *new_root = node->right;
  node->right = new_root->left;
  if (new_root->left) {
    new_root->left->parent = node;
  }

  new_root->parent = node->parent;
  if (node->parent) {
    if (node->parent->left == node) {
      node->parent->left = new_root;
    } else {
      node->parent->right = new_root;
    }
  }

  new_root->left = node;
  node->parent = new_root;

  return new_root;
}

Node *RBTree::right_rotate(Node *node) {
  Node *new_root = node->left;

  node->left = new_root->right;
  if (new_root->right) {
    new_root->right->parent = node;
  }

  new_root->parent = node->parent;
  if (node->parent) {
    if (node->parent->left == node) {
      node->parent->left = new_root;
    } else {
      node->parent->right = new_root;
    }
  }

  new_root->right = node;
  node->parent = new_root;

  return new_root;
}

Node *RBTree::grandparent(Node *node) { return node->parent->parent; }

Node *RBTree::uncle(Node *z) {
  Node *gp = grandparent(z);
  return gp->left == z->parent ? gp->right : gp->left;
}

bool RBTree::is_black(Node *node) {
  return !node || node->color == rbt::Color::BLACK;
}

bool RBTree::is_red(Node *node) {
  return node && node->color == rbt::Color::RED;
}
