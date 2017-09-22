#include "fonctions.h"

#define MAX_DEG 1000

// Complexe
complexe_t fcomplexe_diff_ordre_n(fcomplexe_t fx, size_t n, complexe_t x0) {
    return real_new(1);
}

complexe_t complexe_inv(complexe_t z) {
    return complexe_mult(real_new(-1), z);
}

complexe_t complexe_pow2(complexe_t z) {
    return complexe_mult(z, z);
}

complexe_t complexe_sqrt(complexe_t z) {
    return real_new(0);
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
polynome_t taylor_fonction(fcomplexe_t fx, complexe_t a) {
    polynome_t taylor = polynome_zero(MAX_DEG);
    polynome_t tmp = polynome_new(1, real_new(complexe_inv(a)), real_new(1));
    polynome_t tmp_power = polynome_zero((tmp.size - 1) * n);
    power = polynome_add(power, p);
    complexe_t fact = real_new(1);
    for (size_t i = 0; i < taylor.size; i++) {
        fact = complexe_mult(fact, real_new(i + 1));
        tmp_power = polynome_mult_polynome(tmp, tmp_power);
        taylor = polynome_add(taylor, polynome_mult(tmp_power, fcomplexe_diff_ordre_n(fx, i, a)));
    }
    polynome_delete(tmp);
    polynome_delete(tmp_power);
    return taylor;
}

complexe_t polynomial_fonction(polynome_t p, complexe_t x) {
    complexe_t px = real_new(0);
    for (size_t i = 0; i < p.size; i++)
        px = complexe_add(px, complexe_mult(p.vector[i], complexe_pow(x,i)));
    return px;
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
int main(int argc, char const *argv[]) {

    return 0;
}
#endif
