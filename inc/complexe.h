#ifndef COMPLEXE_H
#define COMPLEXE_H

#include "common.h"

typedef union {
    union {
        double ztab[2];
        struct {
            double real;
            double imaginary;
        } zReIm;
    } alg;
    struct {
        double norme;
        double argument;
    } exp;
} complexe_t;

complexe_t complexe_new(double real, double imaginary);

#define real_new(nbre) complexe_new(nbre, 0)

#define imaginary_new(nbre) complexe_new(0, nbre)

bool complexe_is_null(complexe_t z);

bool complexe_is_real(complexe_t z);

bool complexe_is_imaginary(complexe_t z);

double getReal(complexe_t z);

double getImaginary(complexe_t z);

complexe_t complexe_inv(complexe_t z);

complexe_t complexe_alg2exp(complexe_t z);

complexe_t complexe_exp2alg(complexe_t z);

complexe_t complexe_add(complexe_t z1, complexe_t z2);

complexe_t complexe_mult(complexe_t z1, complexe_t z2);

complexe_t complexe_div(complexe_t z1, complexe_t z2);

complexe_t complexe_pow(complexe_t z, size_t pow);

void complexe_print(complexe_t z);

void complexe_mem_view(complexe_t z);

#endif /* end of include guard: COMPLEXE_H */
