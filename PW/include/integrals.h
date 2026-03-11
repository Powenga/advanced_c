#ifndef INTEGRALS_H
#define INTEGRALS_H

#include <stdio.h>

typedef float (*function)(float);

float integral_square(function f, float a, float b, size_t count);
float integral_trapzoid(function f, float a, float b, size_t count);
float integral_simpson(function f, float a, float b, size_t count);
float integral_monte_carlo(function f, float a, float b, float h, size_t count);
float integral_monte_carlo_expectation(function f, float a, float b,
                                       size_t count);
float integral_stratified(function f, float a, float b, size_t count);

#endif