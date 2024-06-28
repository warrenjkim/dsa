#include "data-structures/bst.h"

#include <stdio.h>
#include <stdlib.h>

static BSTNode *node_init(const int data) {
  BSTNode *node = malloc(sizeof(BSTNode));
  if (!node) {
    fprintf(stderr, "node_init() - malloc failed.");
    exit(EXIT_FAILURE);
  }

  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return node;
}

void bst_destroy(BSTNode **root) {
  if (!*root) {
    return;
  }

  if ((*root)->left) {
    bst_destroy(&((*root)->left));
  }

  if ((*root)->right) {
    bst_destroy(&((*root)->right));
  }

  free((*root));
  (*root) = NULL;
}

void bst_insert(BSTNode **root, const int data) {
  if (!*root) {
    *root = node_init(data);
    return;
  }

  if (data < (*root)->data) {
    bst_insert(&((*root)->left), data);
  } else if (data > (*root)->data) {
    bst_insert(&((*root)->right), data);
  }
}

void bst_delete(BSTNode **root, const int target) {
  if (!*root) {
    return;
  }

  if (target < (*root)->data) {
    bst_delete(&((*root)->left), target);
    return;
  } else if (target > (*root)->data) {
    bst_delete(&((*root)->right), target);
    return;
  }

  if (!((*root)->left)) {
    BSTNode *del = *root;
    *root = (*root)->right;
    free(del);
    return;
  }

  if (!((*root)->right)) {
    BSTNode *del = *root;
    *root = (*root)->left;
    free(del);
    return;
  }

  BSTNode *parent = *root;
  BSTNode *successor = (*root)->right;
  while (successor->left) {
    parent = successor;
    successor = successor->left;
  }

  (*root)->data = successor->data;

  if (parent->left == successor) {
    parent->left = successor->right;
  } else {
    parent->right = successor->right;
  }

  free(successor);
}

BSTNode *bst_find(BSTNode **root, const int target) {
  if (!(*root)) {
    return NULL;
  }

  if ((*root)->data == target) {
    return *root;
  }

  if (target < (*root)->data) {
    return bst_find(&(*root)->left, target);
  } else {
    return bst_find(&(*root)->right, target);
  }
}
