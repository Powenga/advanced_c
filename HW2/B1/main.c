#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct list
{
  void *address;
  size_t size;
  char comment[64];
  struct list *next;
} list;

uint64_t totalMemoryUsage(list *head)
{
  if (!head)
  {
    return 0;
  }
  list *ptr = head;
  size_t size = ptr->size;

  ptr = ptr->next;

  while (ptr != NULL)
  {

    size += ptr->size;
    ptr = ptr->next;
  }

  return size;
}

int pushElem(list **head, size_t size)
{
  list *ptr = calloc(1, sizeof(list));
  if (!ptr)
  {
    return 0;
  }
  ptr->address = NULL;
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
  pushElem(head, 1);
  pushElem(head, 8);
  pushElem(head, 100);
  pushElem(head, 20);
  pushElem(head, 21);
}

int main(int argc, char const *argv[])
{
  list *data = NULL;
  initList(&data);
  printf("%lld", totalMemoryUsage(data));
  return 0;
}
