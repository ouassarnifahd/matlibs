#ifndef VECTORS_H
#define VECTORS_H

#include "common.h"
#include "complexe.h"
#include "entity.h"

typedef struct vect {
    size_t size;
    math_entity_t ent;
    void* vector;
}* vector_t;

vector_t vect_zero(size_t size, math_entity_t ent);

vector_t vect_one(size_t size, math_entity_t ent);

vector_t vect_new(size_t size, math_entity_t ent, ...);

size_t getSize(vector_t vect);

void vect_delete(vector_t vect);

void vect_add(const vector_t vect1, const vector_t vect2, vector_t res, void (*add)(const void*, const void*, void*));

vector_t vect_mult(vector_t vect, void (*mult)(void*, void*));

vector_t vect_mult_vect(const vector_t vect1, const vector_t vect2, vector_t res, void (*mult)(const void*, const void*, void*));

vector_t vect_cauchy_mult(vector_t vect1, vector_t vect2);

complexe_t vect_dot(vector_t vect1, vector_t vect2 );

complexe_t vect_sigma(vector_t vect);

complexe_t vect_pigma(vector_t vect);

#endif /* end of include guard: VECTORS_H */
