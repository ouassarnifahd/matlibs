#ifndef REAL_H
#define REAL_H

#include "common.h"
#include "entity.h"

#define SIZE_REAL sizeof(double)

typedef double* real_t;

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

static const struct math real_entity = {
    SIZE_REAL,
    (math_new_t)real_new,
    real_delete, real_zero, real_one, real_inv,
    real_is_null, real_is_positive, real_is_negative,
    real_add, real_sub, real_mult, real_div,
    real_print
};

typedef void* (*math_real_new_t) (double);

#endif /* end of include guard: REAL_H */
