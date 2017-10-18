#include "structures/complexe.h"

void* complexe_new(double real, double imaginary) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    complexe_t new = malloc(SIZE_COMPLEXE);
    #ifdef DEBUG_MALLOC
    if (new) debug("Memory allocation 'complexe_t': %zu Octets", SIZE_COMPLEXE);
    #endif
    alloc_check(new);
    new->alg.ztab[0] = real_new(real);
    new->alg.ztab[1] = real_new(imaginary);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return (void*)new;
}

void complexe_delete(void* z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (z) {
        complexe_t del = (complexe_t)z;
        real_delete(del->alg.ztab[0]);
        real_delete(del->alg.ztab[1]);
        #ifdef DEBUG_FREE
        debug("Memory freed (complexe_t)");
        #endif
        free(del);
        del = NULL;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

bool complexe_is_null(const void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        complexe_t z = (const complexe_t)x;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return !*z->alg.ztab[0]&& !*z->alg.ztab[1];
    } else {
        error("NULL pointer is already null!");
    }
}

bool complexe_is_real(const void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        complexe_t z = (const complexe_t)x;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return *z->alg.ztab[0] && !*z->alg.ztab[1];
    } else {
        error("NULL pointer can't be real!");
    }
}

bool complexe_is_imaginary(const void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        complexe_t z = (const complexe_t)x;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return !*z->alg.ztab[0] && *z->alg.ztab[1];
    } else {
        error("NULL pointer can't be imaginary!");
    }
}

void complexe_zero(void* z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z) {
        z = malloc(SIZE_COMPLEXE);
        #ifdef DEBUG_MALLOC
        if (z) debug("Memory allocation 'complexe_t': %zu Octets", SIZE_COMPLEXE);
        #endif
        alloc_check(z);
    }
    complexe_t z_tmp = z;
    real_zero(z_tmp->alg.ztab[0]);
    real_zero(z_tmp->alg.ztab[1]);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_one(void* z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z) {
        z = malloc(SIZE_COMPLEXE);
        #ifdef DEBUG_MALLOC
        if (z) debug("Memory allocation 'complexe_t': %zu Octets", SIZE_COMPLEXE);
        #endif
        alloc_check(z);
    }
    complexe_t z_tmp = z;
    real_one(z_tmp->alg.ztab[0]);
    real_zero(z_tmp->alg.ztab[1]);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_i(void* z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z) {
        z = malloc(SIZE_COMPLEXE);
        #ifdef DEBUG_MALLOC
        if (z) debug("Memory allocation 'complexe_t': %zu Octets", SIZE_COMPLEXE);
        #endif
        alloc_check(z);
    }
    complexe_t z_tmp = z;
    real_zero(z_tmp->alg.ztab[0]);
    real_one(z_tmp->alg.ztab[1]);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_inv(void* z) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (z) {
        complexe_t z_tmp = z;
        real_inv(z_tmp->alg.ztab[0]);
        real_inv(z_tmp->alg.ztab[1]);
    } else {
        error("NULL pointer can't be inversed!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_add(const void* z1, const void* z2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else {
        union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
        if (!res) {
            res = malloc(SIZE_COMPLEXE);
            #ifdef DEBUG_MALLOC
            if (res) debug("Memory allocation 'complexe_t': %zu Octets", SIZE_COMPLEXE);
            #endif
            alloc_check(res);
        }
        real_add(a.alg.ztab[0], b.alg.ztab[0], tmp_res.alg.ztab[0]);
        real_add(a.alg.ztab[1], b.alg.ztab[1], tmp_res.alg.ztab[1]);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_sub(const void* z1, const void* z2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else {
        union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
        if (!res) {
            res = malloc(SIZE_COMPLEXE);
            #ifdef DEBUG_MALLOC
            if (res) debug("Memory allocation 'complexe_t': %zu Octets", SIZE_COMPLEXE);
            #endif
            alloc_check(res);
        }
        real_sub(a.alg.ztab[0], b.alg.ztab[0], tmp_res.alg.ztab[0]);
        real_sub(a.alg.ztab[1], b.alg.ztab[1], tmp_res.alg.ztab[1]);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_mult(const void* z1, const void* z2, void* res) { // z1 * z2 = (a1 * a2 - b1 * b2) + i * (a1 * b2 + a2 * b1)
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!z1 || !z2) {
        error("NULL pointer operation!");
    } else {
        union complexe a = *(const complexe_t)z1, b = *(const complexe_t)z2, tmp_res = *(complexe_t)res;
        if (!res) {
            res = malloc(SIZE_COMPLEXE);
            #ifdef DEBUG_MALLOC
            if (res) debug("Memory allocation 'complexe_t': %zu Octets", SIZE_COMPLEXE);
            #endif
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
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_div(const void* z1, const void* z2, void* res) { // z1 / z2 = ((a1 * a2 + b1 * b2) + i * (b1 * a2 - a1 * b2))/(a2 * a2 + b2 * b2)
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
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
            #ifdef DEBUG_MALLOC
            if (res) debug("Memory allocation 'complexe_t': %zu Octets", SIZE_COMPLEXE);
            #endif
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
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_pow(const void* z, size_t pow, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    complexe_t a = (const complexe_t)z;
    complexe_one(res);
    for (size_t i = 0; i < pow; i++)
        complexe_mult(a, res, res);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void complexe_print(const void* x) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
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
    #ifdef DEBUG_PRINT
    debug("leaving print function!\n");
    #endif
}

#ifdef DEBUGED
int main(int argc, char const *argv[]) {
    #if defined (__x86_64__)
        debug("64-bit architecture!\n");
    #elif defined (__i386__)
        warning("32-bit architecture!\n");
    #else
        error("Incompatible architecture!");
    #endif
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
    debug("FY!");
    return 0;
}
#endif
