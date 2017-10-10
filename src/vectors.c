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

int main(int argc, char const *argv[]) {
    math_entity_t entity = &complexe_entity;
    vector_t vect1 = vect_new(2, entity, ((math_complexe_new_t)entity->new)(1, 1), ((math_complexe_new_t)entity->new)(1, -1));
    vector_t vect2 = vect_new(2, entity, ((math_complexe_new_t)entity->new)(1, 1), ((math_complexe_new_t)entity->new)(1, 1));
    vector_t vect12 = vect_new(3, entity, ((math_complexe_new_t)entity->new)(0, 0), ((math_complexe_new_t)entity->new)(0, 0), ((math_complexe_new_t)entity->new)(0, 1));
    vect_add(vect1, vect2, vect12);
    vect_print(vect12);
    vect_delete(vect1);
    vect_delete(vect2);
    vect_delete(vect12);
    return 0;
}
#endif
