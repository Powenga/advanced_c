#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct list
{
  uint64_t address;
  size_t size;
  char comment[64];
  struct list *next;
} list;

uint64_t findMaxBlock(list *head)
{
  if (!head)
  {
    return 0;
  }
  list *ptr = head;
  size_t max = ptr->size;
  uint64_t result = ptr->address;

  ptr = ptr->next;

  while (ptr != NULL)
  {
    if (ptr->size > max)
    {
      max = ptr->size;
      result = ptr->address;
    }
    ptr = ptr->next;
  }

  return result;
}

int pushElem(list **head, uint64_t address, size_t size)
{
  list *ptr = calloc(1, sizeof(list));
  if (!ptr)
  {
    return 0;
  }
  ptr->address = address;
  ptr->size = size;
  ptr->next = NULL;

  if (!*head)
  {
    *head = ptr;
    return 1;
  }

  list *last = *head;

  while (last->next != NULL)
  {
    last = last->next;
  }
  last->next = ptr;
  return 1;
}

int initList(list **head)
{
  pushElem(head, 140525067852320, 1);
  pushElem(head, 140525067852328, 8);
  pushElem(head, 140525067852700, 100);
  pushElem(head, 140525067852360, 20);
  pushElem(head, 140525067852500, 21);
}

int main(int argc, char const *argv[])
{
  list *data = NULL;
  initList(&data);
  printf("%lld", findMaxBlock(data));
  return 0;
}
