#include "std.h"
#include "core/math/real.h"
#include "core/math/complexe.h"

scomplexe_t complexe_new(double real, double imaginary) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    scomplexe_t new;
    new.alg.zReIm.real = real;
    new.alg.zReIm.imaginary = imaginary;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return new;
}

bool complexe_is_null(const complexe_t z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (z) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return !z->alg.ztab[0]&& !z->alg.ztab[1];
    } else {
        error("NULL pointer is already null!");
    }
}

bool complexe_is_real(const complexe_t z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (z) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return z->alg.ztab[0] && !z->alg.ztab[1];
    } else {
        error("NULL pointer can't be real!");
    }
}

bool complexe_is_imaginary(const complexe_t z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (z) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return !z->alg.ztab[0] && z->alg.ztab[1];
    } else {
        error("NULL pointer can't be imaginary!");
    }
}

void complexe_zero(complexe_t z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (z) {
        z->alg.ztab[0] = 0;
        z->alg.ztab[1] = 0;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_one(complexe_t z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (z) {
        z->alg.ztab[0] = 1;
        z->alg.ztab[1] = 0;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_i(complexe_t z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (z) {
        z->alg.ztab[0] = 0;
        z->alg.ztab[1] = 1;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_inv(complexe_t z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (z) {
        z->alg.ztab[0] = -z->alg.ztab[0];
        z->alg.ztab[1] = -z->alg.ztab[1];
    } else {
        error("NULL pointer can't be inversed!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_swap(const complexe_t z1, const complexe_t z2) {
    scomplexe_t tmp = *z1;
    *z1 = *z2;
    *z2 = tmp;
}

void complexe_add(const complexe_t z1, const complexe_t z2, complexe_t res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else {
        if (!res) {
            warning("'res' is NULL");
        }
        res->alg.ztab[0] = z1->alg.ztab[0] + z2->alg.ztab[0];
        res->alg.ztab[1] = z1->alg.ztab[1] + z2->alg.ztab[1];
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_sub(const complexe_t z1, const complexe_t z2, complexe_t res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else {
        if (!res) {
            warning("'res' is NULL");
        }
        res->alg.ztab[0] = z1->alg.ztab[0] - z2->alg.ztab[0];
        res->alg.ztab[1] = z1->alg.ztab[1] - z2->alg.ztab[1];
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_mult(const complexe_t z1, const complexe_t z2, complexe_t res) { // z1 * z2 = (a1 * a2 - b1 * b2) + i * (a1 * b2 + a2 * b1)
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else {
        if (!res) {
            warning("'res' is NULL");
        }
        // a1 * a2 - b1 * b2
        res->alg.ztab[0] = z1->alg.ztab[0] * z2->alg.ztab[0] - z1->alg.ztab[1] * z2->alg.ztab[1];
        // a1 * b2 + a2 * b1
        res->alg.ztab[1] = z1->alg.ztab[0] * z2->alg.ztab[1] + z1->alg.ztab[1] * z2->alg.ztab[0];
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_div(const complexe_t z1, const complexe_t z2, complexe_t res) { // z1 / z2 = ((a1 * a2 + b1 * b2) + i * (b1 * a2 - a1 * b2))/(a2 * a2 + b2 * b2)
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else if (complexe_is_null(z2)) {
        error("Division by zero!");
    } else {
        if (!res) {
            warning("'res' is NULL");
        }
        sreal_t den = z2->alg.ztab[0] * z2->alg.ztab[0] + z2->alg.ztab[1] * z2->alg.ztab[1];
        res->alg.ztab[0] = (z1->alg.ztab[0] * z2->alg.ztab[0] + z1->alg.ztab[1] * z2->alg.ztab[1]) / den;
        res->alg.ztab[1] = (z1->alg.ztab[1] * z2->alg.ztab[0] - z1->alg.ztab[0] * z2->alg.ztab[1]) / den;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_pow(const complexe_t z, size_t pow, complexe_t res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    complexe_one(res);
    for (size_t i = 0; i < pow; i++)
        complexe_mult(z, res, res);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_print(const complexe_t z) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!z) {
        error("NULL pointer print!");
    } else {
        if (z->alg.zReIm.imaginary >= 0.0) Mat_printf(" ");
        real_print(&z->alg.zReIm.real);
        if (z->alg.zReIm.imaginary >= 0.0) {
            Mat_printf(" +");
        } else {
            Mat_printf(" -");
        }
        sreal_t abs_im = Mat_abs(z->alg.zReIm.imaginary);
        real_print(&abs_im);
        Mat_printf("i");
    }
    #ifdef DEBUG_PRINT
    debug("leaving print function!\n");
    #endif
}
