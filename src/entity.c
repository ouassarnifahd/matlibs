#include "entity.h"

math_entity_t entity_new(size_t size_element, math_new_t new, math_methode_t del, math_methode_t zero, math_methode_t one, math_methode_t inv, math_test_t is_null, math_test_t is_positive, math_test_t is_negative, math_operation_t add, math_operation_t sub, math_operation_t mult, math_operation_t div, math_print_t print) {
    math_entity_t ent = malloc(sizeof(struct math));
    ent->size_element = size_element;
    ent->new = new; ent->del = del;
    ent->zero = zero; ent->one = one; ent->inv = inv;
    ent->is_null = is_null; ent->is_positive = is_positive; ent->is_negative = is_negative;
    ent->add = add; ent->sub = sub; ent->mult = mult; ent->div = div;
    ent->print = print;
    return ent;
}

void entity_delete(math_entity_t ent) {
    if (ent) free(ent);
}
