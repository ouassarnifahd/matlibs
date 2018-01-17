#ifndef MLIST_H
#define MLIST_H

typedef struct memNode {
    void* data;
    size_t size;
    #ifdef DEBUG
    unsigned char id;
    #endif
    struct memNode *Next;
} *memoryNode_t;

typedef bool (*compareElem_t)(const void *, const void *);

typedef struct memList {
    size_t        NumElems;
    memoryNode_t  First;
    memoryNode_t  Last;
    memoryNode_t  Current;
    ssize_t       Index;
} *memoryList_t;

#ifdef DEBUG
unsigned char memoryNode_NewId();
#endif

size_t memoryNode_GetSize(const memoryNode_t mNode);

bool memoryList_IsEmpty(const memoryList_t mList);

size_t memoryList_Length(const memoryList_t mList);

memoryNode_t memoryList_GoTo(const memoryList_t mList, ssize_t Pos);

memoryNode_t memoryList_Find(const memoryList_t mList, const void* elt, compareElem_t compare);

ssize_t memoryList_GetIndex(const memoryList_t mList);

memoryNode_t memoryList_InsertFirstPartition(const memoryList_t mList, memoryNode_t mNode);

bool memoryList_RemoveFirstPartition(const memoryList_t mList);

memoryNode_t memoryList_AddPartition(const memoryList_t mList, memoryNode_t mNode);

bool memoryList_RemoveLastPartition(const memoryList_t mList);

memoryNode_t memoryList_InsertPartition(const memoryList_t mList, memoryNode_t mNode);

bool memoryList_RemoveCurrentPartition(const memoryList_t mList);

void memoryList_ClearPartitions(const memoryList_t mList);

#ifdef DEBUG
void memoryList_Display(const memoryList_t mList);
#endif

// Pile
typedef memoryList_t memoryPile_t;

#define memoryPile_PUSH_Partition(mpile, mNode) memoryList_AddPartition(mpile, mNode)

memoryNode_t memoryPile_POP_Partition(const memoryPile_t mpile);

#endif /* end of include guard : MLIST_H */
