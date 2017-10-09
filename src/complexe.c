#include "complexe.h"

const struct math complexe_entity = {
    SIZE_COMPLEXE,
    (math_new_t)complexe_new,
    complexe_delete, complexe_zero, complexe_one, complexe_inv,
    complexe_is_null, NULL, NULL,
    complexe_add, complexe_sub, complexe_mult, complexe_div,
    complexe_print
};

void* complexe_new(double real, double imaginary) {
    complexe_t new = malloc(sizeof(complexe_t));
    new->alg.ztab[0] = real_new(real);
    new->alg.ztab[1] = real_new(imaginary);
    return (void*)new;
}

void complexe_delete(void* z) {
    if (z) {
        real_t *del = (real_t *)z;
        real_delete(del[0]);
        real_delete(del[1]);
    }
}

bool complexe_is_null(const void* x) {
    complexe_t z = (const complexe_t)x;
    return !*z->alg.ztab[0]&& !*z->alg.ztab[1];
}

bool complexe_is_real(const void* x) {
    complexe_t z = (const complexe_t)x;
    return *z->alg.ztab[0] && !*z->alg.ztab[1];
}

bool complexe_is_imaginary(const void* x) {
    complexe_t z = (const complexe_t)x;
    return !*z->alg.ztab[0] && *z->alg.ztab[1];
}

void complexe_zero(void* z) {
    complexe_t z_tmp = z;
    *z_tmp->alg.ztab[0] = 0;
    *z_tmp->alg.ztab[1] = 0;
}

void complexe_one(void* z) {
    complexe_t z_tmp = z;
    *z_tmp->alg.ztab[0] = 1;
    *z_tmp->alg.ztab[1] = 0;
}

void complexe_i(void* z) {
    complexe_t z_tmp = z;
    *z_tmp->alg.ztab[0] = 0;
    *z_tmp->alg.ztab[1] = 1;
}

void complexe_inv(void* z) {
    complexe_t z_tmp = (const complexe_t)z;
    *z_tmp->alg.ztab[0] = -*z_tmp->alg.ztab[0];
    *z_tmp->alg.ztab[1] = -*z_tmp->alg.ztab[1];
}

void complexe_add(const void* z1, const void* z2, void* res) {
    union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
    real_add((const void*)a.alg.ztab[0], (const void*)b.alg.ztab[0], (void*)tmp_res.alg.ztab[0]);
    real_add((const void*)a.alg.ztab[1], (const void*)b.alg.ztab[1], (void*)tmp_res.alg.ztab[1]);
}

void complexe_sub(const void* z1, const void* z2, void* res) {
    union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
    real_sub((const void*)a.alg.ztab[0], (const void*)b.alg.ztab[0], (void*)tmp_res.alg.ztab[0]);
    real_sub((const void*)a.alg.ztab[1], (const void*)b.alg.ztab[1], (void*)tmp_res.alg.ztab[1]);
}

void complexe_mult(const void* z1, const void* z2, void* res) { // z1 * z2 = (a1 * a2 - b1 * b2) + i * (a1 * b2 + a2 * b1)
    union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
    complexe_t tmp = complexe_new(0, 0);
    // a1 * a2 - b1 * b2
    real_mult((const void*)a.alg.ztab[0], (const void*)b.alg.ztab[0], (void*)tmp->alg.ztab[0]);
    real_mult((const void*)a.alg.ztab[1], (const void*)b.alg.ztab[1], (void*)tmp->alg.ztab[1]);
    real_sub((const void*)tmp->alg.ztab[0], (const void*)tmp->alg.ztab[1], (void*)tmp_res.alg.ztab[0]);
    // a1 * b2 + a2 * b1
    real_mult((const void*)a.alg.ztab[0], (const void*)b.alg.ztab[1], (void*)tmp->alg.ztab[0]);
    real_mult((const void*)a.alg.ztab[1], (const void*)b.alg.ztab[0], (void*)tmp->alg.ztab[1]);
    real_add((const void*)tmp->alg.ztab[0], (const void*)tmp->alg.ztab[1], (void*)tmp_res.alg.ztab[1]);
    complexe_delete(tmp);
}

void complexe_div(const void* z1, const void* z2, void* res) { // z1 / z2 = ((a1 * a2 + b1 * b2) + i * (b1 * a2 - a1 * b2))/(a2 * a2 + b2 * b2)
    if (complexe_is_null((const complexe_t)z2)) {
        complexe_delete((complexe_t)res);
        res = NULL;
    } else {
        union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
        complexe_t tmp1 = complexe_new(0, 0), tmp2 = complexe_new(0, 0);
        real_t den = real_new(0);
        real_mult((const void*)a.alg.ztab[0], (const void*)b.alg.ztab[0], (void*)tmp1->alg.ztab[0]);
        real_mult((const void*)a.alg.ztab[1], (const void*)b.alg.ztab[1], (void*)tmp1->alg.ztab[1]);
        real_add((const void*)tmp1->alg.ztab[0], (const void*)tmp1->alg.ztab[1], (void*)tmp2->alg.ztab[0]);

        real_mult((const void*)a.alg.ztab[1], (const void*)b.alg.ztab[0], (void*)tmp1->alg.ztab[0]);
        real_mult((const void*)a.alg.ztab[0], (const void*)b.alg.ztab[1], (void*)tmp1->alg.ztab[1]);
        real_sub((const void*)tmp1->alg.ztab[0], (const void*)tmp1->alg.ztab[1], (void*)tmp2->alg.ztab[1]);

        real_mult((const void*)b.alg.ztab[0], (const void*)b.alg.ztab[0], (void*)tmp1->alg.ztab[0]);
        real_mult((const void*)b.alg.ztab[1], (const void*)b.alg.ztab[1], (void*)tmp1->alg.ztab[1]);
        real_add((const void*)tmp1->alg.ztab[0], (const void*)tmp1->alg.ztab[1], (void*)den);

        real_div((const void*)tmp2->alg.ztab[0], (const void*)den, (void*)tmp_res.alg.ztab[0]);
        real_div((const void*)tmp2->alg.ztab[1], (const void*)den, (void*)tmp_res.alg.ztab[1]);

        complexe_delete(tmp1);
        complexe_delete(tmp2);
        real_delete(den);
    }
}

void complexe_pow(const void* z, size_t pow, void* res) {
    complexe_t tmp_res = complexe_new(1, 0), a = (const complexe_t)z;
    for (size_t i = 0; i < pow; i++)
        complexe_mult(a, tmp_res, tmp_res);
    complexe_delete(tmp_res);
}

void complexe_print(const void* x) {
    complexe_t z = (const complexe_t)x;
    if (complexe_is_null(z)) {
        printf("0");
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

#ifdef DEBUG
int main(int argc, char const *argv[]) {
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
