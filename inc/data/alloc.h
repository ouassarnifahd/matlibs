#ifndef ALLOC_H
#define ALLOC_H

#include "liste.h"

#define Kio 1ull << 10
#define Mio 1ull << 20
#define Gio 1ull << 30

typedef struct partition {
    void* start;
    void* end;
} partition_t;

size_t get_partition_size(partition_t chunk);

bool partition_can_merge(partition_t chunk1, partition_t chunk2);

partition_t partition_merge(partition_t chunk1, partition_t chunk2);

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

void memory_get(size_t size_global);

void memory_resize(size_t new_size_global);

void* memory_alloc(size_t size);

void* memory_realloc(void* pointer, size_t size);

void memory_free(void* pointer);

#endif /* end of include guard: ALLOC_H */
