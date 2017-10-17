#include "complexe.h"

void* complexe_new(double real, double imaginary) {
    #ifdef DEBUG
    debug("Entering function!");
    #endif
    complexe_t new = malloc(sizeof(union complexe));
    #ifdef DEBUG
    if (new) debug("Memory allocation 'real_t': %zu Octets", SIZE_REAL);
    #endif
    alloc_check(new);
    new->alg.ztab[0] = real_new(real);
    new->alg.ztab[1] = real_new(imaginary);
    #ifdef DEBUG
    debug("leaving function!\n");
    #endif
    return (void*)new;
}

void complexe_delete(void* z) {
    if (z) {
        complexe_t del = (complexe_t)z;
        real_delete(del->alg.ztab[0]);
        real_delete(del->alg.ztab[1]);
        free(del);
        del = NULL;
    }
}

bool complexe_is_null(const void* x) {
    if (x) {
        complexe_t z = (const complexe_t)x;
        return !*z->alg.ztab[0]&& !*z->alg.ztab[1];
    } else {
        error("NULL pointer is already null!");
    }
}

bool complexe_is_real(const void* x) {
    if (x) {
        complexe_t z = (const complexe_t)x;
        return *z->alg.ztab[0] && !*z->alg.ztab[1];
    } else {
        error("NULL pointer can't be real!");
    }
}

bool complexe_is_imaginary(const void* x) {
    if (x) {
        complexe_t z = (const complexe_t)x;
        return !*z->alg.ztab[0] && *z->alg.ztab[1];
    } else {
        error("NULL pointer can't be imaginary!");
    }
}

void complexe_zero(void* z) {
    if (!z) {
        z = malloc(SIZE_COMPLEXE);
        alloc_check(z);
    }
    complexe_t z_tmp = z;
    *z_tmp->alg.ztab[0] = 0;
    *z_tmp->alg.ztab[1] = 0;
}

void complexe_one(void* z) {
    if (!z) {
        z = malloc(SIZE_COMPLEXE);
        alloc_check(z);
    }
    complexe_t z_tmp = z;
    *z_tmp->alg.ztab[0] = 1;
    *z_tmp->alg.ztab[1] = 0;
}

void complexe_i(void* z) {
    if (!z) {
        z = malloc(SIZE_COMPLEXE);
        alloc_check(z);
    }
    complexe_t z_tmp = z;
    *z_tmp->alg.ztab[0] = 0;
    *z_tmp->alg.ztab[1] = 1;
}

void complexe_inv(void* z) {
    if (z) {
        complexe_t z_tmp = z;
        *z_tmp->alg.ztab[0] = -*z_tmp->alg.ztab[0];
        *z_tmp->alg.ztab[1] = -*z_tmp->alg.ztab[1];
    } else {
        error("NULL pointer can't be inversed!");
    }
}

void complexe_add(const void* z1, const void* z2, void* res) {
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else {
        union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
        if (!res) {
            res = malloc(SIZE_COMPLEXE);
            alloc_check(res);
        }
        real_add(a.alg.ztab[0], b.alg.ztab[0], tmp_res.alg.ztab[0]);
        real_add(a.alg.ztab[1], b.alg.ztab[1], tmp_res.alg.ztab[1]);
    }
}

void complexe_sub(const void* z1, const void* z2, void* res) {
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else {
        union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
        if (!res) {
            res = malloc(SIZE_COMPLEXE);
            alloc_check(res);
        }
        real_sub(a.alg.ztab[0], b.alg.ztab[0], tmp_res.alg.ztab[0]);
        real_sub(a.alg.ztab[1], b.alg.ztab[1], tmp_res.alg.ztab[1]);
    }
}

void complexe_mult(const void* z1, const void* z2, void* res) { // z1 * z2 = (a1 * a2 - b1 * b2) + i * (a1 * b2 + a2 * b1)
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else {
        union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
        if (!res) {
            res = malloc(SIZE_COMPLEXE);
            alloc_check(res);
        }
        complexe_t tmp = complexe_new(0, 0);
        // a1 * a2 - b1 * b2
        real_mult(a.alg.ztab[0], b.alg.ztab[0], tmp->alg.ztab[0]);
        real_mult(a.alg.ztab[1], b.alg.ztab[1], tmp->alg.ztab[1]);
        real_sub(tmp->alg.ztab[0], tmp->alg.ztab[1], tmp_res.alg.ztab[0]);
        // a1 * b2 + a2 * b1
        real_mult(a.alg.ztab[0], b.alg.ztab[1], tmp->alg.ztab[0]);
        real_mult(a.alg.ztab[1], b.alg.ztab[0], tmp->alg.ztab[1]);
        real_add(tmp->alg.ztab[0], tmp->alg.ztab[1], tmp_res.alg.ztab[1]);
        complexe_delete(tmp);
    }
}

