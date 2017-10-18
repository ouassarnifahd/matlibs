#ifndef ENTITY_H
#define ENTITY_H

#include "common.h"

typedef void* (*math_new_t) (void);

typedef bool (*math_test_t) (const void *);

typedef void (*math_methode_t) (void *);

typedef void (*math_operation_t) (const void *, const void *, void *);

typedef void (*math_pow_t) (const void *, size_t, void *);

typedef void (*math_print_t) (const void *);

typedef struct math {
    size_t size_element;
    math_new_t new;
    math_methode_t delete, zero, one, inv;
    math_test_t is_null, is_positive, is_negative;
    math_operation_t add, sub, mult, div;
    math_print_t print;
} *math_entity_t;

math_entity_t entity_new(size_t size_element, math_new_t new, math_methode_t delete,
                         math_methode_t zero, math_methode_t one, math_methode_t inv,
                         math_test_t is_null, math_test_t is_positive, math_test_t is_negative,
                         math_operation_t add, math_operation_t sub, math_operation_t mult,
                         math_operation_t div, math_print_t print);

void entity_delete(math_entity_t ent);

// Dummy Functions

void* math_new(void);

bool math_test(const void *x);

void math_methode(void *x);

void math_operation(const void *x1, const void *x2, void *res);

void math_pow(const void *x, size_t pow, void *res);

void math_print(const void *x);

#endif /* end of include guard: ENTITY_H */
