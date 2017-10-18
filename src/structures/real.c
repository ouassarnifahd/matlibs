#include "structures/real.h"

double Mat_pow(double x, size_t n) {
    double power = 1;
    for (size_t i = 0; i < n; i++) {
        power *= x;
    }
    return power;
}

double Mat_root(double x, size_t n) {
    double root, precision = 1e-6;
    for (root = 1; Mat_pow(root, n) <= x; ++root);
    for (--root; Mat_pow(root, n) < x; root += precision);
    return root;
}

void* real_new(double x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    real_t new = malloc(SIZE_REAL);
    #ifdef DEBUG_MALLOC
    if (new) debug("Memory allocation 'real_t': %zu Octets", SIZE_REAL);
    #endif
    alloc_check(new);
    #ifdef DEBUG_INIT
    debug("Initialising 'real_t' <- "PRINT_REAL, x);
    #endif
    *new = x;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return (void*)new;
}

void real_delete(void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        free(x);
        #ifdef DEBUG_FREE
        debug("Memory freed (real_t)");
        #endif
        x = NULL;
    } else {
        warning("Can't delete a NULL pointer!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

bool real_is_null(const void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        real_t tmp = (const real_t)x;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return !*tmp;
    } else {
        error("NULL pointer is already null!");
    }
}

bool real_is_positive(const void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        real_t tmp = (const real_t)x;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return *tmp >= 0;
    } else {
        error("NULL pointer can't be positive!");
    }
}

bool real_is_negative(const void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        real_t tmp = (const real_t)x;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return *tmp < 0;
    } else {
        error("NULL pointer can't be negative!");
    }
}

void real_zero(void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x) {
        x = malloc(SIZE_REAL);
        #ifdef DEBUG_MALLOC
        if (x) debug("Memory allocation 'real_t': %zu Octets", SIZE_REAL);
        #endif
        alloc_check(x);
    }
    #ifdef DEBUG_INIT
    debug("Initialising 'real_t' <- 0");
    #endif
    *(real_t)x = 0;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_one(void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x) {
        x = malloc(SIZE_REAL);
        #ifdef DEBUG_MALLOC
        if (x) debug("Memory allocation 'real_t': %zu Octets", SIZE_REAL);
        #endif
        alloc_check(x);
    }
    #ifdef DEBUG_INIT
    debug("Initialising 'real_t' <- 0");
    #endif
    *(real_t)x = 1;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_inv(void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        real_t tmp = (real_t)x;
        *tmp = -*tmp;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
    } else {
        error("NULL pointer can't be inversed!");
    }
}

void real_add(const void* x1, const void* x2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        real_t pa = (const real_t)x1, pb = (const real_t)x2;
        if (!res) {
            res = malloc(SIZE_REAL);
            #ifdef DEBUG_MALLOC
            if (res) debug("Memory allocation 'real_t': %zu Octets", SIZE_REAL);
            #endif
            alloc_check(res);
        }
        *(real_t)res = *pa + *pb;
        #ifdef DEBUG_OPERATION
        debug("Operation 'real_t' <- "PRINT_REAL" = "PRINT_REAL" + "PRINT_REAL, *(real_t)res, *pa, *pb);
        #endif
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_sub(const void* x1, const void* x2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        real_t pa = (const real_t)x1, pb = (const real_t)x2;
        if (!res) {
            res = malloc(SIZE_REAL);
            #ifdef DEBUG_MALLOC
            if (res) debug("Memory allocation 'real_t': %zu Octets", SIZE_REAL);
            #endif
            alloc_check(res);
        }
        *(real_t)res = *pa - *pb;
        #ifdef DEBUG_OPERATION
        debug("Operation 'real_t' <- "PRINT_REAL" = "PRINT_REAL" - "PRINT_REAL, *(real_t)res, *pa, *pb);
        #endif
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_mult(const void* x1, const void* x2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        real_t pa = (const real_t)x1, pb = (const real_t)x2;
        if (!res) {
            res = malloc(SIZE_REAL);
            #ifdef DEBUG_MALLOC
            if (res) debug("Memory allocation 'real_t': %zu Octets", SIZE_REAL);
            #endif
            alloc_check(res);
        }
        *(real_t)res = *pa * *pb;
        #ifdef DEBUG_OPERATION
        debug("Operation 'real_t' <- "PRINT_REAL" = "PRINT_REAL" * "PRINT_REAL, *(real_t)res, *pa, *pb);
        #endif
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_div(const void* x1, const void* x2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else if (real_is_null(x2)) {
        if (res) {
            real_delete(res);
        }
        error("Division by zero!");
    } else {
        real_t pa = (const real_t)x1, pb = (const real_t)x2;
        if (!res) {
            res = malloc(SIZE_REAL);
            #ifdef DEBUG_MALLOC
            if (res) debug("Memory allocation 'real_t': %zu Octets", SIZE_REAL);
            #endif
            alloc_check(res);
        }
        *(real_t)res = *pa / *pb;
        #ifdef DEBUG_OPERATION
        debug("Operation 'real_t' <- "PRINT_REAL" = "PRINT_REAL" / "PRINT_REAL, *(real_t)res, *pa, *pb);
        #endif
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_print(const void* x) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!x) {
        error("NULL pointer print!");
    } else {
        real_t tmp = (const real_t)x;
        printf(PRINT_REAL, *tmp);
    }
    #ifdef DEBUG_PRINT
    printf("\n");
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
    debug("FY!");
    return 0;
}
#endif
