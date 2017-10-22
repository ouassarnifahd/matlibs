#ifndef ALLOC_H
#define ALLOC_H

#include "liste.h"

#define Kio (1ull << 10)
#define Mio (1ull << 20)
#define Gio (1ull << 30)

#define MAX_MEMORY 10 * Mio

typedef struct partition {
    void* start;
    void* data;
    void* end;
} partition_t;

static struct List alloc_segment = {
    0, sizeof(struct partition),
    NULL, NULL, NULL, -1
};

static struct List free_segment = {
    0, sizeof(struct partition),
    NULL, NULL, NULL, -1
};

typedef struct memory {
    void* start_global;
    size_t size_global;
    size_t used_global;
    size_t free_global;
    size_t lost_global;
    PTList used;
    PTPile freed;
} *memory_t;

static struct memory global_memory = {
    NULL, 0, 0, 0, 0, &alloc_segment, &free_segment
};

void memory_get(const memory_t global, size_t size_global);

void memory_resize(const memory_t global, size_t new_size_global);

void* memory_alloc(const memory_t global, size_t size);

void* memory_realloc(const memory_t global, void* pointer, size_t size);

void memory_free(const memory_t global, void* pointer);

#endif /* end of include guard: ALLOC_H */
