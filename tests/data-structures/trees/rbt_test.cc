#include "data-structures/trees/rbt.h"

#include "gtest/gtest.h"

using rbt::Node;

class RBTreeTest : public testing::Test {
 protected:
  RBTree *tree_ = new RBTree();

  void SetUp() override {
    tree_->insert(15);
    tree_->insert(8);
    tree_->insert(20);
    tree_->insert(4);
    tree_->insert(12);
    tree_->insert(25);
    tree_->insert(30);
    tree_->insert(3);
    tree_->insert(5);
    tree_->insert(27);

    Node *expected = new Node(15);
    expected->color = rbt::Color::BLACK;

    expected->left = new Node(8);
    expected->left->color = rbt::Color::RED;
    expected->left->left = new Node(4);
    expected->left->left->color = rbt::Color::BLACK;
    expected->left->left->left = new Node(3);
    expected->left->left->left->color = rbt::Color::RED;
    expected->left->left->right = new Node(5);
    expected->left->left->right->color = rbt::Color::RED;
    expected->left->right = new Node(12);
    expected->left->right->color = rbt::Color::BLACK;

    expected->right = new Node(25);
    expected->right->color = rbt::Color::RED;
    expected->right->left = new Node(20);
    expected->right->left->color = rbt::Color::BLACK;
    expected->right->right = new Node(30);
    expected->right->right->color = rbt::Color::BLACK;
    expected->right->right->left = new Node(27);
    expected->right->right->left->color = rbt::Color::RED;

    printf("===== Actual Tree =====\n");
    inorder(tree_->root());
    printf("\n===== Expected Tree =====\n");
    inorder(expected);
    match_trees(tree_->root(), expected);
  }

  void TearDown() override { delete tree_; }

 protected:
  void match_trees(rbt::Node *actual, rbt::Node *expected) {
    if (!actual && !expected) {
      return;
    }

    ASSERT_TRUE(actual);
    ASSERT_TRUE(expected);
    match_trees(actual->left, expected->left);
    ASSERT_EQ(actual->data, expected->data);
    ASSERT_EQ(actual->color, expected->color);
    match_trees(actual->right, expected->right);
  }

  void inorder(rbt::Node *root, int depth = 0) {
    if (!root) {
      return;
    }

    inorder(root->right, depth + 1);
    if (depth == 0) {
      printf("root: (%d %c)\n", root->data,
             root->color == rbt::Color::RED ? 'R' : 'B');
    } else {
      printf("%*s%*s(%d %c)\n", 4, " ", depth * 4, " ", root->data,
             root->color == rbt::Color::RED ? 'R' : 'B');
    }
    inorder(root->left, depth + 1);
  }
};

TEST_F(RBTreeTest, Size) {
  RBTree *tree = new RBTree();
  ASSERT_EQ(tree->size(), 0);
  // ASSERT_EQ(tree_->size(), 13);
}

TEST_F(RBTreeTest, InsertDuplicate) {
  RBTree *tree = new RBTree();
  ASSERT_TRUE(tree);
  tree->insert(0);
  Node *expected = new Node(0);
  expected->color = rbt::Color::BLACK;
  match_trees(tree->root(), expected);
  tree->insert(0);
  match_trees(tree->root(), expected);
}

TEST_F(RBTreeTest, InsertLeftLeft) {
  RBTree *tree = new RBTree();
  for (int i = 7; i >= 0; i--) {
    tree->insert(i);
  }

  Node *expected = new Node(4);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(2);
  expected->left->color = rbt::Color::RED;
  expected->left->left = new Node(1);
  expected->left->left->color = rbt::Color::BLACK;
  expected->left->left->left = new Node(0);
  expected->left->left->left->color = rbt::Color::RED;
  expected->left->right = new Node(3);
  expected->left->right->color = rbt::Color::BLACK;

  expected->right = new Node(6);
  expected->right->color = rbt::Color::RED;
  expected->right->left = new Node(5);
  expected->right->left->color = rbt::Color::BLACK;
  expected->right->right = new Node(7);
  expected->right->right->color = rbt::Color::BLACK;

  printf("===== Actual Tree =====\n");
  inorder(tree->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree->root(), expected);
  delete tree;
  delete expected;
}

