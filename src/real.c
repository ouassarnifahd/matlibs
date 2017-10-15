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

void* real_new(double x) {
    real_t new = malloc(sizeof(double));
    alloc_check(new);
    *new = x;
    return (void*)new;
}

void real_delete(void* x) {
    if (x) {
        free(x);
        x = NULL;
    }
}

void real_zero(void* x) {
    if (!x) {
        x = malloc(SIZE_REAL);
        alloc_check(x);
    }
    *(real_t)x = 0;
}

void real_one(void* x) {
    if (!x)
        x = malloc(SIZE_REAL);
        alloc_check(x);
    }
    *(real_t)x = 1;
}

void real_inv(void* x) {
    if (x) {
        real_t tmp = (real_t)x;
        *tmp = -*tmp;
    } else {
        error("NULL pointer can't be inversed!");
    }
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
        error("Division by zero!");
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
    real_add(x1, x2, add);
    real_sub(x1, x2, sub);
    real_mult(x1, x2, mult);
    real_div(x1, x2, division);
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
