#ifndef ALGLIB_H
#define ALGLIB_H

#include "structures/entity.h"
#include "structures/real.h"
#include "structures/complexe.h"
#include "structures/vectors.h"
#include "structures/polynome.h"

// REAL NUMBERS

static const struct math real_entity = {
    SIZE_REAL,
    (math_new_t)real_new,
    real_delete, real_zero, real_one, real_inv,
    real_is_null, real_is_positive, real_is_negative,
    real_add, real_sub, real_mult, real_div,
    math_accumulator, real_print
};

typedef void* (*math_real_new_t) (double);

// COMPLEXE NUMBERS

static const struct math complexe_entity = {
    SIZE_COMPLEXE,
    (math_new_t)complexe_new,
    complexe_delete, complexe_zero, complexe_one, complexe_inv,
    complexe_is_null, math_test, math_test,
    complexe_add, complexe_sub, complexe_mult, complexe_div,
    math_accumulator, complexe_print
};

typedef void* (*math_complexe_new_t) (double, double);

// VECTORS
// LINE

static const struct math vect_ligne_entity = {
    SIZE_VECT,
    (math_new_t)vect_new,
    vect_delete, vect_zero, vect_one, vect_inv,
    vect_is_null, math_test, math_test,
    vect_add, vect_sub, vect_mult, math_operation,
    math_accumulator, vect_print_ligne
};

// COLUMN

static const struct math vect_colonne_entity = {
    SIZE_VECT,
    (math_new_t)vect_new,
    vect_delete, vect_zero, vect_one, vect_inv,
    vect_is_null, math_test, math_test,
    vect_add, vect_sub, vect_mult, math_operation,
    math_accumulator, vect_print_colonne
};

typedef void* (*math_vect_new_t) (size_t, math_entity_t, ...);

// POLYNOME

static const struct math polynome_entity = {
    SIZE_VECT,
    (math_new_t)vect_new,
    vect_delete, vect_zero, vect_one, vect_inv,
    vect_is_null, math_test, math_test,
    vect_add, vect_sub, vect_mult, math_operation,
    math_accumulator, polynome_print
};

// MATRIX



#endif /* end of include guard: ALGLIB_H */
