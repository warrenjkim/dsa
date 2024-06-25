#include "data-structures/llist.h"
#include <stdlib.h>
#include <stdio.h>

static LLNode *node_init(const int data) {
  LLNode *node = malloc(sizeof(LLNode));
  if (!node) {
    fprintf(stderr, "node_init() - malloc failed.");
    exit(EXIT_FAILURE);
  }

  node->data = data;
  node->next = NULL;

  return node;
}

void ll_insert(LLNode **head, const int data) {
  if (!*head) {
    *head = node_init(data);
    return;
  }

  LLNode *new_node = node_init(data);
  new_node->next = *head;
  *head = new_node;
}

void ll_delete(LLNode **head, const int target) {
  if (!*head) {
    return;
  }

  if ((*head)->data == target) {
    LLNode *next = *head;
    *head = (*head)->next;
    free(next);
    return;
  }

  if (!(*head)->next) {
    return;
  }

  ll_delete(&((*head)->next), target);
}
