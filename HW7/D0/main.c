#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGHT 256
#define MAX_STRING_LENGHT 10001

typedef struct List {
  char word[MAX_WORD_LENGHT];
  struct List *next;
} List;

// Добавление элемента в конец списка
int add_to_list(List **head, const char *word) {
  List *new_node = calloc(1, sizeof(List));
  if (!new_node) {
    return 0;
  }
  // Add data
  strcpy(new_node->word, word);
  // If emply list
  if (*head == NULL) {
    *head = new_node; // New head
  } else {
    List *current = *head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
  return 1;
}

// Обмен значениями двух элементов списка
void swap_elements(List *a, List *b) {
  char temp[MAX_WORD_LENGHT];
  strcpy(temp, a->word);
  strcpy(a->word, b->word);
  strcpy(b->word, temp);
}

// Печать списка
void print_list(List *head) {
  List *current = head;
  while (current != NULL) {
    printf("%s ", current->word);
    current = current->next;
  }
  printf("\n");
}

// Сортировка списка по алфавиту методом пузырька
void sort_list(List *head) {
  if (!head)
    return;

  List *i, *j;
  for (i = head; i != NULL; i = i->next) {
    for (j = i->next; j != NULL; j = j->next) {
      if (strcmp(i->word, j->word) > 0) {
        swap_elements(i, j);
      }
    }
  }
}

// Освобождение памяти списка
void delete_list(List **head) {
  List *current = *head;
  while (current != NULL) {
    List *next = current->next;
    free(current);
    current = next;
  }
  *head = NULL;
}

int main() {
  char input[MAX_STRING_LENGHT];
  // Read string
  fgets(input, sizeof(input), stdin);

  // Remove \n from string
  input[strcspn(input, "\r\n")] = '\0';
  // Remove . from string
  input[strcspn(input, ".")] = '\0';

  List *head = NULL;

  // Separate sting by space
  char *token = strtok(input, " ");

  while (token != NULL) {
    add_to_list(&head, token);
    token = strtok(NULL, " ");
  }

  sort_list(head);

  print_list(head);

  delete_list(&head);
  return 0;
}