#include <math.h>
#include <stdio.h>

#define EPS 0.0001

typedef float (*function)(float);

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

// Intervals
// f1 = f3 - [0, 2]
// f1 = f2 - [2, 4]
// f2 = f3 - [2, 4]

float root_simple(function f, function g, float a, float b, float eps,
                  int *stepcount) {
  float x, x_root, step, min_diff;
  *stepcount = 0;
  step = fabs(a - b) * eps;

  for (x = a; x < b; x += step, (*stepcount)++) {
    float current_diff = fabs(f(x) - g(x));

    if (x == a || current_diff < min_diff) {
      min_diff = current_diff;
      x_root = x;
    }
  }

  return x_root;
};

float root_bin(function f, function g, float a, float b, float eps,
               int *stepcount) {

  float result_a = f(a) - g(a);
  float result_b = f(b) - g(b);
  *stepcount = 0;

  if (result_a * result_b > 0) {
    return NAN;
  }

  float c, result_c;

  while (fabs(a - b) > eps) {
    (*stepcount)++;

    if (fabs(result_a) < eps) {
      return a;
    }

    if (fabs(result_b) < eps) {
      return b;
    }

    c = (a + b) / 2.0;
    result_c = f(c) - g(c);

    if (fabs(result_c) < eps) {
      return c;
    }

    // Корень слева, знак изменился
    if (result_a * result_c < 0) {
      b = c;
      result_b = result_c;
    } else {
      // Корень слева
      a = c;
      result_a = result_c;
    }
  }

  return (a + b) / 2.0;
  ;
};

float root_chord(function f, function g, float a, float b, float eps,
                 int *stepcount) {
  {
    *stepcount = 0;
    while (fabs(f(a) - f(b)) > eps) {
      (*stepcount)++;
      float h_a = f(a) - g(a);
      float h_b = f(b) - g(b);
      a = b - (b - a) * h_b / (h_b - h_a);
      b = a - (a - b) * h_a / (h_a - h_b);
    }
  }
  return b;
}

float integral(function f, float a, float b, float eps);

int main() {
  int stepcount1 = 0;
  int stepcount2 = 0;
  int stepcount3 = 0;
  float root1 = root_simple(f1, f2, 2, 4, EPS, &stepcount1);
  printf("%.7f %d\n", root1, stepcount1);
  float root2 = root_bin(f1, f2, 2, 4, EPS, &stepcount2);
  printf("%.7f %d\n", root2, stepcount2);
  float root3 = root_chord(f1, f2, 2, 4, EPS, &stepcount3);
  printf("%.7f %d\n", root3, stepcount3);
  return 0;
}