void complexe_div(const void* z1, const void* z2, void* res) { // z1 / z2 = ((a1 * a2 + b1 * b2) + i * (b1 * a2 - a1 * b2))/(a2 * a2 + b2 * b2)
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else if (complexe_is_null(z2)) {
        if (res) {
            complexe_delete(res);
        }
        error("Division by zero!");
    } else {
        union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
        if (!res) {
            res = malloc(SIZE_COMPLEXE);
            alloc_check(res);
        }
        complexe_t tmp1 = complexe_new(0, 0), tmp2 = complexe_new(0, 0);
        real_t den = real_new(0);
        real_mult(a.alg.ztab[0], b.alg.ztab[0], tmp1->alg.ztab[0]);
        real_mult(a.alg.ztab[1], b.alg.ztab[1], tmp1->alg.ztab[1]);
        real_add(tmp1->alg.ztab[0], tmp1->alg.ztab[1], tmp2->alg.ztab[0]);

        real_mult(a.alg.ztab[1], b.alg.ztab[0], tmp1->alg.ztab[0]);
        real_mult(a.alg.ztab[0], b.alg.ztab[1], tmp1->alg.ztab[1]);
        real_sub(tmp1->alg.ztab[0], tmp1->alg.ztab[1], tmp2->alg.ztab[1]);

        real_mult(b.alg.ztab[0], b.alg.ztab[0], tmp1->alg.ztab[0]);
        real_mult(b.alg.ztab[1], b.alg.ztab[1], tmp1->alg.ztab[1]);
        real_add(tmp1->alg.ztab[0], tmp1->alg.ztab[1], den);

        real_div(tmp2->alg.ztab[0], den, tmp_res.alg.ztab[0]);
        real_div(tmp2->alg.ztab[1], den, tmp_res.alg.ztab[1]);

        complexe_delete(tmp1);
        complexe_delete(tmp2);
        real_delete(den);
    }
}

void complexe_pow(const void* z, size_t pow, void* res) {
    complexe_t a = (const complexe_t)z;
    complexe_one(res);
    for (size_t i = 0; i < pow; i++)
        complexe_mult(a, res, res);
}

void complexe_print(const void* x) {
    if (!x) {
        error("NULL pointer print!");
    } else {
        complexe_t z = (const complexe_t)x;
        if (complexe_is_null(z)) {
            printf("0.00 ");
        } else {
            if (complexe_is_real(z)) {
                real_print(z->alg.zReIm.real);
            } else if (complexe_is_imaginary(z)) {
                real_print(z->alg.zReIm.imaginary);
                printf("i");
            } else {
                real_print(z->alg.zReIm.real);
                if (*z->alg.zReIm.imaginary > 0.0) printf(" +");
                real_print(z->alg.zReIm.imaginary);
                printf("i");
            }
        }
    }
}

#ifdef DEBUGED
int main(int argc, char const *argv[]) {
    arch_test();
    complexe_t x1 = complexe_new(1.2, 2.1), x2 = complexe_new(2.8, 3.2);
    complexe_t add = complexe_new(0, 0), sub = complexe_new(0, 0), mult = complexe_new(0, 0), division = complexe_new(0, 0);
    complexe_add((const void*)x1, (const void*)x2, (void*)add);
    complexe_sub((const void*)x1, (const void*)x2, (void*)sub);
    complexe_mult((const void*)x1, (const void*)x2, (void*)mult);
    complexe_div((const void*)x1, (const void*)x2, (void*)division);
    complexe_print(x1); printf(" + "); complexe_print(x2); printf(" = "); complexe_print(add); printf("\n");
    complexe_print(x1); printf(" - "); complexe_print(x2); printf(" = "); complexe_print(sub); printf("\n");
    complexe_print(x1); printf(" * "); complexe_print(x2); printf(" = "); complexe_print(mult); printf("\n");
    complexe_print(x1); printf(" / "); complexe_print(x2); printf(" = "); complexe_print(division); printf("\n");
    complexe_delete(add);
    complexe_delete(sub);
    complexe_delete(mult);
    complexe_delete(division);
    complexe_delete(x1);
    complexe_delete(x2);
    return 0;
}
#endif
