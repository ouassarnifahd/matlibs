#ifndef COMMON_H
#define COMMON_H

#include <stdarg.h>  // args (...)
#include <stdbool.h> // bool defs
#include <stdlib.h>  // malloc & free
#include <stdio.h>   // printf
#include <string.h>  // memcpy & strcat

#include "error.h"   // handling errors/warnings/debug

#define Mat_PI 3.1415926536
#define Mat_exp 2.7182818285

#define Mat_size(data) printf("%lu Octet\n", sizeof(data))
#define Mat_max(x,y) x >= y ? x : y
#define Mat_min(x,y) x <= y ? x : y
#define Mat_signe(x) x < 0
#define Mat_abs(x) Mat_max(x,-x)

double Mat_pow(double x, size_t n);
double Mat_root(double x, size_t n);

#endif /* end of include guard: COMMON_H */
