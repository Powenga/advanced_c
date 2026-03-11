#include <math.h>
#include <roots.h>

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