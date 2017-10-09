#ifndef POLYNOME_H
#define POLYNOME_H

#include "common.h"
#include "vectors.h"

#define MAX_DEG 1000

typedef vector_t polynome_t;

#define polynome_zero(deg) vect_zero(deg + 1)

#define polynome_one(deg) vect_one(deg + 1)

#define polynome_new(deg, ...) vect_new(deg + 1, ##__VA_ARGS__)

#define polynome_delete(p) vect_delete(p)

polynome_t polynome_add(polynome_t p1, polynome_t p2);

#define polynome_mult(p, a) vect_mult(p, a)

#define polynome_mult_polynome(p1, p2) vect_cauchy_mult(p1, p2)

polynome_t polynome_pow(polynome_t p, size_t n);

polynome_t polynome_diff(polynome_t p);

polynome_t polynome_diff_ordre_n(polynome_t p, size_t n);

void polynome_print(polynome_t p, char* variable);

complexe_t polynomial_fonction(polynome_t p, complexe_t x);

vector_t polynome_racines(polynome_t p);

#endif /* end of include guard: POLYNOME_H */
