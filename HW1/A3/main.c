#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  uint32_t input;
  int shift;

  scanf("%" SCNu32 " %d", &input, &shift);

  if (input < 0) {
    printf("First number must be non negative.");
    return 1;
  }

  if (shift < 1 || shift > 31) {
    printf("%u", shift);
    printf("Second number must be bigger than 0 and lesser than 32.");
    return 1;
  }

  printf("%" PRIu32, input ^ (input & ~((1 << shift) - 1)));

  return 0;
}