TEST_F(RBTreeTest, InsertRightRight) {
  RBTree *tree = new RBTree();
  for (int i = 0; i < 8; i++) {
    tree->insert(i);
  }

  Node *expected = new Node(3);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(1);
  expected->left->color = rbt::Color::RED;
  expected->left->left = new Node(0);
  expected->left->left->color = rbt::Color::BLACK;
  expected->left->right = new Node(2);
  expected->left->right->color = rbt::Color::BLACK;

  expected->right = new Node(5);
  expected->right->color = rbt::Color::RED;
  expected->right->left = new Node(4);
  expected->right->left->color = rbt::Color::BLACK;
  expected->right->right = new Node(6);
  expected->right->right->color = rbt::Color::BLACK;
  expected->right->right->right = new Node(7);
  expected->right->right->right->color = rbt::Color::RED;

  printf("===== Actual Tree =====\n");
  inorder(tree->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree->root(), expected);
  delete tree;
  delete expected;
}

TEST_F(RBTreeTest, InsertLeftRight) {
  RBTree *tree = new RBTree();
  tree->insert(0);
  tree->insert(1);
  tree->insert(2);
  tree->insert(4);
  tree->insert(3);

  Node *expected = new Node(1);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(0);
  expected->left->color = rbt::Color::BLACK;

  expected->right = new Node(3);
  expected->right->color = rbt::Color::BLACK;
  expected->right->left = new Node(2);
  expected->right->left->color = rbt::Color::RED;
  expected->right->right = new Node(4);
  expected->right->right->color = rbt::Color::RED;

  printf("===== Actual Tree =====\n");
  inorder(tree->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree->root(), expected);
  delete tree;
  delete expected;
}

TEST_F(RBTreeTest, InsertRightLeft) {
  RBTree *tree = new RBTree();
  tree->insert(4);
  tree->insert(3);
  tree->insert(2);
  tree->insert(0);
  tree->insert(1);

  Node *expected = new Node(3);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(1);
  expected->left->color = rbt::Color::BLACK;
  expected->left->left = new Node(0);
  expected->left->left->color = rbt::Color::RED;
  expected->left->right = new Node(2);
  expected->left->right->color = rbt::Color::RED;

  expected->right = new Node(4);
  expected->right->color = rbt::Color::BLACK;

  printf("===== Actual Tree =====\n");
  inorder(tree->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree->root(), expected);
  delete tree;
  delete expected;
}

TEST_F(RBTreeTest, DeleteRedLeaf) {
  tree_->remove(5);
  tree_->remove(27);

  Node *expected = new Node(15);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(8);
  expected->left->color = rbt::Color::RED;
  expected->left->left = new Node(4);
  expected->left->left->color = rbt::Color::BLACK;
  expected->left->left->left = nullptr;
  expected->left->left->left = new Node(3);
  expected->left->left->left->color = rbt::Color::RED;
  expected->left->right = new Node(12);
  expected->left->right->color = rbt::Color::BLACK;

  expected->right = new Node(25);
  expected->right->color = rbt::Color::RED;
  expected->right->left = new Node(20);
  expected->right->left->color = rbt::Color::BLACK;
  expected->right->right = new Node(30);
  expected->right->right->color = rbt::Color::BLACK;

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
  delete expected;
}

TEST_F(RBTreeTest, DeleteOneChild) {
  tree_->remove(30);

  Node *expected = new Node(15);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(8);
  expected->left->color = rbt::Color::RED;
  expected->left->left = new Node(4);
  expected->left->left->color = rbt::Color::BLACK;
  expected->left->left->left = new Node(3);
  expected->left->left->left->color = rbt::Color::RED;
  expected->left->left->right = new Node(5);
  expected->left->left->right->color = rbt::Color::RED;
  expected->left->right = new Node(12);
  expected->left->right->color = rbt::Color::BLACK;

  expected->right = new Node(25);
  expected->right->color = rbt::Color::RED;
  expected->right->left = new Node(20);
  expected->right->left->color = rbt::Color::BLACK;
  expected->right->right = new Node(27);
  expected->right->right->color = rbt::Color::BLACK;

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
  delete expected;
}

TEST_F(RBTreeTest, DeleteBlackSiblingLeftLeft) {
  tree_->remove(12);

  Node *expected = new Node(15);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(4);
  expected->left->color = rbt::Color::RED;
  expected->left->left = new Node(3);
  expected->left->left->color = rbt::Color::BLACK;
  expected->left->right = new Node(8);
  expected->left->right->color = rbt::Color::BLACK;
  expected->left->right->left = new Node(5);
  expected->left->right->left->color = rbt::Color::RED;
  expected->left->right->right = nullptr;

  expected->right = new Node(25);
  expected->right->color = rbt::Color::RED;
  expected->right->left = new Node(20);
  expected->right->left->color = rbt::Color::BLACK;
  expected->right->right = new Node(30);
  expected->right->right->color = rbt::Color::BLACK;
  expected->right->right->left = new Node(27);
  expected->right->right->left->color = rbt::Color::RED;

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
  delete expected;
}

