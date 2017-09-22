#include "vectors.h"

vector_t vect_zero(size_t size) {
    vector_t vect;
    vect.size = size;
    vect.vector = malloc(size * sizeof(complexe_t));
    for (size_t i = 0; i < size; i++) {
        vect.vector[i] = real_new(0);
    }
    return vect;
}

vector_t vect_one(size_t size) {
    vector_t vect;
    vect.size = size;
    vect.vector = malloc(size * sizeof(complexe_t));
    for (size_t i = 0; i < size; i++) {
        vect.vector[i] = real_new(1);
    }
    return vect;
}

vector_t vect_new(size_t size, ...) {
    va_list args;
    vector_t vect = vect_zero(size);
    va_start(args, size);
    for (size_t i = 0; i < size; i++) {
        vect.vector[i] = va_arg(args, complexe_t);
    }
    va_end(args);
    return vect;
}

size_t getSize(vector_t vect) {
    return vect.size;
}

void vect_delete(vector_t vect) {
    if(vect.vector) free(vect.vector);
}

void vect_print(vector_t vect) {
    printf("[");
    for (size_t i = 0; i < vect.size; ++i) {
        complexe_print(vect.vector[i]);
        if (i != vect.size - 1) printf(" ,");
    }
    printf(" ]\n");
}

vector_t vect_add(vector_t vect1, vector_t vect2) {
    vect1.size = Mat_min(vect1.size, vect2.size);
    for (size_t i = 0; i < vect1.size; i++) {
        vect1.vector[i] = complexe_add(vect1.vector[i], vect2.vector[i]);
    }
    return vect1;
}

vector_t vect_mult(vector_t vect, complexe_t scalar) {
    for (size_t i = 0; i < vect.size; i++) {
        vect.vector[i] = complexe_mult(vect.vector[i], scalar);
    }
    return vect;
}

vector_t vect_mult_vect(vector_t vect1, vector_t vect2) {
    vect1.size = Mat_min(vect1.size, vect2.size);
    for (size_t i = 0; i < vect1.size; i++) {
        vect1.vector[i] = complexe_mult(vect1.vector[i], vect2.vector[i]);
    }
    return vect1;
}

complexe_t vect_dot(vector_t vect1, vector_t vect2) {
    complexe_t dot_mult;
    vect1.size = Mat_min(vect1.size, vect2.size);
    for (size_t i = 0; i < vect1.size; i++) {
        dot_mult = complexe_add(dot_mult, complexe_mult(vect1.vector[i], vect2.vector[i]));
    }
    return dot_mult;
}

// /!\ O(n2)
vector_t vect_cauchy_mult(vector_t vect1, vector_t vect2) {
    vector_t vect = vect_zero(vect1.size + vect2.size - 1);
    for (size_t i = 0; i < vect.size; i++) {
        for (size_t k = 0; k <= i; k++) {
            #ifdef DEBUG
                printf("c%zu = ", i);
                complexe_print(vect.vector[i]);
                printf(" + ");
                complexe_print(vect1.vector[k]);
                printf(" * ");
                complexe_print(vect2.vector[i - k]);
                printf(" (k=%zu) (i-k=%zu)\n", k, i-k);
            #endif
            if (k < vect1.size && (i-k) < vect2.size) {
                vect.vector[i] = complexe_add(vect.vector[i], complexe_mult(vect1.vector[k], vect2.vector[i - k]));
            }
        }
    }
    return vect;
}

#ifdef DEBUG
int main(int argc, char const *argv[]) {
    // printf("Sizeof(complexe_t) %lu\n", sizeof(complexe_t));
    // complexe_mem_view(complexe_new(1,1));
    vector_t vect1 = vect_new(2, real_new(1), real_new(1));
    vector_t vect2 = vect_new(2, real_new(1), real_new(1));
    // vect_print(vect1);
    // printf("**\n");
    // vect_print(vect2);
    // printf("=\n");
    vector_t vect12 = vect_cauchy_mult(vect1, vect2);
    vect_print(vect12);
    vect_delete(vect1);
    vect_delete(vect2);
    vect_delete(vect12);
    return 0;
}
#endif
