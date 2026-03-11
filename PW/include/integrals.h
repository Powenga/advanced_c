#ifndef INTEGRALS_H
#define INTEGRALS_H

typedef float (*function)(float);

float integral_square(function f, float a, float b, size_t count);

#endif