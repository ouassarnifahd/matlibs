#ifndef VECTORS_H
#define VECTORS_H

#include "common.h"
#include "complexe.h"

typedef struct {
    size_t size;
    complexe_t* vector;
} vector_t;

vector_t vect_zero(size_t size);

vector_t vect_one(size_t size);

vector_t vect_new(size_t size, ...);

size_t getSize(vector_t vect);

void vect_delete(vector_t vect);

vector_t vect_add(vector_t vect1, vector_t vect2);

vector_t vect_mult(vector_t vect, complexe_t scalar);

vector_t vect_mult_vect(vector_t vect1, vector_t vect2);

vector_t vect_cauchy_mult(vector_t vect1, vector_t vect2);

complexe_t vect_dot(vector_t vect1, vector_t vect2);

complexe_t vect_sigma(vector_t vect);

complexe_t vect_pigma(vector_t vect);

#endif /* end of include guard: VECTORS_H */
