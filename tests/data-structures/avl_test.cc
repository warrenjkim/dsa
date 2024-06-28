#include "data-structures/avl.h"

#include "gtest/gtest.h"

class AVLTreeTest : public testing::Test {
 protected:
  AVLTree *tree_ = new AVLTree();

  void SetUp() override {
    for (int i = 1; i < 10; i++) {
      tree_->insert(i);
    }
  }

  void TearDown() override { delete tree_; }

 protected:
  void match_trees(AVLNode *actual, AVLNode *expected) {
    if (!actual || !expected) {
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

TEST_F(AVLTreeTest, Insert) {
  AVLTree *tree = new AVLTree();
  ASSERT_TRUE(tree);
  tree->insert(0);

  ASSERT_TRUE(tree);
  ASSERT_TRUE(tree->find(0));
}

TEST_F(AVLTreeTest, InsertMultiple) {
  ASSERT_TRUE(tree_);
  AVLNode *expected = new AVLNode(4);

  expected->left = new AVLNode(2);
  expected->left->left = new AVLNode(1);
  expected->left->right = new AVLNode(3);

  expected->right = new AVLNode(6);
  expected->right->left = new AVLNode(5);
  expected->right->right = new AVLNode(8);
  expected->right->right->left = new AVLNode(7);
  expected->right->right->right = new AVLNode(9);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, DeleteLeaf) {
  ASSERT_TRUE(tree_);
  tree_->remove(5);
  AVLNode *expected = new AVLNode(4);

  expected->left = new AVLNode(2);
  expected->left->left = new AVLNode(1);
  expected->left->right = new AVLNode(3);

  expected->right = new AVLNode(8);
  expected->right->left = new AVLNode(6);
  expected->right->right = new AVLNode(9);
  expected->right->right->right = new AVLNode(7);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, DeleteLeftChild) {
  ASSERT_TRUE(tree_);
  tree_->remove(5);
  tree_->remove(6);
  AVLNode *expected = new AVLNode(4);

  expected->left = new AVLNode(2);
  expected->left->left = new AVLNode(1);
  expected->left->right = new AVLNode(3);

  expected->right = new AVLNode(8);
  expected->right->left = new AVLNode(7);
  expected->right->right = new AVLNode(9);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, DeleteRightChild) {
  ASSERT_TRUE(tree_);
  tree_->remove(3);
  tree_->remove(2);
  AVLNode *expected = new AVLNode(6);

  expected->left = new AVLNode(4);
  expected->left->left = new AVLNode(1);
  expected->left->right = new AVLNode(5);

  expected->right = new AVLNode(8);
  expected->right->left = new AVLNode(7);
  expected->right->right = new AVLNode(9);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, DeleteRoot) {
  ASSERT_TRUE(tree_);
  tree_->remove(4);
  AVLNode *expected = new AVLNode(5);

  expected->left = new AVLNode(2);
  expected->left->left = new AVLNode(1);
  expected->left->right = new AVLNode(3);

  expected->right = new AVLNode(8);
  expected->right->left = new AVLNode(6);
  expected->right->right = new AVLNode(9);
  expected->right->right->right = new AVLNode(7);
  match_trees(tree_->root(), expected);
}

TEST_F(AVLTreeTest, SearchExistent) {
  ASSERT_TRUE(tree_);
  AVLNode *search = tree_->find(7);
  ASSERT_TRUE(search);
}

TEST_F(AVLTreeTest, SearchNonExistent) {
  ASSERT_TRUE(tree_);
  AVLNode *search = tree_->find(0);
  ASSERT_FALSE(search);
}
