#include "polynome.h"

polynome_t polynome_pow(polynome_t p, size_t n) {
    polynome_t power = polynome_zero((p.size - 1) * n);
    power = polynome_add(power, p);
    for (size_t i = 0; i < n - 1; i++) {
        power = polynome_mult_polynome(p, power);
    }
    return power;
}

polynome_t polynome_diff(polynome_t p) {
    polynome_t diff = polynome_zero(p.size - 1);
    for (size_t i = 0; i < diff.size - 1; i++) {
        diff.vector[i] = complexe_mult(p.vector[i + 1], real_new(i + 1));
    }
    return diff;
}

polynome_t polynome_diff_ordre_n(polynome_t p, size_t n) {
    if (n == 0) {
        return p;
    } else if (n == 1) {
        return polynome_diff(p);
    } else {
        return polynome_diff_ordre_n(polynome_diff(p), n - 1);
    }
}

polynome_t polynome_taylor(polynome_t p, complexe_t a) {
    polynome_t taylor = polynome_zero(MAX_DEG);
    polynome_t tmp = polynome_new(1, real_new(complexe_inv(a)), real_new(1));
    polynome_t tmp_power = polynome_zero((tmp.size - 1) * n);
    power = polynome_add(power, p);
    complexe_t fact = real_new(1);
    for (size_t i = 0; i < taylor.size; i++) {
        fact = complexe_mult(fact, real_new(i + 1));
        tmp_power = polynome_mult_polynome(tmp, tmp_power);
        taylor = polynome_add(taylor, polynome_mult(tmp_power, complexe_div(fcomplexe_diff_ordre_n(fx, i, a), fact)));
    }
    polynome_delete(tmp);
    polynome_delete(tmp_power);
    return taylor;
}

void polynome_print(polynome_t p, char* variable) {
    for (size_t i = 0; i < p.size; i++) {
        if (!complexe_is_null(p.vector[i])) {
            if(i == 0) {
                complexe_print(p.vector[i]);
            } else {
                if (!(complexe_is_real(p.vector[i]) || complexe_is_imaginary(p.vector[i]))) printf(" + (");
                else printf("%s", (Mat_signe(p.vector[i].alg.ztab[1])|| Mat_signe(p.vector[i].alg.ztab[0]))? " " : " +");
                complexe_print(p.vector[i]);
                if (!(complexe_is_real(p.vector[i]) || complexe_is_imaginary(p.vector[i]))) printf(")");
                if (i == 1) {
                    printf("%s", variable);
                } else {
                    printf("%s^%zu", variable, i);
                }
            }
        }
    }
    printf("\n");
}

#ifdef DEBUG
#include "vectors.h"

int main(int argc, char const *argv[]) {
    polynome_t p = polynome_new(1, real_new(1), real_new(1));
    printf("P   = "); polynome_print(p, "X");
    polynome_t pa = polynome_pow(p, 10);
    printf("Pa  = "); polynome_print(pa, "X");
    polynome_t pa_ = polynome_diff_ordre_n(pa, 1);
    printf("Pa\' = "); polynome_print(pa_, "X");
    polynome_t pa__ = polynome_diff_ordre_n(pa, 10);
    printf("Pa\" = "); polynome_print(pa__, "X");
    polynome_delete(p);
    polynome_delete(pa);
    polynome_delete(pa_);
    polynome_delete(pa__);
    return 0;
}
#endif
