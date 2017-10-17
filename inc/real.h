#ifndef REAL_H
#define REAL_H

#include "common.h"

#ifdef __x86_64__

#define SIZE_REAL sizeof(double)
#define PRINT_REAL "%7.2lf"

typedef double* real_t;

#elif __i386__

#define SIZE_REAL sizeof(float)
#define PRINT_REAL "%5.2f"

typedef float* real_t;

#endif

void* real_new(double x);

void real_delete(void* x);

void real_zero(void* x);

void real_one(void* x);

void real_inv(void* x);

bool real_is_null(const void* x);

bool real_is_positive(const void* x);

bool real_is_negative(const void* x);

void real_add(const void* x1, const void* x2, void* res);

void real_sub(const void* x1, const void* x2, void* res);

void real_mult(const void* x1, const void* x2, void* res);

void real_div(const void* x1, const void* x2, void* res);

void real_print(const void* x);

#endif /* end of include guard: REAL_H */
