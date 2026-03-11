#include <integrals.h>
#include <math.h>
#include <stdlib.h>

float integral_square(function f, float a, float b, size_t count) {
  float result = 0;
  float x_step = (b - a) / count;

  for (size_t i = 0; i < count; i++) {
    result += f(a);
    a += x_step;
  }

  return result * x_step;
};

float integral_trapzoid(function f, float a, float b, size_t count) {
  float result = 0;
  float x_step = (b - a) / count;

  for (size_t i = 0; i < count; i++) {
    float x = a + i * x_step;
    result += 0.5f * x_step * (f(x) + f(x + x_step));
  }

  return result;
};

float integral_simpson(function f, float a, float b, size_t count) {
  float result = 0;
  float x_step = (b - a) / count;

  for (size_t i = 0; i < count; i++) {
    float x = a + i * x_step;

    result +=
        x_step / 6.0f * (f(x) + 4.0f * f(x + x_step * 0.5f) + f(x + x_step));
  }

  return result;
};

float randf() {
  return (float)rand() / RAND_MAX;
}

float integral_monte_carlo(function f, float a, float b, float h,
                           size_t count) {
  size_t inner_count = 0;
  float width = fabs(b - a), height = h;
  for (size_t i = 0; i < count; i++) {
    float x = a + randf() * width;
    float y = randf() * height;

    if (y < f(x)) {
      inner_count++;
    }
  }
  return (float)inner_count / count * width * height;
};

float integral_monte_carlo_expectation(function f, float a, float b,
                                       size_t count) {
  float sum = 0;
  float width = b - a;

  for (size_t i = 0; i < count; i++) {
    float x = a + randf() * width;
    sum += f(x);
  }

  return width * sum / count;
}

float integral_stratified(function f, float a, float b, size_t count) {
  float width = (b - a) / count;
  float sum = 0;

  for (size_t i = 0; i < count; i++) {

    float x = a + (i + randf()) * width;

    sum += f(x);
  }

  return (b - a) * sum / count;
}
