#ifndef ALLOC_H
#define ALLOC_H

#define Kio (1ull << 10)
#define Mio (1ull << 20)
#define Gio (1ull << 30)

#define PAGE_SIZE 4 * Kio

#define MAX_MEMORY 8 * PAGE_SIZE

typedef void* (*alloc_t)(size_t);
typedef void (*free_t)(void *);

void* Mat_alloc(size_t size);

void* Mat_realloc(void* pointer, size_t size);

void Mat_free(void* pointer);

#ifdef DEBUG
void memory_Debug();
#endif

#endif /* end of include guard: ALLOC_H */
