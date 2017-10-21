#include "data/alloc.h"

// TODO Defrag!?

#ifdef DEBUG
#include <string.h>
#include <stdio.h>
#endif

static size_t get_size_used_memory(const memory_t global) {
    return global->used_global;
}

static size_t get_size_free_memory(const memory_t global) {
    return global->free_global;
}

static void* get_current_top_memory(const memory_t global) {
    return (char *)global->start_global + global->used_global;
}

static void* static_alloc(size_t size) {
    global_memory.used_global += size;
    global_memory.lost_global += size;
    global_memory.free_global -= size;
    return (char *)global_memory.start_global + global_memory.used_global - size;
}

static void static_free(void* pointer) {
    pointer = NULL;
}

void memory_get(size_t size_global) {
    global_memory.start_global = malloc(size_global);
    alloc_check(global_memory.start_global);
    global_memory.size_global = size_global;
    global_memory.free_global = size_global;
}

void memory_resize(size_t new_size_global) {
    global_memory.start_global = realloc(global_memory.start_global, new_size_global);
    alloc_check(global_memory.start_global);
    global_memory.free_global += new_size_global - global_memory.size_global;
    global_memory.size_global = new_size_global;
}

void* memory_alloc(size_t size) {
    partition_t chunk;
    chunk.start = (char *)global->start_global + global->used_global;
    chunk.end = (char *)chunk.start + size;
    global->used_global += size;
    global->free_global -= size;
    TList_Add(global->used, &chunk, static_alloc);
    return chunk.start;
}

void* memory_realloc(void* pointer, size_t size){

}

void memory_free(void* pointer) {

}
