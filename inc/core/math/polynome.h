#ifndef POLYNOME_H
#define POLYNOME_H

#include "cvector.h"

#define MAX_DEG 20

typedef enum {Positive, Negative} pow_t;

typedef struct root {
    size_t mult;
    scomplexe_t root;
} *root_t;

typedef struct polynome *polynome_t;

#define SIZE_POLYNOME sizeof(struct polynome)

polynome_t polynome_init(char variable, pow_t power);

polynome_t polynome_new(char variable, pow_t power, cvector_t vect);

void polynome_delete(polynome_t polynome);

bool polynome_is_complexe(const polynome_t polynome);

polynome_t polynome_add(const polynome_t polynome1, const polynome_t polynome2);

polynome_t polynome_sub(const polynome_t polynome1, const polynome_t polynome2);

polynome_t polynome_mult(const polynome_t polynome1, const polynome_t polynome2);

polynome_t polynome_pow(const polynome_t polynome, size_t power);

scomplexe_t polynomial_fonction(const polynome_t polynome, scomplexe_t x);

root_t polynome_racines(const polynome_t polynome);

void polynome_print(const polynome_t polynome);

#endif /* end of include guard: POLYNOME_H */
