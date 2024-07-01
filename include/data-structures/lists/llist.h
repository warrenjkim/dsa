#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LLNode {
  int data;
  struct LLNode *next;
} LLNode;

void ll_insert(LLNode **head, const int data);
void ll_delete(LLNode **head, const int target);

#ifdef __cplusplus
}
#endif

#endif  // !LINKED_LIST_H
