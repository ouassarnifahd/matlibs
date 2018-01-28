#ifndef RVECTOR_H
#define RVECTOR_H

#include "real.h"

typedef struct rvect {
    size_t size;
    real_t vector;
} *rvector_t;

#define SIZE_RVECT sizeof(struct rvect)

rvector_t rvect_init(size_t size);

rvector_t rvect_zero(size_t size);

rvector_t rvect_one(size_t size);

rvector_t rvect_new(size_t size, ...);

void rvect_delete(rvector_t vect);

bool rvect_is_null(const rvector_t vect);

bool rvect_is_real(const rvector_t vect);

rvector_t rvect_add(const rvector_t vect1, const rvector_t vect2);

rvector_t rvect_sub(const rvector_t vect1, const rvector_t vect2);

rvector_t rvect_mult(const rvector_t vect, const rvector_t vect2);

rvector_t rvect_conv(const rvector_t vect1, const rvector_t vect2);

sreal_t rvect_dot(const rvector_t vect1, const rvector_t vect2);

rvector_t rvect_scale(const rvector_t vect, sreal_t scalar);

void rvect_print_colonne(const rvector_t x);

void rvect_print_ligne(const rvector_t x);

#endif /* end of include guard: RVECTOR_H */
