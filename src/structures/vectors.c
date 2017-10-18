#include "structures/vectors.h"

static void* vect_init(size_t size, math_entity_t ent) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    vector_t vect = malloc(SIZE_VECT);
    #ifdef DEBUG_MALLOC
    if (vect) debug("Memory allocation 'vect': %zu Octets", SIZE_VECT);
    #endif
    alloc_check(vect);
    vect->ent = ent;
    vect->size = size;
    vect->vector = malloc(size * ent->size_element);
    #ifdef DEBUG_MALLOC
    if (vect) debug("Memory allocation 'vect->vector': %zu Octets", size * ent->size_element);
    #endif
    alloc_check(vect->vector);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return (void*)vect;
}

void* vect_new(size_t size, math_entity_t ent, ...) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    vector_t vect = vect_init(size, ent);
    void* arg = NULL;
    va_list args;
    va_start(args, ent);
    for (size_t i = 0; i < size; i++) {
        arg = va_arg(args, void*);
        memcpy((char*)vect->vector + i * vect->ent->size_element, arg, ent->size_element);
        ent->delete(arg);
    }
    va_end(args);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return (void*)vect;
}

void vect_delete(void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    vector_t vect = (vector_t)x;
    if (vect) {
        if (vect->vector) {
            free(vect->vector);
            #ifdef DEBUG_FREE
            debug("Memory freed (vect->vector)");
            #endif
            vect->vector = NULL;
        }
        free(vect);
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

bool vect_is_null(const void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        size_t i = 0;
        vector_t vect = (const vector_t)x;
        while(i < vect->size && vect->ent->is_null((char*)vect->vector + i * vect->ent->size_element)) i++;
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

void vect_zero(void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        vector_t vect = (vector_t)x;
        for (size_t i = 0; i < vect->size; i++)
            vect->ent->zero(((char*)vect->vector + i * vect->ent->size_element));
    } else {
        error("NULL pointer methode!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void vect_one(void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        vector_t vect = (vector_t)x;
        for (size_t i = 0; i < vect->size; i++)
            vect->ent->one((void*)((char*)vect->vector + i * vect->ent->size_element));
    } else {
        error("NULL pointer methode!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void vect_inv(void* x) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (x) {
        vector_t vect = (vector_t)x;
        for (size_t i = 0; i < vect->size; i++)
            vect->ent->inv((void*)((char*)vect->vector + i * vect->ent->size_element));
    } else {
        error("NULL pointer can't be inversed!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void vect_add(const void* x1, const void* x2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        vector_t vect1 = (const vector_t)x1, vect2 = (const vector_t)x2, vect = (vector_t)res;
        if (vect1->ent->size_element != vect2->ent->size_element) {
            error("Incompatible vector size operation");
        } else {
            size_t max_vects = Mat_max(vect1->size, vect2->size);
            if (!res) {
                warning("'res' is undefined!");
                res = vect_init(max_vects, vect1->ent);
            }
            for (size_t i = 0; i < max_vects; i++) {
                if (vect1->size < i) {
                    *((char*)vect->vector + i * vect->ent->size_element) = *((char*)vect2->vector + i * vect2->ent->size_element);
                } if (vect2->size < i) {
                    *((char*)vect->vector + i * vect->ent->size_element) = *((char*)vect1->vector + i * vect1->ent->size_element);
                } else {
                    vect->ent->add((char*)vect1->vector + i * vect1->ent->size_element, (char*)vect2->vector + i * vect2->ent->size_element, (char*)vect->vector + i * vect->ent->size_element);
                }
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void vect_sub(const void* x1, const void* x2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        vector_t vect1 = (const vector_t)x1, vect2 = (const vector_t)x2, vect = (vector_t)res;
        if (vect1->ent->size_element != vect2->ent->size_element) {
            error("Incompatible vector size operation");
        } else {
            size_t max_vects = Mat_max(vect1->size, vect2->size);
            if (!res) {
                warning("'res' is undefined!");
                res = vect_init(max_vects, vect1->ent);
            }
            for (size_t i = 0; i < max_vects; i++) {
                if (vect1->size < i) {
                    *((char*)vect->vector + i * vect->ent->size_element) = *((char*)vect2->vector + i * vect2->ent->size_element);
                    vect2->ent->inv((char*)vect->vector + i * vect->ent->size_element);
                } if (vect2->size < i) {
                    *((char*)vect->vector + i * vect->ent->size_element) = *((char*)vect1->vector + i * vect1->ent->size_element);
                } else {
                    vect->ent->sub((char*)vect1->vector + i * vect1->ent->size_element, (char*)vect2->vector + i * vect2->ent->size_element, (char*)vect->vector + i * vect->ent->size_element);
                }
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void vect_mult(const void* x1, const void* x2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        vector_t vect1 = (const vector_t)x1, vect2 = (const vector_t)x2, vect = (vector_t)res;
        if (vect1->ent->size_element != vect2->ent->size_element) {
            error("Incompatible vector size operation");
        } else {
            size_t max_vects = Mat_max(vect1->size, vect2->size);
            if (!res) {
                warning("'res' is undefined!");
                res = vect_init(max_vects, vect1->ent);
            }
            for (size_t i = 0; i < vect1->size; i++) {
                 vect1->ent->mult((char*)vect1->vector + i * vect1->ent->size_element,
                                  (char*)vect2->vector + i * vect2->ent->size_element,
                                  (char*)vect->vector  + i * vect->ent->size_element);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void vect_dot(const void* x1, const void* x2 , void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        vector_t vect1 = (const vector_t)x1, vect2 = (const vector_t)x2;
        void* dot_mult = malloc(vect1->ent->size_element);
        #ifdef DEBUG_MALLOC
        if (dot_mult) debug("Memory allocation 'dot_mult': %zu Octets", vect1->ent->size_element);
        #endif
        alloc_check(dot_mult);
        if (vect1->ent->size_element != vect2->ent->size_element) {
            error("Incompatible operation");
        } else {
            size_t min_vects = Mat_min(vect1->size, vect2->size);
            if (!res) {
                warning("'res' is undefined!");
                res = malloc(vect1->ent->size_element);
                #ifdef DEBUG_MALLOC
                if (res) debug("Memory allocation 'res': %zu Octets", vect1->ent->size_element);
                #endif
                alloc_check(res);
            }
            for (size_t i = 0; i < min_vects; i++) {
                vect1->ent->mult((char*)vect1->vector + i * vect1->ent->size_element,
                                 (char*)vect2->vector + i * vect2->ent->size_element,
                                 dot_mult);
                vect1->ent->add(res, dot_mult, res);
            }
        }
        vect1->ent->delete(dot_mult);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

// /!\ O(n2)
void vect_cauchy_mult(const void* x1, const void* x2, void* res) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!x1 || !x2) {
        error("NULL pointer operation!");
    } else {
        vector_t vect1 = (const vector_t)x1, vect2 = (const vector_t)x2, vect = (vector_t)res;
        void* tmp = malloc(vect1->ent->size_element);
        #ifdef DEBUG_MALLOC
        if (tmp) debug("Memory allocation 'tmp': %zu Octets", vect1->ent->size_element);
        #endif
        alloc_check(tmp);
        if (vect1->ent->size_element != vect2->ent->size_element) {
            error("Incompatible operation");
            vect = NULL;
        } else {
            for (size_t i = 0; i < vect1->size + vect2->size - 1; i++) {
                for (size_t k = 0; k <= i; k++) {
                    #ifdef DEBUG
                        printf("c%zu = ", i);
                        vect1->ent->print((char*)vect->vector + i * vect->ent->size_element);
                        printf(" + ");
                        vect1->ent->print((char*)vect1->vector + k * vect1->ent->size_element);
                        printf(" * ");
                        vect1->ent->print((char*)vect2->vector + (i - k) * vect2->ent->size_element);
                        printf(" (k=%zu) (i-k=%zu)\n", k, i - k);
                    #endif
                    if (k < vect1->size && (i-k) < vect2->size) {
                        vect1->ent->mult((char*)vect1->vector + k * vect1->ent->size_element,
                                         (char*)vect2->vector + (i - k) * vect2->ent->size_element,
                                         tmp);
                        vect1->ent->add((char*)vect->vector + i * vect->ent->size_element,
                                        tmp,
                                        (char*)vect->vector + i * vect->ent->size_element);
                    }
                }
            }
        }
        vect1->ent->delete(tmp);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void vect_print_colonne(const void* x) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!x) {
        error("NULL pointer print!");
    } else {
        vector_t vect = (const vector_t)x;
        printf("\n");
        for (size_t i = 0; i < vect->size; ++i) {
            printf("\t[ ");
            vect->ent->print((char*)vect->vector + i * vect->ent->size_element);
            printf(" ]\n");
        }
        printf("\n");
    }
    #ifdef DEBUG_PRINT
    debug("leaving print function!\n");
    #endif
}

void vect_print_ligne(const void* x) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (!x) {
        error("NULL pointer print!");
    } else {
        vector_t vect = (const vector_t)x;
        printf("\t[ ");
        for (size_t i = 0; i < vect->size; ++i) {
            vect->ent->print((char*)vect->vector + i * vect->ent->size_element);
            if (i != vect->size - 1) printf("   "); // A revoir!
        }
        printf(" ]\n");
    }
    #ifdef DEBUG_PRINT
    debug("leaving print function!\n");
    #endif
}

#ifdef DEBUG
#include "structures/alglib.h"

int main(int argc, char const *argv[]) {
    #if defined (__x86_64__)
        debug("64-bit architecture!\n");
    #elif defined (__i386__)
        warning("32-bit architecture!\n");
    #else
        error("Incompatible architecture!");
    #endif
    math_entity_t entity = &real_entity;
    math_vect_new_t new = vect_new;
    math_real_new_t ent_new = entity->new;
    math_methode_t ent_delete = entity->delete;
    math_methode_t delete = vect_delete;
    math_operation_t operation = vect_add;
    math_print_t print = vect_print_colonne;

    void* vect1 = new(6, entity, ent_new(100),
                                 ent_new(2),
                                 ent_new(3),
                                 ent_new(4),
                                 ent_new(5),
                                 ent_new(6));

    void* vect2 = new(6, entity, ent_new(1),
                                 ent_new(2),
                                 ent_new(3),
                                 ent_new(4),
                                 ent_new(5),
                                 ent_new(6));

    void* vect12 = vect_init(6, entity);

    void* dot = ent_new(0);

    vect_dot(vect1, vect2, dot);

    operation(vect1, vect2, vect12);

    printf("dot = "); entity->print(dot); printf("\n");

    print(vect1);
    print(vect2);
    print(vect12);

    free(dot);
    delete(vect1);
    delete(vect2);
    delete(vect12);
    debug("FY!");
    return 0;
}
#endif
