#include "data-structures/bst.h"

#include "gtest/gtest.h"

class BinarySearchTreeTest : public testing::Test {
 protected:
  BSTNode *root_ = nullptr;

  void SetUp() override {
    bst_insert(&root_, 4);

    bst_insert(&root_, 2);
    bst_insert(&root_, 1);
    bst_insert(&root_, 3);

    bst_insert(&root_, 6);
    bst_insert(&root_, 5);
    bst_insert(&root_, 7);
  }

  void TearDown() override {
    bst_destroy(&root_);
    ASSERT_FALSE(root_);
  }

 protected:
  BSTNode *node_init(const int data) {
    BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));
    if (!node) {
      fprintf(stderr, "node_init() - malloc failed.");
      exit(EXIT_FAILURE);
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
  }

  void match_trees(BSTNode *actual, BSTNode *expected) {
    if (!actual || !expected) {
      return;
    }

    ASSERT_TRUE(actual);
    ASSERT_TRUE(expected);
    match_trees(actual->left, expected->left);
    ASSERT_EQ(actual->data, expected->data);
    match_trees(actual->right, expected->right);
  }

  void inorder(BSTNode *root) {
    if (!root) {
      return;
    }

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
  }
};

TEST_F(BinarySearchTreeTest, Nulls) {
  BSTNode *null = nullptr;
  bst_delete(&null, 0);
  ASSERT_FALSE(null);
  bst_find(&null, 0);
  ASSERT_FALSE(null);
  bst_destroy(&null);
  ASSERT_FALSE(null);
}

TEST_F(BinarySearchTreeTest, InsertDuplicate) {
  BSTNode *root = nullptr;
  bst_insert(&root, 0);
  ASSERT_TRUE(root);
  ASSERT_EQ(root->data, 0);
  bst_insert(&root, 0);
  ASSERT_TRUE(root);
  ASSERT_EQ(root->data, 0);
}

TEST_F(BinarySearchTreeTest, InsertMultiple) {
  ASSERT_TRUE(root_);
  BSTNode *expected = node_init(4);
  expected->left = node_init(2);
  expected->right = node_init(6);
  expected->left->left = node_init(1);
  expected->left->right = node_init(3);
  expected->right->left = node_init(5);
  expected->right->right = node_init(7);
  match_trees(root_, expected);
}

TEST_F(BinarySearchTreeTest, DeleteLeaf) {
  BSTNode *root = nullptr;

  bst_insert(&root, 0);
  bst_delete(&root, 0);
  ASSERT_FALSE(root);

  ASSERT_TRUE(root_);
  bst_delete(&root_, 1);
  ASSERT_TRUE(root_);
  BSTNode *expected = node_init(4);
  expected->left = node_init(2);
  expected->right = node_init(6);
  expected->left->right = node_init(3);
  expected->right->left = node_init(5);
  expected->right->right = node_init(7);
  match_trees(root_, expected);
}

TEST_F(BinarySearchTreeTest, DeleteLeftChild) {
  ASSERT_TRUE(root_);
  bst_insert(&root_, 0);
  ASSERT_TRUE(root_);
  bst_delete(&root_, 1);
  BSTNode *expected = node_init(4);
  expected->left = node_init(2);
  expected->right = node_init(6);
  expected->left->left = node_init(0);
  expected->left->right = node_init(3);
  expected->right->left = node_init(5);
  expected->right->right = node_init(7);
  match_trees(root_, expected);
}

TEST_F(BinarySearchTreeTest, DeleteRightChild) {
  ASSERT_TRUE(root_);
  bst_insert(&root_, 8);
  ASSERT_TRUE(root_);
  bst_delete(&root_, 7);
  ASSERT_TRUE(root_);
  BSTNode *expected = node_init(4);
  expected->left = node_init(2);
  expected->right = node_init(6);
  expected->left->left = node_init(1);
  expected->left->right = node_init(3);
  expected->right->left = node_init(5);
  expected->right->right = node_init(8);
  match_trees(root_, expected);
}

TEST_F(BinarySearchTreeTest, DeleteRoot) {
  ASSERT_TRUE(root_);
  bst_delete(&root_, 4);
  ASSERT_TRUE(root_);
  BSTNode *expected = node_init(5);
  expected->left = node_init(2);
  expected->right = node_init(6);
  expected->left->left = node_init(1);
  expected->left->right = node_init(3);
  expected->right->right = node_init(7);
  match_trees(root_, expected);
}

TEST_F(BinarySearchTreeTest, SearchExistent) {
  ASSERT_TRUE(root_);
  BSTNode *search = bst_find(&root_, 2);
  ASSERT_TRUE(search);
}

TEST_F(BinarySearchTreeTest, SearchNonExistent) {
  ASSERT_TRUE(root_);
  BSTNode *search = bst_find(&root_, 0);
  ASSERT_FALSE(search);
  search = bst_find(&root_, 100);
}
