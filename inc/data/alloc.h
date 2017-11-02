#ifndef ALLOC_H
#define ALLOC_H

void* Mat_alloc(size_t size);

void* Mat_realloc(void* pointer, size_t size);

void Mat_free(void* pointer);

#endif /* end of include guard: ALLOC_H */
