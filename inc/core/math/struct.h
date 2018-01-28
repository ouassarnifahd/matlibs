#ifndef STRUCT_H
#define STRUCT_H

typedef void (*method_t) (void);

typedef bool (*test_t) (void);

typedef void* (*operation_t) (const void *);

typedef void* (*math_new_t) (void);

typedef bool (*math_test_t) (const void *);

typedef void (*math_methode_t) (void *);

typedef void (*math_operation_t) (const void *, const void *, void *);

typedef void (*math_accumulator_t) (const void *, math_methode_t, math_operation_t, size_t, void *);

typedef void (*math_print_t) (const void *);

typedef struct math {
    void* element;
    size_t size_element;
    dataType_t type;
    method_t new, delete, zero, one, print;
    test_t is_null;
    operation_t add, sub, mult, div;
} *math_struct_t;

math_struct_t math_struct_new(size_t size_element);

void math_struct_delete(math_struct_t ent);

// Dummy Functions

void math_new(void);

bool math_test(const void *x);

void math_methode(void *x);

void math_operation(const void *x1, const void *x2, void *res);

void math_accumulator(const void *x, math_methode_t init, math_operation_t operation, size_t iters, void *res);

void math_print(const void *x);

#endif /* end of include guard: STRUCT_H */
