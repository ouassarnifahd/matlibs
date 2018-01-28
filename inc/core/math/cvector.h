#ifndef CVECTOR_H
#define CVECTOR_H

#include "complexe.h"

typedef struct cvect {
    size_t size;
    complexe_t vector;
} *cvector_t;

#define SIZE_CVECT sizeof(struct cvect)

cvector_t cvect_init(size_t size);

cvector_t cvect_zero(size_t size);

cvector_t cvect_one(size_t size);

cvector_t cvect_new(size_t size, ...);

void cvect_delete(cvector_t vect);

bool cvect_is_null(const cvector_t vect);

bool cvect_is_complexe(const cvector_t vect);

cvector_t cvect_add(const cvector_t vect1, const cvector_t vect2);

cvector_t cvect_sub(const cvector_t vect1, const cvector_t vect2);

cvector_t cvect_mult(const cvector_t vect1, const cvector_t vect2);

cvector_t cvect_scale(const cvector_t vect, scomplexe_t scalar);

cvector_t cvect_conv(const cvector_t vect1, const cvector_t vect2);

scomplexe_t cvect_dot(const cvector_t vect1, const cvector_t vect2);

void cvect_print_colonne(const cvector_t vect);

void cvect_print_ligne(const cvector_t vect);

#endif /* end of include guard: CVECTOR_H */
