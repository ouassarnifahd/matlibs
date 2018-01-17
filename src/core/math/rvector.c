#include "std.h"
#include "core/math/rvector.h"

rvector_t rvect_init(size_t size) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rvector_t vect = Mat_alloc(SIZE_RVECT);
    alloc_check(vect);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'vect': %zu Octets", SIZE_RVECT);
    #endif
    vect->size = size;
    vect->vector = Mat_alloc(SIZE_RVector(size));
    alloc_check(vect->vector);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'vect->vector': %zu Octets", (size_t)SIZE_RVector(size));
    #endif
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return vect;
}

rvector_t rvect_zero(size_t size) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rvector_t zero = rvect_init(size);
    if (zero) {
        for (size_t i = 0; i < zero->size; i++)
            real_zero(&zero->vector[i]);
    } else {
        error("NULL pointer methode!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return zero;
}

rvector_t rvect_one(size_t size) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rvector_t one = rvect_init(size);
    if (one) {
        for (size_t i = 0; i < one->size; i++)
            real_one(&one->vector[i]);
    } else {
        error("NULL pointer methode!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return one;
}

rvector_t rvect_new(size_t size, ...) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rvector_t vect = rvect_init(size);
    sreal_t arg;
    va_list args;
    va_start(args, size);
    for (size_t i = 0; i < size; i++) {
        arg = va_arg(args, sreal_t);
        vect->vector[i] = arg;
    }
    va_end(args);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return vect;
}

void rvect_delete(rvector_t vect) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (vect) {
        if (vect->vector) {
            Mat_free(vect->vector);
            #ifdef DEBUG_FREE
            debug("Memory freed (vect->vector)");
            #endif
            vect->vector = NULL;
        }
        Mat_free(vect);
        #ifdef DEBUG_FREE
        debug("Memory freed (vect)");
        #endif
        vect = NULL;
    } else {
        warning("NULL pointer exeption!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

bool rvect_is_null(const rvector_t vect) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (vect) {
        size_t i = 0;
        while(i < vect->size && real_is_null(&vect->vector[i])) i++;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        if (i == vect->size)
            return true;
        else
            return false;
    } else {
        error("NULL pointer is already null!");
    }
}

void rvect_inv(rvector_t vect) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (vect) {
        for (size_t i = 0; i < vect->size; i++)
            real_inv(&vect->vector[i]);
    } else {
        error("NULL pointer can't be inversed!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

rvector_t rvect_add(const rvector_t vect1, const rvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rvector_t res = NULL;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else if (vect1->size != vect2->size) {
        warning("Vectors dimentions must agree!");
    } else {
        size_t max_vects = Mat_max(vect1->size, vect2->size);
        res = rvect_init(max_vects);
        for (size_t i = 0; i < res->size; i++) {
            if (vect1->size < i) {
                res->vector[i] = vect2->vector[i];
            } if (vect2->size < i) {
                res->vector[i] = vect1->vector[i];
            } else {
                res->vector[i] = vect1->vector[i] + vect2->vector[i];
                // real_add(&vect1->vector[i], &vect2->vector[i], &res->vector[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

rvector_t rvect_sub(const rvector_t vect1, const rvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rvector_t res = NULL;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else if (vect1->size != vect2->size) {
        warning("Vectors dimentions must agree!");
    } else {
        size_t max_vects = Mat_max(vect1->size, vect2->size);
        res = rvect_init(max_vects);
        for (size_t i = 0; i < max_vects; i++) {
            if (vect1->size < i) {
                res->vector[i] = vect2->vector[i];
                real_inv(&res->vector[i]);
            } if (vect2->size < i) {
                res->vector[i] = vect1->vector[i];
            } else {
                res->vector[i] = vect1->vector[i] - vect2->vector[i];
                // real_sub(&vect1->vector[i], &vect2->vector[i], &res->vector[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

rvector_t rvect_mult(const rvector_t vect1, const rvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rvector_t res = NULL;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else if (vect1->size != vect2->size) {
        warning("Vectors dimentions must agree!");
    } else {
        size_t max_vects = Mat_max(vect1->size, vect2->size);
        res = rvect_init(max_vects);
        for (size_t i = 0; i < res->size; i++) {
            if (vect1->size < i || vect2->size < i) {
                real_zero(&res->vector[i]);
            } else {
                res->vector[i] = vect1->vector[i] * vect2->vector[i];
                // real_mult(&vect1->vector[i], &vect2->vector[i], &res->vector[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

sreal_t rvect_dot(const rvector_t vect1, const rvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    sreal_t res;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else {
        // sreal_t dot_mult = 0.0;
        size_t min_vects = Mat_min(vect1->size, vect2->size);
        res = 0.0;
        for (size_t i = 0; i < min_vects; i++) {
            res += vect1->vector[i] * vect2->vector[i];
            // real_mult(&vect1->vector[i], &vect2->vector[i], &dot_mult);
            // real_add(&res, &dot_mult, &res);
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

rvector_t rvect_scale(const rvector_t vect, sreal_t scalar) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rvector_t res = NULL;
    if (!vect || !scalar) {
        error("NULL pointer operation!");
    } else {
        res = rvect_init(vect->size);
        for (size_t i = 0; i < res->size; i++) {
            res->vector[i] = vect->vector[i] * scalar;
            // real_mult(&vect1->vector[i], &vect2->vector[i], &res->vector[i]);
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

// /!\ O(n2)
rvector_t rvect_conv(const rvector_t vect1, const rvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rvector_t res = NULL;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else if (vect1->size != vect2->size) {
        warning("Vectors dimentions must agree!");
    } else {
        // sreal_t tmp = 0.0;
        res = rvect_init(vect1->size + vect2->size - 1);
        for (size_t i = 0; i < res->size; i++) {
            for (size_t k = 0; k <= i; k++) {
                #ifdef DEBUGED
                    Mat_printf("c%zu = ", i);
                    real_print(&res->vector[i]);
                    Mat_printf(" + ");
                    real_print(&vect1->vector[k]);
                    Mat_printf(" * ");
                    real_print(&vect2->vector[i - k]);
                    Mat_printf(" (k=%zu) (i-k=%zu)\n", k, i - k);
                #endif
                if (k < vect1->size && (i-k) < vect2->size) {
                    res->vector[i] += vect1->vector[k] * vect2->vector[i - k];
                    // real_mult(&vect1->vector[k], &vect2->vector[i - k], &tmp);
                    // real_add(&res->vector[i], &tmp, &res->vector[i]);
                }
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

void rvect_print_colonne(const rvector_t vect) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!vect) {
        error("NULL pointer print!");
    } else {
        Mat_printf("\n");
        for (size_t i = 0; i < vect->size; ++i) {
            Mat_printf("\t[ ");
            real_print(&vect->vector[i]);
            Mat_printf(" ]\n");
        }
        Mat_printf("\n");
    }
    #ifdef DEBUG_PRINT
    debug("leaving print function!\n");
    #endif
}

void rvect_print_ligne(const rvector_t vect) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!vect) {
        error("NULL pointer print!");
    } else {
        Mat_printf("  [ ");
        for (size_t i = 0; i < vect->size; ++i) {
            real_print(&vect->vector[i]);
            if (i != vect->size - 1) {
                Mat_printf("  ");
            }
        }
        Mat_printf(" ]\n");
    }
    #ifdef DEBUG_PRINT
    debug("leaving print function!\n");
    #endif
}

#ifdef DEBUGED
int main(int argc, char const *argv[]) {
    init_log();
    #if defined (__x86_64__)
        debug("64-bit architecture!\n");
    #elif defined (__i386__)
        warning("32-bit architecture!\n");
    #else
        error("Incompatible architecture!");
    #endif

    rvector_t A1 = rvect_new(2, 1.0, 1.0);
    rvector_t A2 = rvect_new(2, 1.0, 1.0);

    Mat_printf("A1  ="); rvect_print_ligne(A1);
    Mat_printf("A2  ="); rvect_print_ligne(A2);
    Mat_printf("\n");

    rvector_t A12 = rvect_conv(A1,A2);

    Mat_printf("A12 ="); rvect_print_ligne(A12);

    rvect_delete(A1);
    rvect_delete(A2);
    rvect_delete(A12);

    debug("FY!");
    return 0;
}
#endif
