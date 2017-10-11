#ifndef POLYNOME_H
#define POLYNOME_H

#include "common.h"
#include "vectors.h"

#define MAX_DEG 1000

typedef vector_t polynome_t;

#define polynome_zero(deg) vect_zero(deg + 1)

#define polynome_one(deg) vect_one(deg + 1)

#define polynome_new(deg, ent, ...) vect_new(deg + 1, ent, ##__VA_ARGS__)

#define polynome_delete(p) vect_delete(p)

#define polynome_add(p1, p2, res) vect_add(p1, p2, res)

#define polynome_sub(p1, p2, res) vect_sub(p1, p2, res)

#define polynome_mult(p, a, res) vect_mult(p, a, res)

#define polynome_mult_polynome(p1, p2, res) vect_cauchy_mult(p1, p2, res)

void polynome_pow(const void* p, size_t n, void* res);

void polynome_diff(const void* p, void* res);

void polynome_diff_ordre_n(const void* p, size_t n, void* res);

void polynome_print(polynome_t p, char* variable);

void polynomial_fonction(const void* p, const void* x, void* res);

void polynome_racines(const void* p);

#endif /* end of include guard: POLYNOME_H */
