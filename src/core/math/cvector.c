#include "std.h"
#include "core/math/cvector.h"

cvector_t cvect_init(size_t size) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cvector_t vect = Mat_alloc(SIZE_CVECT);
    alloc_check(vect);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'vect': %zu Octets", SIZE_CVECT);
    #endif
    vect->size = size;
    vect->vector = Mat_alloc(SIZE_CVector(size));
    alloc_check(vect->vector);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'vect->vector': %zu Octets", (size_t)SIZE_CVector(size));
    #endif
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return vect;
}

cvector_t cvect_zero(size_t size) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cvector_t zero = cvect_init(size);
    for (size_t i = 0; i < zero->size; i++)
        complexe_one(&zero->vector[i]);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return zero;
}

cvector_t cvect_one(size_t size) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cvector_t one = cvect_init(size);
    for (size_t i = 0; i < one->size; i++)
        complexe_one(&one->vector[i]);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return one;
}

cvector_t cvect_new(size_t size, ...) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cvector_t vect = cvect_init(size);
    scomplexe_t arg;
    va_list args;
    va_start(args, size);
    for (size_t i = 0; i < size; i++) {
        arg = va_arg(args, scomplexe_t);
        vect->vector[i] = arg;
    }
    va_end(args);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return vect;
}

void cvect_delete(cvector_t vect) {
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

bool cvect_is_null(const cvector_t vect) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (vect) {
        size_t i = 0;
        while(i < vect->size && complexe_is_null(&vect->vector[i])) i++;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        if (i == vect->size)
            return 1;
        else
            return 0;
    } else {
        error("NULL pointer is already null!");
    }
}

bool cvect_is_complexe(const cvector_t vect) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (vect) {
        return vect->size == 1;
    } else {
        error("NULL pointer is not complexe!");
    }
}

cvector_t cvect_add(const cvector_t vect1, const cvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cvector_t res = NULL;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else if (vect1->size != vect2->size) {
        warning("Vectors dimentions must agree!");
    } else {
        size_t max_vects = Mat_max(vect1->size, vect2->size);
        res = cvect_init(max_vects);
        for (size_t i = 0; i < res->size; i++) {
            if (vect1->size < i) {
                res->vector[i] = vect2->vector[i];
            } if (vect2->size < i) {
                res->vector[i] = vect1->vector[i];
            } else {
                complexe_add(&vect1->vector[i], &vect2->vector[i], &res->vector[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

cvector_t cvect_sub(const cvector_t vect1, const cvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cvector_t res = NULL;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else if (vect1->size != vect2->size) {
        warning("Vectors dimentions must agree!");
    } else {
        size_t max_vects = Mat_max(vect1->size, vect2->size);
        res = cvect_init(max_vects);
        for (size_t i = 0; i < max_vects; i++) {
            if (vect1->size < i) {
                res->vector[i] = vect2->vector[i];
                complexe_inv(&res->vector[i]);
            } if (vect2->size < i) {
                res->vector[i] = vect1->vector[i];
            } else {
                complexe_sub(&vect1->vector[i], &vect2->vector[i], &res->vector[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

cvector_t cvect_mult(const cvector_t vect1, const cvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cvector_t res = NULL;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else if (vect1->size != vect2->size) {
        warning("Vectors dimentions must agree!");
    } else {
        size_t max_vects = Mat_max(vect1->size, vect2->size);
        res = cvect_init(max_vects);
        for (size_t i = 0; i < res->size; i++) {
            if (vect1->size < i || vect2->size < i) {
                complexe_zero(&res->vector[i]);
            } else {
                complexe_mult(&vect1->vector[i], &vect2->vector[i], &res->vector[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

scomplexe_t cvect_dot(const cvector_t vect1, const cvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    scomplexe_t res;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else {
        scomplexe_t dot_mult = complexe_new(0.0, 0.0);
        size_t min_vects = Mat_min(vect1->size, vect2->size);
        res = complexe_new(0.0, 0.0);
        for (size_t i = 0; i < min_vects; i++) {
            complexe_mult(&vect1->vector[i], &vect2->vector[i], &dot_mult);
            complexe_add(&res, &dot_mult, &res);
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

cvector_t cvect_conv(const cvector_t vect1, const cvector_t vect2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cvector_t res = NULL;
    if (!vect1 || !vect2) {
        error("NULL pointer operation!");
    } else if (vect1->size != vect2->size) {
        warning("Vectors dimentions must agree!");
    } else {
        scomplexe_t tmp = complexe_new(0.0, 0.0);
        res = cvect_init(vect1->size + vect2->size);
        for (size_t i = 0; i < res->size - 1; i++) {
            for (size_t k = 0; k <= i; k++) {
                #ifdef DEBUGED
                    Mat_printf("c%zu = ", i);
                    complexe_print(&res->vector[i]);
                    Mat_printf(" + ");
                    complexe_print(&vect1->vector[k]);
                    Mat_printf(" * ");
                    complexe_print(&vect2->vector[i - k]);
                    Mat_printf(" (k=%zu) (i-k=%zu)\n", k, i - k);
                #endif
                if (k < vect1->size && (i-k) < vect2->size) {
                    complexe_mult(&vect1->vector[k], &vect2->vector[i - k], &tmp);
                    complexe_add(&res->vector[i], &tmp, &res->vector[i]);
                }
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

void cvect_print_colonne(const cvector_t vect) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!vect) {
        error("NULL pointer print!");
    } else {
        Mat_printf("\n");
        for (size_t i = 0; i < vect->size; ++i) {
            Mat_printf("\t[ ");
            complexe_print(&vect->vector[i]);
            Mat_printf(" ]\n");
        }
        Mat_printf("\n");
    }
    #ifdef DEBUG_PRINT
    debug("leaving print function!\n");
    #endif
}

void cvect_print_ligne(const cvector_t vect) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!vect) {
        error("NULL pointer print!");
    } else {
        Mat_printf("  [ ");
        for (size_t i = 0; i < vect->size; ++i) {
            complexe_print(&vect->vector[i]);
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

    cvector_t A1 = cvect_new(2, complexe_new(100,0),
                                complexe_new(1,16));

    cvector_t A2 = cvect_new(2, complexe_new(10,3),
                                complexe_new(1,2));

    Mat_printf("A1  ="); cvect_print_ligne(A1);
    Mat_printf("A2  ="); cvect_print_ligne(A2);
    Mat_printf("\n");

    cvector_t A12 = cvect_add(A2, A1);
    cvector_t A22 = cvect_sub(A1, A2);

    scomplexe_t dot = cvect_dot(A12, A22);

    Mat_printf("A12 ="); cvect_print_ligne(A12);
    Mat_printf("A22 ="); cvect_print_colonne(A22);
    Mat_printf("A12 • A22 = "); complexe_print(&dot); Mat_printf("\n");

    cvect_delete(A1);
    cvect_delete(A2);
    cvect_delete(A12);
    cvect_delete(A22);

    debug("FY!");
    return 0;
}
#endif
