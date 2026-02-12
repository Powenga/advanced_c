#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  uint32_t input, max = 0, mask = 0;
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

  mask = (1 << shift) - 1;

  for (int i = 0; i < 32; i++) {
    uint32_t res = input >> i & mask;
    if (res > max) {
      max = res;
    }
  }

  printf("%" PRIu32, max);

  return 0;
}
