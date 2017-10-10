#include "vectors.h"

void* vect_new(size_t size, math_entity_t ent, ...) {
    va_list args;
    vector_t vect = malloc(sizeof(struct vect));
    vect->ent = ent;
    vect->size = size;
    vect->vector = malloc(size * ent->size_element);
    va_start(args, ent);
    for (size_t i = 0; i < size; i++) {
        memcpy((char*)vect->vector + i * vect->ent->size_element, va_arg(args, void*), ent->size_element);
    }
    va_end(args);
    return (void*)vect;
}

void vect_delete(void* x) {
    vector_t vect = (vector_t)x;
    if(vect->vector) free(vect->vector);
    if(vect) free(vect);
}

void vect_zero(void* x) {
    vector_t vect = (vector_t)x;
    for (size_t i = 0; i < vect->size; i++) {
        vect->ent->zero((void*)((char*)vect->vector + i * vect->ent->size_element));
    }
}

void vect_one(void* x) {
    vector_t vect = (vector_t)x;
    for (size_t i = 0; i < vect->size; i++) {
        vect->ent->one((void*)((char*)vect->vector + i * vect->ent->size_element));
    }
}

void vect_inv(void* x) {
    vector_t vect = (vector_t)x;
    for (size_t i = 0; i < vect->size; i++) {
        vect->ent->inv((void*)((char*)vect->vector + i * vect->ent->size_element));
    }
}

void vect_add(const void* x1, const void* x2, void* res) {
    vector_t vect1 = (const vector_t)x1, vect2 = (const vector_t)x2, vect = (vector_t)res;
    if (vect1->ent->size_element != vect2->ent->size_element) {
        vect = NULL;
    } else {
        size_t max_vects = Mat_max(vect1->size, vect2->size);
        for (size_t i = 0; i < max_vects; i++) {
            if (vect1->size < i)
                *((char*)vect->vector + i * vect->ent->size_element) = *((char*)vect2->vector + i * vect2->ent->size_element);
            if (vect2->size < i)
                *((char*)vect->vector + i * vect->ent->size_element) = *((char*)vect1->vector + i * vect1->ent->size_element);
            else
                vect->ent->add((char*)vect1->vector + i * vect1->ent->size_element, (char*)vect2->vector + i * vect2->ent->size_element, (char*)vect->vector + i * vect->ent->size_element);
        }
    }
}

void vect_mult(const void* x1, const void* x2, void* res) {
    vector_t vect1 = (const vector_t)x1, vect = (vector_t)res;
    for (size_t i = 0; i < vect1->size; i++) {
         vect1->ent->mult((char*)vect1->vector + i * vect1->ent->size_element, x2, (char*)vect->vector + i * vect->ent->size_element);
    }
}

void vect_mult_vect(const void* x1, const void* x2, void* res) {
    vector_t vect1 = (const vector_t)x1, vect2 = (const vector_t)x2, vect = (vector_t)res;
    if (vect1->ent->size_element != vect2->ent->size_element) {
        vect = NULL;
    } else {
        size_t min_vects = Mat_min(vect1->size, vect2->size);
        for (size_t i = 0; i < min_vects; i++) {
            vect1->ent->mult((char*)vect1->vector + i * vect1->ent->size_element, (char*)vect2->vector + i * vect2->ent->size_element, (char*)vect->vector + i * vect->ent->size_element);
        }
    }
}

void vect_dot(const void* x1, const void* x2 , void* res) {
    vector_t vect1 = (const vector_t)x1, vect2 = (const vector_t)x2;
    void* dot_mult = malloc(vect1->ent->size_element);
    if (vect1->ent->size_element != vect2->ent->size_element) {
        res = NULL;
    } else {
        size_t min_vects = Mat_min(vect1->size, vect2->size);
        for (size_t i = 0; i < min_vects; i++) {
            vect1->ent->mult((char*)vect1->vector + i * vect1->ent->size_element, (char*)vect2->vector + i * vect2->ent->size_element, dot_mult);
            vect1->ent->add(res, dot_mult, res);
        }
    }
    free(dot_mult);
}

