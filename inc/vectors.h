#ifndef VECTORS_H
#define VECTORS_H

#include "common.h"
#include "entity.h"

typedef struct vect {
    size_t size;
    math_entity_t ent;
    void* vector;
}* vector_t;

#define SIZE_VECT sizeof(struct vect)

void* vect_new(size_t size, math_entity_t ent, ...);

void vect_delete(void* vect);

void vect_zero(void* x);

void vect_one(void* x);

void vect_inv(void* x);

void vect_add(const void* vect1, const void* vect2, void* res);

void vect_sub(const void* vect1, const void* vect2, void* res);

void vect_mult(const void* vect, const void* scalar, void* res);

void vect_cauchy_mult(const void* vect1, const void* vect2, void* res);

void vect_dot(const void* vect1, const void* vect2 , void* res);

void vect_print_colonne(const void* x);

void vect_print_ligne(const void* x);

#endif /* end of include guard: VECTORS_H */
