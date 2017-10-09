#ifndef COMMON_H
#define COMMON_H

#include <stdarg.h>  // args ...
#include <stdbool.h> // bool
#include <stdlib.h>  // malloc
#include <stdio.h>   // print
#include <string.h>  // Temporary (memcpy)

#define PI 3.1415926536

#define Mat_size(data) printf("%lu Octet\n", sizeof(data))
#define Mat_max(x,y) x >= y ? x : y
#define Mat_min(x,y) x <= y ? x : y
#define Mat_signe(x) x < 0
#define Mat_abs(x) Mat_max(x,-x)

double Mat_pow(double x, size_t n);
double Mat_root(double x, size_t n);

#endif /* end of include guard: COMMON_H */
