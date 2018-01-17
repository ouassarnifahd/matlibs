#ifndef BUILD

#include "std.h"
#include "core/data/mlist.h"

static unsigned char lastID = 0x00;

unsigned char memoryNode_NewId() {
    return ++lastID;
}

#ifdef DEBUG
static void memoryNode_Display(const memoryNode_t mNode) {
    if (mNode) {
        Mat_printf("\n  &part: %zu, id: %hhu, size: %zu",
          (size_t)mNode, mNode->id,
          mNode->size);
    }
}
#endif

size_t memoryNode_GetSize(const memoryNode_t mNode) {
    return mNode->size + sizeof(struct memNode);
}

bool memoryList_IsEmpty(const memoryList_t mList) {
    return !mList->NumElems;
}

size_t memoryList_Length(const memoryList_t mList) {
    return mList->NumElems;
}

ssize_t memoryList_GetIndex(const memoryList_t mList) {
    return mList->Index;
}

memoryNode_t memoryList_GoTo(const memoryList_t mList, ssize_t Pos) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if(memoryList_Length(mList) <= Pos) {
        #ifdef DEBUG_MEMORY
        debug("leaving function!\n");
        #endif
        return NULL;
    }
    mList->Current = mList->First;
    mList->Index = 0;
    while(mList->Index < Pos){
        mList->Current = mList->Current->Next;
        mList->Index++;
    }
    #ifdef DEBUG_MEMORY
    memoryNode_Display(mList->Current); Mat_printf("\n");
    debug("leaving function!\n");
    #endif
    return mList->Current;
}

memoryNode_t memoryList_Find(const memoryList_t mList, const void* elt, compareElem_t compare) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    mList->Current = mList->First;
    mList->Index = 0;
    while(mList->Index < memoryList_Length(mList) && !compare(mList->Current->data, elt)) {
        mList->Current = mList->Current->Next;
        mList->Index++;
    }
    #ifdef DEBUG_MEMORY
    memoryNode_Display(mList->Current); Mat_printf("\n");
    debug("leaving function!\n");
    #endif
    return mList->Current;
}

memoryNode_t memoryList_InsertFirstPartition(const memoryList_t mList, memoryNode_t mNode) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    memoryList_Display(mList);
    #endif
    mNode->Next = mList->First;
    if(memoryList_IsEmpty(mList))
        mList->Last = mNode;
    mList->First = mNode;
    mList->NumElems++;
    mList->Index = 0;
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
    return mNode;
}

bool memoryList_RemoveFirstPartition(const memoryList_t mList) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if(memoryList_IsEmpty(mList)) {
        #ifdef DEBUG_MEMORY
        debug("leaving function!\n");
        #endif
        return 0;
    }
    memoryNode_t pNode    = mList->First;
    memoryNode_t nextNode = pNode->Next;
    pNode->Next = NULL;
    mList->First = nextNode;
    mList->NumElems--;
    mList->Index = 0;
    if(memoryList_IsEmpty(mList))
        mList->Last = NULL;
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
    return 1;
}

memoryNode_t memoryList_AddPartition(const memoryList_t mList, memoryNode_t mNode) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if(memoryList_IsEmpty(mList))
        mList->First = mNode;
    else
        mList->Last->Next = mNode;
    mList->Last = mNode;
    mList->NumElems++;
    mList->Index = mList->NumElems - 1;
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
    return mNode;
}

bool memoryList_RemoveLastPartition(const memoryList_t mList) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if (memoryList_IsEmpty(mList)) {
        #ifdef DEBUG_MEMORY
        debug("leaving function!\n");
        #endif
        return false;
    }
    memoryNode_t prevNode = mList->First, pNode = prevNode->Next;
    if (!pNode) {
        prevNode->Next = NULL;
        mList->First = NULL;
        mList->Last = NULL;
    } else {
        while (pNode->Next) {
            prevNode = pNode;
            pNode = pNode->Next;
        }
        prevNode->Next = NULL;
        mList->Last = prevNode;
    }
    mList->NumElems--;
    mList->Index = mList->NumElems - 1;
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
    return true;
}

memoryNode_t memoryList_InsertPartition(const memoryList_t mList, memoryNode_t mNode) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    if (!mList->Current) {
        #ifdef DEBUG_MEMORY
        debug("leaving function!\n");
        #endif
        return NULL;
    }
    if (mList->First == mList->Current) {
        mList->Current = memoryList_InsertFirstPartition(mList, mNode);
    } else {
        mNode->Next = mList->Current;
        mList->Current = memoryList_GoTo(mList, memoryList_GetIndex(mList) - 1);
        mList->Current->Next = mNode;
        mList->Current = mNode;
        mList->Index++;
        mList->NumElems++;
    }
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
    return mList->Current;
}

bool memoryList_RemoveCurrentPartition(const memoryList_t mList) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    bool status = (memoryList_IsEmpty(mList) || !mList->Current);
    if (status) {
        #ifdef DEBUG_MEMORY
        debug("leaving function!\n");
        #endif
        return 0;
    } else if (mList->Current == mList->First) {
        status = memoryList_RemoveFirstPartition(mList);
        if (status) {
            mList->Current = mList->First;
            if (!mList->Current)
                mList->Index = -1;
        }
        #ifdef DEBUG_MEMORY
        debug("leaving function!\n");
        #endif
        return status;
    } else if (mList->Current == mList->Last) {
        status = memoryList_RemoveLastPartition(mList);
        if (status) {
            mList->Current = mList->Last;
            if (!mList->Current)
                mList->Index = -1;
        }
        #ifdef DEBUG_MEMORY
        debug("leaving function!\n");
        #endif
        return status;
    } else {
        memoryNode_t pNodeToRemove = mList->Current;
        memoryList_GoTo(mList, memoryList_GetIndex(mList) - 1);
        mList->Current->Next = pNodeToRemove->Next;
        pNodeToRemove->Next = NULL;
        mList->Current = mList->Current->Next;
        mList->Index++;
        mList->NumElems--;
        #ifdef DEBUG_MEMORY
        debug("leaving function!\n");
        #endif
        return 1;
    }
}

void memoryList_ClearPartitions(const memoryList_t mList) {
    // while (memoryList_RemoveFirstPartition(mList)) {}
    while(memoryList_RemoveLastPartition(mList)) {}
    #ifdef DEBUG_MEMORY
    debug("Inline function!\n");
    #endif
}

#ifdef DEBUG
void memoryList_Display(const memoryList_t mList) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    memoryNode_t CurrentNode = mList->First;
    Mat_printf("List length: %zu\n", memoryList_Length(mList));
    Mat_printf("Partitions: ");
    while (CurrentNode) {
        memoryNode_Display(CurrentNode);
        Mat_printf(" -> ");
        CurrentNode = CurrentNode->Next;
    }
    Mat_printf("(null)\n");
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
}
#endif

// Pile

memoryNode_t memoryPile_POP_Partition(const memoryPile_t mList) {
    #ifdef DEBUG_MEMORY
    debug("Entering function!");
    #endif
    memoryNode_t pop = memoryList_GoTo(mList, memoryList_Length(mList) - 1);
    if (!memoryList_RemoveLastPartition(mList)) {
        pop = NULL;
    }
    #ifdef DEBUG_MEMORY
    debug("leaving function!\n");
    #endif
    return pop;
}

#endif
