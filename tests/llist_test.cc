#include "data-structures/llist.h"

#include "gtest/gtest.h"

TEST(LinkedListTest, Insert) {
  LLNode *head = nullptr;
  ll_insert(&head, 0);

  ASSERT_TRUE(head);
  ASSERT_EQ(head->data, 0);

  free(head);
}

TEST(LinkedListTest, Delete) {
  LLNode *head = nullptr;
  for (int i = 0; i < 10; i++) {
    ll_insert(&head, i);
  }

  ASSERT_TRUE(head);
  ll_delete(&head, 5);
  ASSERT_TRUE(head);

  int i = 9;
  while (head && i > 0) {
    if (i == 5) {
      i--;
      continue;
    }

    ASSERT_TRUE(head);
    ASSERT_EQ(head->data, i);

    LLNode *del = head;
    head = head->next;
    free(del);
    i--;
  }

  ASSERT_EQ(i, 0);
}

TEST(LinkedListTest, DeleteHead) {
  LLNode *head = nullptr;
  for (int i = 0; i < 10; i++) {
    ll_insert(&head, i);
  }

  ASSERT_TRUE(head);
  ll_delete(&head, 9);
  ASSERT_TRUE(head);

  int i = 8;
  while (head && i > 0) {
    ASSERT_TRUE(head);
    ASSERT_EQ(head->data, i);

    LLNode *del = head;
    head = head->next;
    free(del);
    i--;
  }

  ASSERT_EQ(i, 0);
}

TEST(LinkedListTest, DeleteTail) {
  LLNode *head = nullptr;
  for (int i = 0; i < 10; i++) {
    ll_insert(&head, i);
  }

  ASSERT_TRUE(head);
  ll_delete(&head, 0);
  ASSERT_TRUE(head);

  int i = 9;
  while (head && i > 1) {
    ASSERT_TRUE(head);
    ASSERT_EQ(head->data, i);

    LLNode *del = head;
    head = head->next;
    free(del);
    i--;
  }

  ASSERT_EQ(i, 1);
}

TEST(LinkedListTest, DeleteNonExistent) {
  LLNode *head = nullptr;
  for (int i = 0; i < 10; i++) {
    ll_insert(&head, i);
  }

  ASSERT_TRUE(head);
  ll_delete(&head, 100);
  ASSERT_TRUE(head);

  int i = 9;
  while (head && i > 0) {
    ASSERT_TRUE(head);
    ASSERT_EQ(head->data, i);

    LLNode *del = head;
    head = head->next;
    free(del);
    i--;
  }

  ASSERT_EQ(i, 0);
}

