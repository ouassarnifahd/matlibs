#include "common.h"
#include "data/liste.h"

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

static size_t get_partition_size(const partition_t *chunk) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    return (size_t)chunk->end - (size_t)chunk->start;
}

static bool partition_can_merge(partition_t chunk1, partition_t chunk2) {
    return 0;
}

static partition_t partition_merge(partition_t chunk1, partition_t chunk2) {
    return chunk1;
}

static bool partitions_equal(const void *chunk1, const void *chunk2) {
    partition_t part1 = *(const partition_t *)chunk1, part2 = *(const partition_t *)chunk2;
    return !(part1.data - part2.data);
}

static void memory_get(const memory_t global, size_t size_global) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if (size_global < MAX_MEMORY) {
        global->start_global = malloc(size_global);
        alloc_check(global->start_global);
        #ifdef DEBUG_MEMORY
        debug("Memory allocation 'void *': %zu Octets", size_global);
        #endif
        global->size_global = size_global;
        global->free_global = size_global;
    } else {
        error("Reached memory limits!");
    }
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
}

static void memory_resize(const memory_t global, size_t size_global) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if (size_global < MAX_MEMORY) {
        global->start_global = realloc(global->start_global, size_global);
        alloc_check(global->start_global);
        #ifdef DEBUG_MEMORY
        debug("Memory reallocation 'void *': %zu Octets", size_global);
        #endif
        global->free_global += size_global - global->size_global;
        global->size_global = size_global;
    } else {
        error("Reached memory limits!");
    }
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
}

static void memory_let(const memory_t global) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if (!TList_IsEmpty(global->used)) {
        warning("Memory Freed Data loss!");
    }
    free(global->start_global);
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
}

static void memory_defrag(const memory_t global) {
    return ;
}

static void* get_current_top_memory(const memory_t global) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    return (char *)global->start_global + global->used_global;
}

static void* memory_alloc(const memory_t global, size_t size) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if (!global->start_global) {
        memory_get(global, Kio);
    } else if (global->free_global < size) {
        memory_resize(global, global->size_global + Kio);
    }
    partition_t *chunk = (partition_t *)((char *)global->start_global + global->used_global);
    chunk->start = (char *)global->start_global + global->used_global;
    chunk->data = (char *)global->start_global + global->used_global + sizeof(partition_t) + sizeof(TNode);
    chunk->end = (char *)chunk->start + size + sizeof(partition_t) + sizeof(TNode);
    #ifdef DEBUG_MEMORY
    debug("Memory chunk allocated: size %zu Octets", size);
    #endif
    global->used_global += sizeof(partition_t) + sizeof(TNode);
    global->free_global -= sizeof(partition_t) + sizeof(TNode);
    PTNode newChunk = (PTNode)((char *)chunk->start + sizeof(partition_t));
    newChunk->pElement = chunk;
    newChunk->Next = NULL;
    TList_AddNode(global->used, newChunk);
    global->used_global += size;
    global->free_global -= size;
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
    return (void *)chunk->data;
}

void* Mat_alloc(size_t size) {
    return memory_alloc(&global_memory, size);
}

static void memory_free(const memory_t global, void* pointer) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    partition_t tmp = {NULL, NULL, NULL}; tmp.data = pointer;
    PTNode toFree = TList_Find(global->used, &tmp, partitions_equal);
    if(!TList_RemoveCurrentNode(global->used)) {
        error("Memory error!");
    }
    TPile_PUSHNode(global->freed, toFree);
    size_t lost = get_partition_size((const partition_t *)toFree);
    global->lost_global += lost;
    global->free_global -= lost;
    if (TList_IsEmpty(global->used)) {
        memory_let(global);
    }
    pointer = NULL;
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
}

void Mat_free(void* pointer) {
    memory_free(&global_memory, pointer);
}

static void* memory_realloc(const memory_t global, void* pointer, size_t size) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    memory_free(global, pointer);
    PTNode toRealloc = TPile_POPNode(global->freed);
    size_t allocated = get_partition_size(toRealloc->pElement);
    void* newPointer = memory_alloc(global, size);
    void* oldPointer = ((partition_t *)toRealloc->pElement)->data;
    memcpy(newPointer, oldPointer, allocated - sizeof(partition_t) - sizeof(TNode));
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
    return newPointer;
}

void* Mat_realloc(void* pointer, size_t size) {
    return memory_realloc(&global_memory, pointer, size);
}

#ifdef DEBUGED
int main(int argc, char const *argv[]) {
    init_log();
    #if defined (__x86_64__)
        debug("64-bit architecture!\n");
    #elif defined (__i386__)
        warning("32-bit architecture!\n");
    #else
        error("Incompatible architecture!");
    #endif
    memory_get(&global_memory, Kio);
    int* integer = memory_alloc(&global_memory, sizeof(int));
    *integer = 123;
    printf("%d\n", *integer);
    char* str = memory_alloc(&global_memory, 12);
    strcpy(str, "Hello World!");
    printf("%s\n", str);
    memory_free(&global_memory, integer);
    str = memory_realloc(&global_memory, str, 12);
    printf("%s\n", str);
    memory_free(&global_memory, str);
    memory_let(&global_memory);
    debug("FY!");
    return 0;
}
#endif
