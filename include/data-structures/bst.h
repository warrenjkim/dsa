#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BSTNode {
  int data;
  struct BSTNode *left;
  struct BSTNode *right;
} BSTNode;

void bst_destroy(BSTNode **root);
void bst_insert(BSTNode **root, const int data);
void bst_delete(BSTNode **root, const int target);
BSTNode *bst_find(BSTNode **root, const int target);

#ifdef __cplusplus
}
#endif

#endif  // !BINARY_SEARCH_TREE_H
