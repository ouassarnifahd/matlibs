#include "structures/entity.h"

math_entity_t entity_new(size_t size_element) {
    math_entity_t ent = malloc(sizeof(struct math));
    alloc_check(ent);
    ent->size_element = size_element;
    ent->new = math_new; ent->delete = math_methode;
    ent->zero = math_methode; ent->one = math_methode; ent->inv = math_methode;
    ent->is_null = math_test; ent->is_positive = math_test; ent->is_negative = math_test;
    ent->add = math_operation; ent->sub = math_operation; ent->mult = math_operation; ent->div = math_operation;
    ent->accumulator = math_accumulator; ent->print = math_print;
    return ent;
}

void entity_delete(math_entity_t ent) {
    if (ent) {
        free(ent);
        ent = NULL;
    }
}

void* math_new(void) {
    return NULL;
}

bool math_test(const void *x) {
    return true;
}

void math_methode(void *x) {
    if (x) x = NULL;
}

void math_operation(const void *x1, const void *x2, void *res) {
    res = NULL;
}

void math_accumulator(const void *x, math_methode_t init, math_operation_t operation, size_t iters, void *res) {
    res = NULL;
}

void math_print(const void *x) {
    printf("D-entity");
}
