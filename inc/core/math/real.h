#ifndef REAL_H
#define REAL_H

#include "core/types.h"

typedef sreal_t* real_t;

#define real_new(x) (sreal_t)x

void real_zero(real_t x);

void real_one(real_t x);

void real_inv(real_t x);

bool real_is_null(const real_t x);

bool real_is_positive(const real_t x);

bool real_is_negative(const real_t x);

void real_swap(const real_t x1, const real_t x2);

void real_add(const real_t x1, const real_t x2, real_t res);

void real_sub(const real_t x1, const real_t x2, real_t res);

void real_mult(const real_t x1, const real_t x2, real_t res);

void real_div(const real_t x1, const real_t x2, real_t res);

void real_pow(const real_t x, size_t power, real_t res);

void real_root(const real_t x, size_t root, real_t res);

void real_print(const real_t x);

#endif /* end of include guard: REAL_H */
