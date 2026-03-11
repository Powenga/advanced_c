#include <math.h>
#include <roots.h>
#include <stdio.h>

#define EPS 0.0001

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

float integral(function f, float a, float b, float eps);

int main() {

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
  return 0;
}