#ifndef COMPLEXE_H
#define COMPLEXE_H

#include "core/types.h"

typedef union complexe {
    union {
        sreal_t ztab[2];
        struct {
            sreal_t real;
            sreal_t imaginary;
        } zReIm;
    } alg;
    struct {
        sreal_t norme;
        sreal_t argument;
    } exp;
} scomplexe_t, *complexe_t;

scomplexe_t complexe_new(sreal_t real, sreal_t imaginary);

void complexe_zero(complexe_t z);

void complexe_one(complexe_t z);

void complexe_i(complexe_t z);

void complexe_inv(complexe_t z);

bool complexe_is_null(const complexe_t z);

bool complexe_is_real(const complexe_t z);

bool complexe_is_imaginary(const complexe_t z);

void complexe_swap(const complexe_t z1, const complexe_t z2);

void complexe_add(const complexe_t z1, const complexe_t z2, complexe_t res);

void complexe_sub(const complexe_t z1, const complexe_t z2, complexe_t res);

void complexe_mult(const complexe_t z1, const complexe_t z2, complexe_t res);

void complexe_div(const complexe_t z1, const complexe_t z2, complexe_t res);

void complexe_pow(const complexe_t z, size_t pow, complexe_t res);

void complexe_print(const complexe_t z);

#endif /* end of include guard: COMPLEXE_H */
