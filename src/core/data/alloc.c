#include "std.h"

#ifndef BUILD

#include "core/data/mlist.h"
#include "core/data/alloc.h"

static struct memList alloc_segment = { 0, NULL, NULL, NULL, -1 };

static struct memList free_segment = { 0, NULL, NULL, NULL, -1 };

typedef struct memory {
    void* start_global;
    size_t size_global;
    size_t used_global;
    size_t free_global;
    size_t lost_global;
    memoryList_t used;
    memoryPile_t freed;
} *memory_t;

static struct memory global_memory = {
    NULL, 0, 0, 0, 0, &alloc_segment, &free_segment
};

#ifdef DEBUG
static void memory_Display(const memory_t global) {
    debug("MEMORY STATE!");
    if (global->start_global) {
        debug("Start MEMORY: %zu", (size_t)global->start_global);
        debug("Size  MEMORY: %zu Octets", global->size_global);
        debug("used  MEMORY: %zu Octets", global->used_global);
        debug("free  MEMORY: %zu Octets", global->free_global);
        debug("lost  MEMORY: %zu Octets", global->lost_global);
        debug("USED Partitions:");
        if (global->used) {
            memoryList_Display(global->used);
        } else {
            debug("MemoryList is Empty!");
        }
        debug("FREED Partitions:");
        if (global->freed) {
            memoryList_Display(global->freed);
        } else {
            debug("MemoryList is Empty!");
        }
    } else {
        debug("Memory was freed!");
    }
}

void memory_Debug() {
    memory_Display(&global_memory);
}
#endif

static bool partitions_equal(const void *data1, const void *data2) {
    return !(data1 - data2);
}

static void memory_get(const memory_t global, size_t size_global) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if (size_global < MAX_MEMORY) {
        #ifdef DEBUG_MEMORY
        debug("SYSCALL malloc: %zu Octets", size_global);
        #endif
        global->start_global = malloc(size_global);
        alloc_check(global->start_global);
        #ifdef DEBUG_MEMORY
        debug("Memory allocated Successfully: %zu Octets", size_global);
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
        #ifdef DEBUG_MEMORY
        debug("SYSCALL realloc: %zu Octets", size_global);
        #endif
        global->start_global = realloc(global->start_global, size_global);
        alloc_check(global->start_global);
        #ifdef DEBUG_MEMORY
        debug("Memory reallocation Successed: %zu Octets", size_global);
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
    free(global->start_global);
    global->start_global = NULL;
    global->size_global = 0;
    global->used_global = 0;
    global->free_global = 0;
    global->lost_global = 0;
    // memoryList_ClearPartitions(global->freed); // Fuck!
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
}

static void* memory_GetTop(const memory_t global) {
    #ifdef DEBUG_MEMORY
    debug("Inline function!\n");
    #endif
    return (char *)global->start_global + global->used_global;
}

static void* memory_alloc(const memory_t global, size_t size) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if (!global->start_global) {
        memory_get(global, PAGE_SIZE);
    } else if (global->free_global < size) {
        memory_resize(global, global->size_global + PAGE_SIZE);
    }
    memoryNode_t chunk = (memoryNode_t)memory_GetTop(global);
    chunk->data = memory_GetTop(global) + sizeof(struct memNode);
    chunk->size = size;
    #ifndef BUILD
    chunk->id = memoryNode_NewId();
    #endif
    chunk->Next = NULL;
    #ifdef DEBUG_MEMORY
    debug("Memory chunk allocated: size %zu Octets", size);
    #endif
    global->used_global += memoryNode_GetSize(chunk);
    global->free_global -= memoryNode_GetSize(chunk);
    memoryList_AddPartition(global->used, chunk);
    #ifdef DEBUG_MEMORY
    memory_Display(global);
    debug("leaving function!\n");
    #endif
    return chunk->data;
}

static void memory_free(const memory_t global, void* pointer) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    memoryNode_t toFree = memoryList_Find(global->used, pointer, partitions_equal);
    if(!memoryList_RemoveCurrentPartition(global->used)) {
        error("Memory error!");
    }
    memoryPile_PUSH_Partition(global->freed, toFree);
    #ifdef DEBUG_MEMORY
    memoryList_Display(global->freed);
    #endif
    size_t lost = memoryNode_GetSize(toFree);
    #ifdef DEBUG_MEMORY
    debug("lost memory: %zu", lost);
    #endif
    global->used_global -= lost;
    global->lost_global += lost;
    if (memoryList_IsEmpty(global->used)) {
        memory_let(global);
    }
    pointer = NULL;
    #ifdef DEBUG_MEMORY
    memory_Display(global);
    debug("leaving function!\n");
    #endif
}

static void* memory_realloc(const memory_t global, void* pointer, size_t size) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    void* newPointer = NULL;
    memoryNode_t toFree = memoryList_Find(global->used, pointer, partitions_equal);
    if (toFree->size > size) {
        newPointer = pointer;
        global->lost_global += memoryNode_GetSize(toFree) - size;
        toFree->size = size;
    } else if (toFree->size == size) {
        newPointer = pointer;
    } else {
        memory_free(global, pointer);
        memoryNode_t toRealloc = memoryPile_POP_Partition(global->freed);
        void* newPointer = memory_alloc(global, size);
        void* oldPointer = toRealloc->data;
        memcpy(newPointer, oldPointer, toRealloc->size);
    }
    #ifdef DEBUG_MEMORY
    memory_Display(global);
    debug("leaving function!\n");
    #endif
    return newPointer;
}

#endif

void* Mat_alloc(size_t size) {
    #ifndef BUILD
    return memory_alloc(&global_memory, size);
    #else
    return malloc(size);
    #endif
}

void Mat_free(void* pointer) {
    #ifndef BUILD
    memory_free(&global_memory, pointer);
    #else
    free(pointer);
    #endif
}

void* Mat_realloc(void* pointer, size_t size) {
    #ifndef BUILD
    return memory_realloc(&global_memory, pointer, size);
    #else
    return realloc(pointer, size);
    #endif
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
    int* integer = Mat_alloc(sizeof(int));
    *integer = 123;
    printf("%d\n", *integer);
    char* str = Mat_alloc(sizeof(char) * 12);
    strcpy(str, "Hello World!");
    printf("%s\n", str);
    Mat_free(integer);
    // str = Mat_realloc(str, 14); // Pffff!!
    printf("%s\n", str);
    Mat_free(str);
    debug("FY!");
    return 0;
}
#endif
