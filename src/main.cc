#include <stdio.h>
#include <stdlib.h>

#include "data-structures/bst.h"
#include "data-structures/llist.h"

void inorder(BSTNode *root, int depth);
void linked_list_test();
void binary_search_tree_test();

int main() {
  printf("===========\n");
  printf("Linked List\n");
  printf("===========\n");
  linked_list_test();
  printf("\n\n");
  printf("==================\n");
  printf("Binary Search Tree\n");
  printf("==================\n");
  binary_search_tree_test();
  printf("\n");
}

void inorder(BSTNode *root, int depth = 0) {
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

void linked_list_test() {
  LLNode *head = nullptr;
  for (int i = 0; i < 10; i++) {
    ll_insert(&head, i);
  }

  int i = 9;
  while (head && i > 0) {
    printf("(%d)->", head->data);
    LLNode *del = head;
    head = head->next;
    free(del);
    i--;
  }

  printf("(NULL)\n");
}

void binary_search_tree_test() {
  BSTNode *root = nullptr;
  bst_insert(&root, 4);

  bst_insert(&root, 2);
  bst_insert(&root, 1);
  bst_insert(&root, 3);

  bst_insert(&root, 6);
  bst_insert(&root, 5);
  bst_insert(&root, 7);

  inorder(root);

  bst_destroy(&root);
}
