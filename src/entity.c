#include "entity.h"

math_entity_t entity_new(size_t size_element, math_new_t new, math_methode_t delete, math_methode_t zero, math_methode_t one, math_methode_t inv, math_test_t is_null, math_test_t is_positive, math_test_t is_negative, math_operation_t add, math_operation_t sub, math_operation_t mult, math_operation_t div, math_print_t print) {
    math_entity_t ent = malloc(sizeof(struct math));
    alloc_check(ent);
    ent->size_element = size_element;
    ent->new = new; ent->delete = delete;
    ent->zero = zero; ent->one = one; ent->inv = inv;
    ent->is_null = is_null; ent->is_positive = is_positive; ent->is_negative = is_negative;
    ent->add = add; ent->sub = sub; ent->mult = mult; ent->div = div;
    ent->print = print;
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

void math_pow(const void *x, size_t pow, void *res) {
    res = NULL;
}

void math_print(const void *x) {
    printf("D-entity");
}
