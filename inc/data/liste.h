#ifndef LISTE_H
#define LISTE_H

#include "common.h"

typedef struct Node {
    void* pElement;
    struct Node *Next;
} TNode, *PTNode;

PTNode TNode_New(alloc_t mem_alloc, void* pNewElt);

typedef void (*deleteElem_t)(void *);

typedef void (*displayElem_t)(const void *);

typedef bool (*compareElem_t)(const void *, const void *);

typedef void* (*alloc_t)(size_t);

typedef void (*free_t)(void *);

typedef struct List {
    size_t  NumElems;
    size_t  SizeofElem;
    PTNode  First;
    PTNode  Last;
    PTNode  Current;
    ssize_t Index;
} TList, *PTList;

PTList TList_New(alloc_t mem_alloc, size_t sizeofElem);

bool TList_IsEmpty(const PTList list);

size_t TList_Length(const PTList list);

size_t TList_GetSizeofElem(const PTList list);

PTNode TList_GoTo(const PTList list, ssize_t Pos);

PTNode TList_Find(const PTList list, const void* elt, compareElem_t equal);

ssize_t TList_GetIndex(const PTList list);

PTNode TList_InsertFirst(const PTList list, void* pNewElt, alloc_t mem_alloc);

bool TList_RemoveFirst(const PTList list, deleteElem_t deleteElem, free_t mem_free);

PTNode TList_Add(const PTList list, void* pNewElt, alloc_t mem_alloc);

PTNode TList_AddNode(const PTList list, PTNode newNode);

bool TList_RemoveLast(const PTList list, deleteElem_t deleteElem, free_t mem_free);

PTNode TList_Insert(const PTList list, void* pNewElt, alloc_t mem_alloc);

PTNode TList_InsertNode(const PTList list, PTNode newNode);

bool TList_RemoveCurrent(const PTList list, deleteElem_t deleteElem, free_t mem_free);

void TList_Clear(const PTList list, deleteElem_t deleteElem, free_t mem_free);

void TList_Delete(const PTList list, deleteElem_t deleteElem, free_t mem_free);

void TList_Display(const PTList list, displayElem_t display);

// Pile

typedef PTList PTPile;

#define TPile_NEW(sizeofElem) TList_New(sizeofElem)

#define TPile_PUSH(pile, pNewElt, mem_alloc) TList_Add(pile, pNewElt, mem_alloc)

PTNode TPile_POP(const PTPile pile, deleteElem_t deleteElem, free_t mem_free);

#define TPile_Delete(pile, deleteElem, mem_free) TList_Delete(pile, deleteElem, mem_free)

#endif /* end of include guard : LISTE_H */
