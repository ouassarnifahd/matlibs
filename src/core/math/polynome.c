#include "std.h"
#include "core/math/polynome.h"

struct polynome {
    ssize_t deg;
    pow_t power;
    char variable;
    root_t roots;
    cvector_t vect;
};

ssize_t polynome_degre(const polynome_t polynome) {
    if (polynome->vect) {
        size_t size;
        // for (
            size = polynome->vect->size;
        //      size > 0 && complexe_is_null(&polynome->vect->vector[size]);
        //      size--) {}
        return size - 1;
    } else {
        error("NULL don't have a degre!");
    }
}

polynome_t polynome_init(char variable, pow_t power) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    polynome_t new = Mat_alloc(SIZE_POLYNOME);
    alloc_check(new);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'new': %zu Octets", SIZE_CVECT);
    #endif
    new->deg = -1;
    new->power = power;
    new->variable = variable;
    new->roots = NULL;
    new->vect = NULL;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return new;
}

polynome_t polynome_new(char variable, pow_t power, cvector_t vect) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    polynome_t new = polynome_init(variable, power);
    new->vect = vect;
    new->deg = polynome_degre(new);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return new;
}

void polynome_delete(polynome_t polynome) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (polynome) {
        // if (polynome->vect) {
        //     cvect_delete(polynome->vect);
        //     polynome->vect = NULL;
        // }
        Mat_free(polynome);
        #ifdef DEBUG_FREE
        debug("Memory freed (polynome)");
        #endif
        polynome = NULL;
    } else {
        warning("NULL pointer exeption!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

bool polynome_is_null(const polynome_t polynome) {
    return cvect_is_null(polynome->vect);
}

bool polynome_is_complexe(const polynome_t polynome) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (polynome) {
        return polynome->deg == 0;
    } else {
        error("NULL pointer is not complexe!");
    }
}

polynome_t polynome_add(const polynome_t polynome1, const polynome_t polynome2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    polynome_t res = NULL;
    if (!polynome1 || !polynome2) {
        error("NULL pointer operation!");
    } else if (polynome1->variable != polynome2->variable) {
        error("Polynomes Variable must agree!");
    } else if (polynome1->power != polynome2->power) {
        error("Polynomes Power must agree!");
    } else {
        res = polynome_init(polynome1->variable, polynome1->power);
        res->vect = cvect_add(polynome1->vect, polynome2->vect);
        res->deg = polynome_degre(res);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

polynome_t polynome_sub(const polynome_t polynome1, const polynome_t polynome2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    polynome_t res = NULL;
    if (!polynome1 || !polynome2) {
        error("NULL pointer operation!");
    } else if (polynome1->variable != polynome2->variable) {
        error("Polynomes Variable must agree!");
    } else if (polynome1->power != polynome2->power) {
        error("Polynomes Power must agree!");
    } else {
        res = polynome_init(polynome1->variable, polynome1->power);
        res->vect = cvect_sub(polynome1->vect, polynome2->vect);
        res->deg = polynome_degre(res);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

polynome_t polynome_mult(const polynome_t polynome1, const polynome_t polynome2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    polynome_t res = NULL;
    if (!polynome1 || !polynome2) {
        error("NULL pointer operation!");
    } else if (polynome1->variable != polynome2->variable) {
        error("Polynomes Variable must agree!");
    } else if (polynome1->power != polynome2->power) {
        error("Polynomes Power must agree!");
    } else {
        res = polynome_init(polynome1->variable, polynome1->power);
        res->vect = cvect_conv(polynome1->vect, polynome2->vect);
        res->deg = polynome_degre(res);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

polynome_t polynome_pow(const polynome_t polynome, size_t power) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    polynome_t res = NULL;
    if (!polynome) {
        error("NULL pointer operation!");
    } else {
        res = polynome_init(polynome->variable, polynome->power);
        // res->vect = cvect_pow(polynome->vect, power);
        res->deg = polynome_degre(res);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

scomplexe_t polynomial_fonction(const polynome_t polynome, scomplexe_t x) {
    scomplexe_t res = polynome->vect->vector[0];
    scomplexe_t xi;
    for (size_t i = 1; i < polynome->vect->size; i++) {
        complexe_mult(&x, &polynome->vect->vector[i], &xi);
        complexe_add(&res, &xi, &res);
    }
    return res;
}

// root_t polynome_racines(const polynome_t polynome);

void polynome_print(const polynome_t polynome) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!polynome) {
        error("NULL pointer print!");
    } else {
        #ifdef DEBUG
        Mat_printf("");
        #endif
        for (size_t i = 0; i <= polynome->deg; i++) {
            cvector_t vect = polynome->vect;
            if (!complexe_is_null(&vect->vector[i])) {
                if(i == 0) {
                    complexe_print(&vect->vector[i]);
                } else {
                    if (!(complexe_is_real(&vect->vector[i]) || complexe_is_imaginary(&vect->vector[i]))) {
                        Mat_printf(" + (");
                    } else {
                        Mat_printf("%s", (Mat_signe(vect->vector[i].alg.ztab[1])|| Mat_signe(vect->vector[i].alg.ztab[0]))? " " : " +");
                    }
                    complexe_print(&vect->vector[i]);
                    if (!(complexe_is_real(&vect->vector[i]) || complexe_is_imaginary(&vect->vector[i]))) Mat_printf(")");
                    if (i == 1) {
                        Mat_printf("%c%s", polynome->variable, (polynome->power == Positive)?"\0":"^-1");
                    } else {
                        Mat_printf("%c%s%zu", polynome->variable, (polynome->power == Positive)?"^":"^-", i);
                    }
                }
            }
        }
        Mat_printf("\n");
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

    cvector_t vect = cvect_new(2, complexe_new(1,0), complexe_new(1, 0));
    polynome_t pa = polynome_new('X', Positive, vect);
    Mat_printf("Pa = "); polynome_print(pa);
    polynome_t pb = polynome_new('X', Positive, vect);
    Mat_printf("Pb = "); polynome_print(pb);

    polynome_t p = polynome_mult(pa, pb);
    Mat_printf("P  = "); polynome_print(p);

    scomplexe_t p0 = polynomial_fonction(p, complexe_new(0, 0));

    Mat_printf("P(0) = "); complexe_print(&p0); Mat_printf("\n");

    polynome_delete(p);
    polynome_delete(pa);
    polynome_delete(pb);
    cvect_delete(vect);

    debug("FY!");
    return 0;
}
#endif
