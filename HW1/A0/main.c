#include <stdio.h>

int main(int argc, char const *argv[]) {
  int size, count = 0, input, max;
  scanf("%d", &size);

  if (size <= 0) {
    printf("First number must be positive.");
    return 1;
  }

  for (int i = 0; i < size; i++) {
    scanf("%d", &input);
    if (i == 0) {
      max = input;
      count = 1;
      continue;
    }
    if (input > max) {
      max = input;
      count = 1;
    } else if (input == max) {
      count++;
    }
  }

  printf("%d\n", count);

  return 0;
}
