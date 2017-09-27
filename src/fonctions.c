#include "fonctions.h"

// Complexe
complexe_t complexe_pow2(complexe_t z) {
    return complexe_mult(z, z);
}

complexe_t complexe_sqrt(complexe_t z) {
    return real_new(0);
}

complexe_t fcomplexe_diff_ordre_n(fcomplexe_t fx, size_t n, complexe_t x0) {
    if (n == 0) {
        return fx(x0);
    } else if (n == 1) {
        return complexe_div(complexe_add(fx(complexe_add(x0, real_new(STEP))), complexe_inv(fx(complexe_add(x0, complexe_inv(real_new(STEP)))))), real_new(2 * STEP));
    } else {
        return complexe_div(complexe_add(fcomplexe_diff_ordre_n(fx, n - 1, complexe_add(x0, real_new(STEP))), complexe_inv(fcomplexe_diff_ordre_n(fx, n - 1,complexe_add(x0, complexe_inv(real_new(STEP)))))), real_new(2 * STEP));
    }
}

// Vector
vector_t vect_pow2(vector_t vect) {
    vector_t pow2 = vect_zero(vect.size);
    for (size_t i = 0; i < vect.size; i++) {
        pow2.vector[i] = complexe_pow2(vect.vector[i]);
    }
    return pow2;
}

// Polynome
polynome_t taylor_fonction(fcomplexe_t fx, size_t ordre, complexe_t a) {
    polynome_t taylor = polynome_zero(ordre);
    polynome_t tmp = polynome_new(1, complexe_inv(a), real_new(1));
    polynome_t tmp_power = polynome_zero(ordre);
    tmp_power = polynome_add(tmp_power, tmp);
    unsigned int fact = 1;
    for (size_t i = 0; i < ordre; i++) {
        printf("fact(%zu) = %u\n", i, fact);
        printf("P%zu = ", i); polynome_print(tmp_power, "X");
        tmp_power = polynome_mult_polynome(tmp_power, tmp);
        printf("T%zu = ", i); polynome_print(taylor, "X");
        taylor = polynome_add(taylor, polynome_mult(tmp_power, complexe_div(fcomplexe_diff_ordre_n(fx, i, a), real_new(fact))));
        fact *= i + 1;
    }
    polynome_delete(tmp);
    polynome_delete(tmp_power);
    return taylor;
}

// fonctions

// fcomplexe fcomplexe_o(fcomplexe gx, fcomplexe fx) {
//     return (*gx)(fx);
// }

// fcomplexe fcomplexe_differentiate(fcomplexe fx) {
//     switch (fx) {
//         case complexe_cos:
//             return fcomplexe_o(complexe_inv, complexe_sin);
//         case complexe_sin:
//             return complexe_cos;
//         case complexe_cosh:
//             return complexe_sinh;
//         case complexe_sinh:
//             return complexe_cosh;
//         case complexe_exp:
//             return complexe_exp;
//         case complexe_log:
//             // return NULL;
//     }
// }

#ifdef DEBUG
#include <math.h>

complexe_t complexe_sin(complexe_t z) {
    return real_new(cos(z.alg.zReIm.real));
}

int main(int argc, char const *argv[]) {
    polynome_t p = polynome_new(1, real_new(1), real_new(1));
    printf("P  = "); polynome_print(p, "X");
    polynome_t pa = polynome_pow(p, 2);
    printf("Pa = "); polynome_print(pa, "X");
    polynome_delete(p);
    polynome_delete(pa);
    // polynome_t polynome_sin = taylor_fonction(complexe_sin, 5, real_new(1));
    // polynome_print(polynome_sin, "X");
    // complexe_t sin1 = polynomial_fonction(polynome_sin, real_new(1));
    // complexe_mem_view(sin1);
    return 0;
}
#endif
