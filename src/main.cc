#include "data-structures/llist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Node *head = NULL;
  for (int i = 0; i < 10; i++) {
    ll_insert(&head, i);
  }

  ll_delete(&head, 500);

  int i = 9;
  while (head && i > 0) {
    printf("head: %d\n", head->data);
    Node *del = head;
    head = head->next;
    free(del);
    i--;
  }
}
