#include <integrals.h>
#include <stdio.h>

float integral_square(function f, float a, float b, size_t count) {
  float result = 0;
  float x_step = (b - a) / count;
  for (size_t i = 0; i < count; i++, a += x_step) {
    result += f(a);
  }

  return result;
};