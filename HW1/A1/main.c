#include <stdio.h>

#define ALPHABET_SIZE 26
#define CAPITAL_A_POSTION 65
#define LOWERCASE_A_POSTION 97

int main(int argc, char const *argv[]) {
  int size;
  char c;

  scanf("%d", &size);

  if (size < 0) {
    printf("First number must be non negative.");
    return 1;
  }

  do {
    scanf("%c", &c);
    if (c >= 'A' && c <= 'Z') {
      printf("%c", (c - CAPITAL_A_POSTION + size) % ALPHABET_SIZE +
                       CAPITAL_A_POSTION);
      continue;
    }
    if (c >= 'a' && c <= 'z') {
      printf("%c", (c - LOWERCASE_A_POSTION + size) % ALPHABET_SIZE +
                       LOWERCASE_A_POSTION);
      continue;
    }
    printf("%c", c);
  } while (c != '.');

  return 0;
}
