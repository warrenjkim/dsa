#include "data-structures/trees/bst.h"

#include <stdio.h>
#include <stdlib.h>

static BSTNode *successor(BSTNode *root) {
  BSTNode *successor = root->right;
  while (successor && successor->left) {
    successor = successor->left;
  }

  return successor;
}
static BSTNode *node_init(const int data) {
  BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
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

  if (!((*root)->left) || !((*root)->right)) {
    BSTNode *del = (*root)->left ? (*root)->left : (*root)->right;
    if (!del) {
      free(*root);
      *root = NULL;
    } else {
      **root = *del;
      free(del);
    }

    return;
  }

  BSTNode *del = successor(*root);
  (*root)->data = del->data;
  bst_delete(&((*root)->right), del->data);
}

BSTNode *bst_find(BSTNode **root, const int target) {
  if (!*root) {
    return NULL;
  }

  if (target < (*root)->data) {
    return bst_find(&(*root)->left, target);
  } else if (target > (*root)->data) {
    return bst_find(&(*root)->right, target);
  }

  return *root;
}
