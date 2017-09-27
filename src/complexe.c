#include "complexe.h"

double Mat_pow(double x, int n) {
    double power = 1;
    for (size_t i = 0; i < n; i++) {
        power *= x;
    }
    return power;
}

complexe_t complexe_new(double real, double imaginary) {
    complexe_t new;
    new.alg.ztab[0] = real;
    new.alg.ztab[1] = imaginary;
    // new.exp.norme = 1;//Mat_sqrt(real * real + imaginary * imaginary);
    // new.exp.argument = 0;//Mat_arctan(imaginary / real);
    return new;
}

bool complexe_is_null(complexe_t z) {
    return !z.alg.ztab[0]&& !z.alg.ztab[1];
}

bool complexe_is_real(complexe_t z) {
    return z.alg.ztab[0] && !z.alg.ztab[1];
}

bool complexe_is_imaginary(complexe_t z) {
    return !z.alg.ztab[0] && z.alg.ztab[1];
}

complexe_t complexe_inv(complexe_t z) {
    return complexe_mult(real_new(-1), z);
}

complexe_t complexe_add(complexe_t z1, complexe_t z2) {
    return complexe_new(z1.alg.ztab[0] + z2.alg.ztab[0], z1.alg.ztab[1] + z2.alg.ztab[1]);
}

complexe_t complexe_mult(complexe_t z1, complexe_t z2) { // z1 * z2 = (a1 * a2 - b1 * b2) + i * (a1 * b2 + a2 * b1)
    return complexe_new(z1.alg.ztab[0] * z2.alg.ztab[0] - z1.alg.ztab[1] * z2.alg.ztab[1],
                        z1.alg.ztab[0] * z2.alg.ztab[1] + z1.alg.ztab[1] * z2.alg.ztab[0]);
}

complexe_t complexe_div(complexe_t z1, complexe_t z2) { // z1 / z2 = ((a1 * a2 + b1 * b2) + i * (b1 * a2 - a1 * b2))/(a2 * a2 + b2 * b2)
    return complexe_new((z1.alg.ztab[0] * z2.alg.ztab[0] + z1.alg.ztab[1] * z2.alg.ztab[1])/(z2.alg.ztab[0] * z2.alg.ztab[0] + z2.alg.ztab[1] * z2.alg.ztab[1]),
                        (z1.alg.ztab[1] * z2.alg.ztab[0] - z1.alg.ztab[0] * z2.alg.ztab[1])/(z2.alg.ztab[0] * z2.alg.ztab[0] + z2.alg.ztab[1] * z2.alg.ztab[1]));
}

complexe_t complexe_pow(complexe_t z, size_t pow) {
    complexe_t power = real_new(1);
    for (size_t i = 0; i < pow; i++)
        power = complexe_mult(power, z);
    return power;
}

void complexe_print(complexe_t z) {
    if (complexe_is_null(z)) {
        printf("0");
    } else {
        if (complexe_is_real(z)) {
            printf("%.2lf", z.alg.zReIm.real);
        } else if (complexe_is_imaginary(z)) {
            printf("%.2lfi", z.alg.zReIm.imaginary);
        } else {
            printf("%.2lf", z.alg.zReIm.real);
            if (z.alg.zReIm.imaginary > 0.0) printf(" +");
            printf("%.2lfi", z.alg.zReIm.imaginary);
        }
    }
}

void complexe_mem_view(complexe_t z) {
    printf("complexe_t ");
    complexe_print(z);
    printf("\n\tz.alg:\n");
    printf("\t  ztab[0]   = %lf\n", z.alg.ztab[0]);
    printf("\t  ztab[1]   = %lf\n", z.alg.ztab[1]);
    printf("\tz.alg.zReIm:\n");
    printf("\t  real      = %lf\n", z.alg.zReIm.real);
    printf("\t  imaginary = %lf\n", z.alg.zReIm.imaginary);
    printf("\tz.exp:\n");
    printf("\t  norme     = %lf\n", z.exp.norme);
    printf("\t  argument  = %lf\n\n", z.exp.argument);
}
