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
