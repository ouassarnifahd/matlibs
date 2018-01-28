#include "std.h"
#include "core/math/real.h"

static sreal_t Mat_pow(sreal_t x, size_t n) {
    return (n > 1)? x * Mat_pow(x, n - 1): x;
}

void real_pow(const real_t x, size_t power, real_t res) {
    *res = 1;
    for (size_t i = 0; i < power; i++) {
        *res *= *x;
    }
}

void real_root(const real_t x, size_t root, real_t res) {
    for (*res = 1; Mat_pow(*res, root) <= *x; ++*res);
    for (--*res; Mat_pow(*res, root) < *x; *res += EPSILON);
}

bool real_is_null(const real_t x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return !*x;
    } else {
        error("NULL pointer is already null!");
    }
}

bool real_is_positive(const real_t x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return *x >= 0;
    } else {
        error("NULL pointer can't be positive!");
    }
}

bool real_is_negative(const real_t x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return *x < 0;
    } else {
        error("NULL pointer can't be negative!");
    }
}

void real_zero(real_t x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        #ifdef DEBUG_INIT
        debug("Initialising 'real_t' <- 0");
        #endif
        *x = 0;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_one(real_t x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        #ifdef DEBUG_INIT
        debug("Initialising 'real_t' <- 1");
        #endif
        *x = 1;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_inv(real_t x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        *x = -*x;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
    } else {
        error("NULL pointer can't be inversed!");
    }
}

void real_swap(const real_t x1, const real_t x2) {
    sreal_t tmp = *x1;
    *x1 = *x2;
    *x2 = tmp;
}

void real_add(const real_t x1, const real_t x2, real_t res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        if (!res) {
            warning("'res' is NULL");
        }
        #ifdef DEBUG_OPERATION
        sreal_t a = *x1, b = *x2;
        debug("Operation 'real_t' <- "PRINT_REAL" = "PRINT_REAL" + "PRINT_REAL, a + b, a, b);
        #endif
        *res = *x1 + *x2;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_sub(const real_t x1, const real_t x2, real_t res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        if (!res) {
            warning("'res' is NULL");
        }
        #ifdef DEBUG_OPERATION
        sreal_t a = *x1, b = *x2;
        debug("Operation 'real_t' <- "PRINT_REAL" = "PRINT_REAL" - "PRINT_REAL, a - b, a, b);
        #endif
        *res = *x1 - *x2;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_mult(const real_t x1, const real_t x2, real_t res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        if (!res) {
            warning("'res' is NULL");
        }
        #ifdef DEBUG_OPERATION
        sreal_t a = *x1, b = *x2;
        debug("Operation 'real_t' <- "PRINT_REAL" = "PRINT_REAL" * "PRINT_REAL, a * b, a, b);
        #endif
        *res = *x1 * *x2;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_div(const real_t x1, const real_t x2, real_t res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else if (real_is_null(x2)) {
        error("Division by zero!");
    } else {
      if (!res) {
          warning("'res' is NULL");
      }
      #ifdef DEBUG_OPERATION
      sreal_t a = *x1, b = *x2;
      debug("Operation 'real_t' <- "PRINT_REAL" = "PRINT_REAL" / "PRINT_REAL, a / b, a, b);
      #endif
        *res = *x1 / *x2;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void real_print(const real_t x) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!x) {
        error("NULL pointer print!");
    } else {
        Mat_printf(PRINT_REAL, *x);
    }
    #ifdef DEBUG_PRINT
    Mat_printf("\n");
    debug("leaving print function!\n");
    #endif
}
