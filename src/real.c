#include "real.h"

double Mat_pow(double x, size_t n) {
    double power = 1;
    for (size_t i = 0; i < n; i++) {
        power *= x;
    }
    return power;
}

double Mat_root(double x, size_t n) {
    // idea!
    for (size_t i = 0; i < n; i++) {
        for (size_t i = 0; Mat_pow(x, i) < n; i++);
    }
    return 0.0;
}

const struct math real_entity = {
    SIZE_REAL,
    (math_new_t)real_new,
    real_delete, real_zero, real_one, real_inv,
    real_is_null, real_is_positive, real_is_negative,
    real_add, real_sub, real_mult, real_div,
    real_print
};

void* real_new(double x) {
    real_t new = malloc(sizeof(double));
    *new = x;
    return (void*)new;
}

void real_delete(void* x) {
    if (x) free(x);
}

void real_zero(void* x) {
    real_t tmp = (real_t)x;
    *tmp = 0;
}

void real_one(void* x) {
    real_t tmp = (real_t)x;
    *tmp = 1;
}

void real_inv(void* x) {
    real_t tmp = (real_t)x;
    *tmp = -*tmp;
}

bool real_is_null(const void* x) {
    real_t tmp = (const real_t)x;
    return !*tmp;
}

bool real_is_positive(const void* x) {
    real_t tmp = (const real_t)x;
    return *tmp >= 0;
}

bool real_is_negative(const void* x) {
    real_t tmp = (const real_t)x;
    return *tmp < 0;
}

void real_add(const void* x1, const void* x2, void* res) {
    double a = *(const real_t)x1, b = *(const real_t)x2;
    *(real_t)res = a + b;
}

void real_sub(const void* x1, const void* x2, void* res) {
    double a = *(const real_t)x1, b = *(const real_t)x2;
    *(real_t)res = a - b;
}

void real_mult(const void* x1, const void* x2, void* res) {
    double a = *(const real_t)x1, b = *(const real_t)x2;
    *(real_t)res = a * b;
}

void real_div(const void* x1, const void* x2, void* res) {
    if (real_is_null((const real_t)x2)) {
        real_delete((real_t)res);
        res = NULL;
    } else {
        double a = *(const real_t)x1, b = *(const real_t)x2;
        *(real_t)res = a / b;
    }
}

void real_print(const void* x) {
    real_t tmp = (const real_t)x;
    printf("%.2lf", *tmp);
}

#ifdef DEBUG
int main(int argc, char const *argv[]) {
    real_t x1 = real_new(1.2), x2 = real_new(2.8);
    real_t add = real_new(0), sub = real_new(0), mult = real_new(0), division = real_new(0);
    real_add((const void*)x1, (const void*)x2, (void*)add);
    real_sub((const void*)x1, (const void*)x2, (void*)sub);
    real_mult((const void*)x1, (const void*)x2, (void*)mult);
    real_div((const void*)x1, (const void*)x2, (void*)division);
    real_print(x1); printf(" + "); real_print(x2); printf(" = "); real_print(add); printf("\n");
    real_print(x1); printf(" - "); real_print(x2); printf(" = "); real_print(sub); printf("\n");
    real_print(x1); printf(" * "); real_print(x2); printf(" = "); real_print(mult); printf("\n");
    real_print(x1); printf(" / "); real_print(x2); printf(" = "); real_print(division); printf("\n");
    real_delete(add);
    real_delete(sub);
    real_delete(mult);
    real_delete(division);
    real_delete(x1);
    real_delete(x2);
    return 0;
}
#endif
