#include "data-structures/trees/avl.h"

#include "gtest/gtest.h"

using avl::Node;

class AVLTreeTest : public testing::Test {
 protected:
  AVLTree *tree_ = new AVLTree();

  void SetUp() override {
    tree_->insert(10);
    tree_->insert(8);
    tree_->insert(6);
    tree_->insert(4);
    tree_->insert(5);
    tree_->insert(12);
    tree_->insert(14);
    tree_->insert(16);
    tree_->insert(15);
  }

  void TearDown() override { delete tree_; }

 protected:
  void match_trees(Node *actual, Node *expected) {
    if (!actual && !expected) {
      return;
    }

    ASSERT_TRUE(actual);
    ASSERT_TRUE(expected);
    match_trees(actual->left, expected->left);
    ASSERT_EQ(actual->data, expected->data);
    match_trees(actual->right, expected->right);
  }

  void inorder(Node *root, int depth = 0) {
    if (!root) {
      return;
    }

    inorder(root->right, depth + 1);
    if (depth == 0) {
      printf("root: (%d)\n", root->data);
    } else {
      printf("%*s%*s(%d)\n", 4, " ", depth * 4, " ", root->data);
    }
    inorder(root->left, depth + 1);
  }
};

TEST_F(AVLTreeTest, Size) {
  AVLTree *tree = new AVLTree();
  ASSERT_EQ(tree->size(), 0);
  ASSERT_EQ(tree_->size(), 9);
}

TEST_F(AVLTreeTest, InsertDuplicate) {
  AVLTree *tree = new AVLTree();
  ASSERT_TRUE(tree);
  tree->insert(0);
  Node *expected = new Node(0);
  match_trees(tree->root(), expected);
  tree->insert(0);
  match_trees(tree->root(), expected);
}

TEST_F(AVLTreeTest, InsertMultiple) {
  ASSERT_TRUE(tree_);

  Node *expected = new Node(8);

  expected->left = new Node(5);
  expected->left->left = new Node(4);
  expected->left->right = new Node(6);

  expected->right = new Node(12);
  expected->right->left = new Node(10);
  expected->right->left->left = nullptr;
  expected->right->left->right = nullptr;
  expected->right->right = new Node(15);
  expected->right->right->left = new Node(14);
  expected->right->right->right = new Node(16);

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, DeleteLeftHeavy) {
  ASSERT_TRUE(tree_);
  tree_->remove(15);
  tree_->remove(16);
  tree_->remove(14);
  tree_->remove(10);
  tree_->remove(12);

  Node *expected = new Node(5);
  expected->left = new Node(4);
  expected->right = new Node(8);
  expected->right->left = new Node(6);

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, DeleteRightHeavy) {
  ASSERT_TRUE(tree_);
  tree_->remove(10);
  tree_->remove(12);
  tree_->remove(8);

  Node *expected = new Node(14);

  expected->left = new Node(5);
  expected->left->left = new Node(4);
  expected->left->right = new Node(6);

  expected->right = new Node(15);
  expected->right->left = nullptr;
  expected->right->right = new Node(16);

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, DeleteNonExistent) {
  ASSERT_TRUE(tree_);
  tree_->remove(100);

  Node *expected = new Node(8);

  expected->left = new Node(5);
  expected->left->left = new Node(4);
  expected->left->right = new Node(6);

  expected->right = new Node(12);
  expected->right->left = new Node(10);
  expected->right->left->left = nullptr;
  expected->right->left->right = nullptr;
  expected->right->right = new Node(15);
  expected->right->right->left = new Node(14);
  expected->right->right->right = new Node(16);

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, SearchExistent) {
  ASSERT_TRUE(tree_);
  Node *search = tree_->find(10);
  ASSERT_TRUE(search);
}

TEST_F(AVLTreeTest, SearchNonExistent) {
  ASSERT_TRUE(tree_);
  Node *search = tree_->find(100);
  ASSERT_FALSE(search);
}
