typedef float (*function)(float);

float root_simple(function f, function g, float a, float b, float eps,
                  int *stepcount);
float root_bin(function f, function g, float a, float b, float eps,
               int *stepcount);
float root_chord(function f, function g, float a, float b, float eps,
                 int *stepcount);