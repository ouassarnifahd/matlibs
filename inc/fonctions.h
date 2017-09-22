#ifndef FONCTION_H
#define FONCTION_H

#include "common.h"
#include "complexe.h"
#include "vectors.h"
#include "polynome.h"
#include "matrix.h"

// enum lib_taylor {
//     SIN,
//     COS,
//     TAN,
//     TOTAL
// };
//
// vector_t vect_get(unsigned int i) {
//     return vect_load(TAILLE_HEADER + i * (TAILLE_VECTOR + 1));
// }

// vect_get(SIN)

// C -> C
typedef complexe_t (*fcomplexe_t) (complexe_t);

// C -> C
typedef complexe_t (*fpolynomial_t) (polynome_t, complexe_t);

// Cn -> C (formes lineaires)
typedef complexe_t (*flinear_t) (vector_t);

// Cn -> Cn
typedef vector_t (*fvect_t) (vector_t);

// Cn2 -> Cn2
typedef matrix_t (*fmatrix_t) (matrix_t);

fcomplexe_t complexe_fonctions[] = {
    // base
    complexe_inv,
    complexe_pow2,
    complexe_sqrt,
    // Trigo
    complexe_sin,
    complexe_arcsin,
    complexe_cos,
    complexe_arccos,
    complexe_tan,
    complexe_arctan,
    // logarithmic
    complexe_log,
    complexe_exp,
    // hyperbolic
    complexe_sinh,
    complexe_arcsinh,
    complexe_cosh,
    complexe_arccosh,
    complexe_tanh,
    complexe_arctanh
};

fpolynomial_t polynome_fonctions[] = {
    &polynomial_fonction,
};

fvect_t vect_fonctions[] = {
    // base
    &vect_pow2,
    &vect_sqrt,
    &vect_norme,
    // Trigo
    &vect_sin,
    &vect_arcsin,
    &vect_cos,
    &vect_arccos,
    &vect_tan,
    &vect_arctan,
    // logarithmic
    &vect_log,
    &vect_exp,
    // hyperbolic
    &vect_sinh,
    &vect_arcsinh,
    &vect_cosh,
    &vect_arccosh,
    &vect_tanh,
    &vect_arctanh
};

complexe_t fcomplexe_diff_ordre_n(fcomplexe_t fx, size_t n, complexe_t x0);

complexe_t polynomial_fonction(polynome_t p, complexe_t x);

polynome_t taylor_fonction(fcomplexe_t fx, complexe_t a);

fcomplexe_t fcomplexe_o(fcomplexe_t gx, fcomplexe_t fx);

fcomplexe_t fcomplexe_differentiate(fcomplexe_t fx);

#endif /* end of include guard: FONCTION_H */