TEST_F(RBTreeTest, DeleteBlackSiblingLeftRight) {
  tree_->remove(3);
  tree_->remove(12);

  Node *expected = new Node(15);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(5);
  expected->left->color = rbt::Color::RED;
  expected->left->left = new Node(4);
  expected->left->left->color = rbt::Color::BLACK;
  expected->left->right = new Node(8);
  expected->left->right->color = rbt::Color::BLACK;

  expected->right = new Node(25);
  expected->right->color = rbt::Color::RED;
  expected->right->left = new Node(20);
  expected->right->left->color = rbt::Color::BLACK;
  expected->right->right = new Node(30);
  expected->right->right->color = rbt::Color::BLACK;
  expected->right->right->left = new Node(27);
  expected->right->right->left->color = rbt::Color::RED;

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
  delete expected;
}

TEST_F(RBTreeTest, DeleteFull) {
  tree_->remove(27);
  tree_->remove(25);

  Node *expected = new Node(15);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(8);
  expected->left->color = rbt::Color::RED;
  expected->left->left = new Node(4);
  expected->left->left->color = rbt::Color::BLACK;
  expected->left->left->left = new Node(3);
  expected->left->left->left->color = rbt::Color::RED;
  expected->left->left->right = new Node(5);
  expected->left->left->right->color = rbt::Color::RED;
  expected->left->right = new Node(12);
  expected->left->right->color = rbt::Color::BLACK;

  expected->right = new Node(30);
  expected->right->color = rbt::Color::BLACK;
  expected->right->left = new Node(20);
  expected->right->left->color = rbt::Color::RED;

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
  delete expected;
}

TEST_F(RBTreeTest, DeleteBlackFull) {
  tree_->remove(3);
  tree_->remove(12);
  tree_->remove(27);
  tree_->remove(30);
  tree_->remove(20);
  tree_->remove(25);

  Node *expected = new Node(5);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(4);
  expected->left->color = rbt::Color::BLACK;

  expected->right = new Node(15);
  expected->right->color = rbt::Color::BLACK;
  expected->right->left = new Node(8);
  expected->right->left->color = rbt::Color::RED;

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
  delete expected;
}

TEST_F(RBTreeTest, DeleteRoot) {
  tree_->find(8)->color = rbt::Color::BLACK;
  tree_->find(25)->color = rbt::Color::BLACK;
  tree_->remove(27);
  tree_->remove(15);

  Node *expected = new Node(20);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(8);
  expected->left->color = rbt::Color::RED;
  expected->left->left = new Node(4);
  expected->left->left->color = rbt::Color::BLACK;
  expected->left->left->left = new Node(3);
  expected->left->left->left->color = rbt::Color::RED;
  expected->left->left->right = new Node(5);
  expected->left->left->right->color = rbt::Color::RED;
  expected->left->right = new Node(12);
  expected->left->right->color = rbt::Color::BLACK;

  expected->right = new Node(25);
  expected->right->color = rbt::Color::BLACK;
  expected->right->right = new Node(30);
  expected->right->right->color = rbt::Color::RED;

  printf("===== Actual Tree =====\n");
  inorder(tree_->root());
  printf("\n===== Expected Tree =====\n");
  inorder(expected);
  match_trees(tree_->root(), expected);
  delete expected;
}

TEST_F(RBTreeTest, DeleteNonExistent) {
  ASSERT_TRUE(tree_);
  tree_->remove(-100);

  Node *expected = new Node(15);
  expected->color = rbt::Color::BLACK;

  expected->left = new Node(8);
  expected->left->color = rbt::Color::RED;
  expected->left->left = new Node(4);
  expected->left->left->color = rbt::Color::BLACK;
  expected->left->left->left = new Node(3);
  expected->left->left->left->color = rbt::Color::RED;
  expected->left->left->right = new Node(5);
  expected->left->left->right->color = rbt::Color::RED;
  expected->left->right = new Node(12);
  expected->left->right->color = rbt::Color::BLACK;

  expected->right = new Node(25);
  expected->right->color = rbt::Color::RED;
  expected->right->left = new Node(20);
  expected->right->left->color = rbt::Color::BLACK;
  expected->right->right = new Node(30);
  expected->right->right->color = rbt::Color::BLACK;
  expected->right->right->left = new Node(27);
  expected->right->right->left->color = rbt::Color::RED;

  match_trees(tree_->root(), expected);
}

TEST_F(RBTreeTest, SearchExistent) {
  ASSERT_TRUE(tree_);
  rbt::Node *search = tree_->find(30);
  ASSERT_TRUE(search);
}

TEST_F(RBTreeTest, SearchNonExistent) {
  ASSERT_TRUE(tree_);
  rbt::Node *search = tree_->find(-100);
  ASSERT_FALSE(search);
}
