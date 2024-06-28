#include "data-structures/avl.h"

#include "gtest/gtest.h"

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
  void match_trees(AVLNode *actual, AVLNode *expected) {
    if (!actual && !expected) {
      return;
    }

    ASSERT_TRUE(actual);
    ASSERT_TRUE(expected);
    match_trees(actual->left, expected->left);
    ASSERT_EQ(actual->data, expected->data);
    match_trees(actual->right, expected->right);
  }

  void inorder(AVLNode *root, int depth = 0) {
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

TEST_F(AVLTreeTest, InsertDuplicate) {
  AVLTree *tree = new AVLTree();
  ASSERT_TRUE(tree);
  tree->insert(0);
  AVLNode *expected = new AVLNode(0);
  match_trees(tree->root(), expected);
  tree->insert(0);
  match_trees(tree->root(), expected);
}

TEST_F(AVLTreeTest, InsertMultiple) {
  ASSERT_TRUE(tree_);
  AVLNode *expected = new AVLNode(8);

  expected->left = new AVLNode(5);
  expected->left->left = new AVLNode(4);
  expected->left->right = new AVLNode(6);

  expected->right = new AVLNode(12);

  expected->right->left = new AVLNode(10);
  expected->right->left->left = nullptr;
  expected->right->left->right = nullptr;

  expected->right->right = new AVLNode(15);
  expected->right->right->left = new AVLNode(14);
  expected->right->right->right = new AVLNode(16);
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
  AVLNode *expected = new AVLNode(5);
  expected->left = new AVLNode(4);
  expected->right = new AVLNode(8);
  expected->right->left = new AVLNode(6);

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
  AVLNode *expected = new AVLNode(14);

  expected->left = new AVLNode(5);
  expected->left->left = new AVLNode(4);
  expected->left->right = new AVLNode(6);

  expected->right = new AVLNode(15);
  expected->right->left = nullptr;
  expected->right->right = new AVLNode(16);

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, DeleteNonExistent) {
  ASSERT_TRUE(tree_);
  tree_->remove(100);
  AVLNode *expected = new AVLNode(8);

  expected->left = new AVLNode(5);
  expected->left->left = new AVLNode(4);
  expected->left->right = new AVLNode(6);

  expected->right = new AVLNode(12);

  expected->right->left = new AVLNode(10);
  expected->right->left->left = nullptr;
  expected->right->left->right = nullptr;

  expected->right->right = new AVLNode(15);
  expected->right->right->left = new AVLNode(14);
  expected->right->right->right = new AVLNode(16);
  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, SearchExistent) {
  ASSERT_TRUE(tree_);
  AVLNode *search = tree_->find(10);
  ASSERT_TRUE(search);
}

TEST_F(AVLTreeTest, SearchNonExistent) {
  ASSERT_TRUE(tree_);
  AVLNode *search = tree_->find(100);
  ASSERT_FALSE(search);
}
