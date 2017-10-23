#include "data/alloc.h"

static size_t get_partition_size(const partition_t *chunk) {
    return (size_t)chunk->end - (size_t)chunk->start;
}

static bool partition_can_merge(partition_t chunk1, partition_t chunk2);

static partition_t partition_merge(partition_t chunk1, partition_t chunk2);

static bool partitions_equal(const void *chunk1, const void *chunk2) {
    partition_t part1 = *(const partition_t *)chunk1, part2 = *(const partition_t *)chunk2;
    return !(part1.data - part2.data);
}

void memory_get(const memory_t global, size_t size_global) {
    if (size_global < MAX_MEMORY) {
        global->start_global = malloc(size_global);
        alloc_check(global->start_global);
        global->size_global = size_global;
        global->free_global = size_global;
    } else {
        error("Reached memory limits!");
    }
}

void memory_resize(const memory_t global, size_t size_global) {
    if (size_global < MAX_MEMORY) {
        global->start_global = realloc(global->start_global, size_global);
        alloc_check(global->start_global);
        global->free_global += size_global - global->size_global;
        global->size_global = size_global;
    } else {
        error("Reached memory limits!");
    }
}

void memory_let(const memory_t global) {
    if (global->used_global > 0) {
        warning("Memory Freed Data loss!");
    }
    free(global->start_global);
}

static void memory_defrag(const memory_t global);

static void* get_current_top_memory(const memory_t global) {
    return (char *)global->start_global + global->used_global;
}

void* memory_alloc(const memory_t global, size_t size) {
    if (global->free_global < size) {
        memory_resize(global, global->size_global + 3 * size);
    }
    partition_t *chunk = (partition_t *)((char *)global->start_global + global->used_global);
    chunk->start = (char *)global->start_global + global->used_global;
    chunk->data = (char *)global->start_global + global->used_global + sizeof(partition_t) + sizeof(TNode);
    chunk->end = (char *)chunk->start + size + sizeof(partition_t) + sizeof(TNode);
    global->used_global += sizeof(partition_t) + sizeof(TNode);
    global->free_global -= sizeof(partition_t) + sizeof(TNode);
    PTNode newChunk = (PTNode)((char *)chunk->start + sizeof(partition_t));
    newChunk->pElement = chunk;
    newChunk->Next = NULL;
    TList_AddNode(global->used, newChunk);
    global->used_global += size;
    global->free_global -= size;
    return chunk->data;
}

void* memory_realloc(const memory_t global, void* pointer, size_t size) {

}

void memory_free(const memory_t global, void* pointer) {
    partition_t tmp = {NULL, NULL, NULL}; tmp.data = pointer;
    PTNode toFree = TList_Find(global->used, &tmp, partitions_equal);
    TPile_PUSH(global->freed, toFree);
    size_t lost = get_partition_size(toFree);
    global->lost_global += lost;
    global->free_global -= lost;
}

#ifdef DEBUG
int main(int argc, char const *argv[]) {
    memory_get(&global_memory, Kio);
    int* integer = memory_alloc(&global_memory, sizeof(int));
    char* str = memory_alloc(&global_memory, 12);
    strcpy(str, "Hello World!");
    *integer = 123;
    printf("%d\n", *integer);
    printf("%s\n", str);
    memory_let(&global_memory);
    return 0;
}
#endif
