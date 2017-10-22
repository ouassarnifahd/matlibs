#include "data/alloc.h"

static size_t get_partition_size(partition_t chunk);

static bool partition_can_merge(partition_t chunk1, partition_t chunk2);

static partition_t partition_merge(partition_t chunk1, partition_t chunk2);

static bool partitions_equal(const void *chunk1, const void *chunk2) {
    partition_t part1 = *(const partition_t *)chunk1, part2 = *(const partition_t *)chunk2;
    return !(part1.data - part2.data);
}

static size_t get_size_used_memory(const memory_t global) {
    return global->used_global;
}

static size_t get_size_free_memory(const memory_t global) {
    return global->free_global;
}

static void* get_current_top_memory(const memory_t global) {
    return (char *)global->start_global + global->used_global;
}

static void* static_alloc(size_t size) { // Danger!
    global_memory.used_global += size;
    global_memory.free_global -= size;
    return (char *)global_memory.start_global + global_memory.used_global - size;
}

static void static_free(void* pointer) {
    pointer = NULL;
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

void memory_resize(const memory_t global, size_t new_size_global) {
    if (size_global < MAX_MEMORY) {
        global->start_global = realloc(global->start_global, new_size_global);
        alloc_check(global->start_global);
        global->free_global += new_size_global - global->size_global;
        global->size_global = new_size_global;
    } else {
        error("Reached memory limits!");
    }
}

static void memory_defrag(const memory_t global);

void* memory_alloc(const memory_t global, size_t size) {
    if (global->free_global < size) {
        memory_resize(global->size_global + 3 * size);
    }
    partition_t chunk;
    chunk.start = (char *)global->start_global + global->used_global;
    chunk.data = (char *)global->start_global + global->used_global + sizeof(chunk);
    chunk.end = (char *)chunk.start + size + sizeof(chunk);
    TList_Add(global->used, &chunk, static_alloc);
    global->used_global += size;
    global->free_global -= size;
    return chunk.data;
}

void* memory_realloc(const memory_t global, void* pointer, size_t size) {

}

void memory_free(const memory_t global, void* pointer) {
    PTNode toFree = TList_Find();
}

#ifdef DEBUG
int main(int argc, char const *argv[]) {

    return 0;
}
#endif
