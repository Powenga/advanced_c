#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cli.h>
#include <integrals.h>
#include <roots.h>

#define EPS 0.0001
#define INTEGRAL_COUNT 10000

// Functions
float f1(float x) {
  return 0.6 * x + 3;
}

float f2(float x) {
  return (x - 2) * (x - 2) * (x - 2) - 1;
}

float f3(float x) {
  return 3 / x;
}

int main(int argc, char *argv[]) {
  CliOptions options;
  if (!parse_cli(argc, argv, &options)) {
    print_cli_usage(argv[0]);
    return 0;
  }

  // Help message
  if (options.show_help) {
    print_help(argv[0]);
    return 0;
  }

  srand(time(NULL));

  // Intersection points
  // Intervals
  // f1 = f3 - [0, 2]
  // f1 = f2 - [2, 4]
  // f2 = f3 - [2, 4]

  int stepcount1 = 0;
  int stepcount2 = 0;
  int stepcount3 = 0;
  // f1 & f2
  float root_1_2 = root_bin(f1, f2, 2, 4, EPS, &stepcount1);
  // f1 & f3
  float root_1_3 = root_bin(f1, f3, 0, 2, EPS, &stepcount2);
  // f2 & f3
  float root_2_3 = root_bin(f2, f3, 2, 4, EPS, &stepcount3);

  if (options.show_interation_count) {
    printf("\nIteraction count:\n");
    printf("f1 & f2: %d\n", stepcount2);
    printf("f1 & f3: %d\n", stepcount1);
    printf("f2 & f3: %d\n", stepcount3);
    printf("-------------------------------\n");
  }

  if (options.show_intersection_dots) {
    printf("\nIntersection dots:\n");
    printf("f1 & f2: x=%.5f, y=%0.5f\n", root_1_2, f1(root_1_2));
    printf("f1 & f3: x=%.5f, y=%0.5f\n", root_1_3, f1(root_1_3));
    printf("f2 & f3: x=%.5f, y=%0.5f\n", root_2_3, f2(root_2_3));
    printf("-------------------------------\n");
  }

  // Areas
  // f1
  float area1 = integral_trapzoid(f1, root_1_3, root_1_2, INTEGRAL_COUNT);
  // f2
  float area2 = integral_trapzoid(f2, root_2_3, root_1_2, INTEGRAL_COUNT);
  // f3
  float area3 = integral_trapzoid(f3, root_1_3, root_2_3, INTEGRAL_COUNT);

  printf("\nArea: %.5f\n\n", area1 - area2 - area3);

  return 0;
}