// /!\ O(n2)
void vect_cauchy_mult(const void* x1, const void* x2, void* res) {
    vector_t vect1 = (const vector_t)x1, vect2 = (const vector_t)x2, vect = (vector_t)res;
    void* tmp = malloc(vect1->ent->size_element);
    if (vect1->ent->size_element != vect2->ent->size_element) {
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
                    vect1->ent->mult((char*)vect1->vector + k * vect1->ent->size_element, (char*)vect2->vector + (i - k) * vect2->ent->size_element, tmp);
                    vect1->ent->add((char*)vect->vector + i * vect->ent->size_element, tmp, (char*)vect->vector + i * vect->ent->size_element);
                }
            }
        }
    }
    free(tmp);
}

void vect_print(const void* x) {
    vector_t vect = (const vector_t)x;
    printf("\n");
    for (size_t i = 0; i < vect->size; ++i) {
        printf("\t");
        vect->ent->print((char*)vect->vector + i * vect->ent->size_element);
        printf("\n");
    }
}

void vect_print_ligne(const void* x) {
    vector_t vect = (const vector_t)x;
    printf("\n\t");
    for (size_t i = 0; i < vect->size; ++i) {
        vect->ent->print((char*)vect->vector + i * vect->ent->size_element);
        if (i != vect->size - 1) printf("   ");
    }
}

#ifdef DEBUG
#include "complexe.h"
#include "real.h"

const struct math complexe_entity = {
    SIZE_COMPLEXE,
    (math_new_t)complexe_new,
    complexe_delete, complexe_zero, complexe_one, complexe_inv,
    complexe_is_null, NULL, NULL,
    complexe_add, complexe_sub, complexe_mult, complexe_div,
    complexe_print
};

typedef void* (*math_complexe_new_t) (double, double);

const struct math real_entity = {
    SIZE_REAL,
    (math_new_t)real_new,
    real_delete, real_zero, real_one, real_inv,
    real_is_null, real_is_positive, real_is_negative,
    real_add, real_sub, real_mult, real_div,
    real_print
};

typedef void* (*math_real_new_t) (double);

const struct math vect_entity = {
    SIZE_VECT,
    (math_new_t)vect_new,
    vect_delete, vect_zero, vect_one, vect_inv,
    NULL, NULL, NULL,
    vect_add, NULL, vect_mult, NULL,
    vect_print_ligne
};

typedef void* (*math_vect_new_t) (size_t, math_entity_t, ...);

int main(int argc, char const *argv[]) {
    math_entity_t top_entity = &vect_entity, entity = &real_entity;
    math_vect_new_t new = vect_new, top_ent_new = top_entity->new;
    math_real_new_t ent_new = entity->new;
    math_methode_t top_ent_delete = top_entity->delete, ent_delete = entity->delete;
    math_methode_t delete = vect_delete;
    math_print_t print = vect_print;

    void* V11 = ent_new(1);
    void* V12 = ent_new(0);
    void* V1 = top_ent_new(2, entity, V11, V12);

    void* V21 = ent_new(0);
    void* V22 = ent_new(1);
    void* V2 = top_ent_new(2, entity, V21, V22);

    void* vect1 = new(2, top_entity, V1, V2);

    void* W11 = ent_new(1);
    void* W12 = ent_new(0);
    void* W1 = top_ent_new(2, entity, W11, W12);

    void* W21 = ent_new(0);
    void* W22 = ent_new(1);
    void* W2 = top_ent_new(2, entity, W21, W22);

    void* vect2 = new(2, top_entity, W1, W2);

    void* X11 = ent_new(0);
    void* X12 = ent_new(0);
    void* X1 = top_ent_new(2, entity, X11, X12);

    void* X21 = ent_new(0);
    void* X22 = ent_new(0);
    void* X2 = top_ent_new(2, entity, X21, X22);

    void* vect12 = new(2, top_entity, X1, X2);

    vect_add(vect1, vect2, vect12);

    print(vect1);
    print(vect2);
    print(vect12);

    ent_delete(V11); ent_delete(V12); ent_delete(V21); ent_delete(V22);
    ent_delete(W11); ent_delete(W12); ent_delete(W21); ent_delete(W22);
    ent_delete(X11); ent_delete(X12); ent_delete(X21); ent_delete(X22);
    delete(V1); delete(V2); delete(W1); delete(W2); delete(X1); delete(X2);
    top_ent_delete(vect1); top_ent_delete(vect2); top_ent_delete(vect12);
    return 0;
}
#endif
