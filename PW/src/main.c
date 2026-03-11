#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main() {
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
  // f2 & f4
  float root_2_3 = root_bin(f2, f3, 2, 4, EPS, &stepcount3);

  printf("%.7f %d\n", root_1_3, stepcount2);
  printf("%.7f %d\n", root_1_2, stepcount1);
  printf("%.7f %d\n", root_2_3, stepcount3);

  // Areas
  // f1
  float area1 = integral_trapzoid(f1, root_1_3, root_1_2, INTEGRAL_COUNT);
  float area11 = integral_simpson(f1, root_1_3, root_1_2, INTEGRAL_COUNT);
  float area12 = integral_monte_carlo(f1, root_1_3, root_1_2, 6, 10000);
  float area13 =
      integral_monte_carlo_expectation(f1, root_1_3, root_1_2, 10000);
  float area14 = integral_stratified(f1, root_1_3, root_1_2, 10000);
  // f2
  float area2 = integral_trapzoid(f2, root_2_3, root_1_2, INTEGRAL_COUNT);
  float area22 = integral_simpson(f2, root_2_3, root_1_2, INTEGRAL_COUNT);
  // f3
  float area3 = integral_trapzoid(f3, root_1_3, root_2_3, INTEGRAL_COUNT);
  float area33 = integral_simpson(f3, root_1_3, root_2_3, INTEGRAL_COUNT);

  printf("%.7f\n", area1);
  printf("%.7f\n", area11);
  printf("%.7f\n", area12);
  printf("%.7f\n", area13);
  printf("%.7f\n", area14);
  printf("%.7f\n", area2);
  printf("%.7f\n", area22);
  printf("%.7f\n", area3);
  printf("%.7f\n", area33);
  printf("%.7f\n", area1 - area2 - area3);
  printf("%.7f\n", area11 - area22 - area33);

  return 0;
}