#ifndef COMPLEXE_H
#define COMPLEXE_H

#include "common.h"
#include "real.h"

typedef union complexe {
    union {
        real_t ztab[2];
        struct {
            real_t real;
            real_t imaginary;
        } zReIm;
    } alg;
    struct {
        real_t norme;
        real_t argument;
    } exp;
} *complexe_t;

#define SIZE_COMPLEXE sizeof(union complexe)

void* complexe_new(double real, double imaginary);

void complexe_delete(void* z);

void complexe_zero(void* z);

void complexe_one(void* z);

void complexe_i(void* z);

void complexe_inv(void* z);

bool complexe_is_null(const void* z);

bool complexe_is_real(const void* z);

bool complexe_is_imaginary(const void* z);

void complexe_add(const void* z1, const void* z2, void* res);

void complexe_sub(const void* z1, const void* z2, void* res);

void complexe_mult(const void* z1, const void* z2, void* res);

void complexe_div(const void* z1, const void* z2, void* res);

void complexe_pow(const void* z, size_t pow, void* res);

void complexe_print(const void* z);

#endif /* end of include guard: COMPLEXE_H */
