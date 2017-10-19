#ifndef LISTE_H
#define LISTE_H

#include "common.h"

typedef struct Node {
    void* pElement;
    struct Node *Next;
} TNode, *PTNode;

typedef void (*deleteElem_t)(void *);

typedef void (*displayElem_t)(const void *);

typedef struct List {
    size_t  NumElems;
    size_t  SizeofElem;
    PTNode  First;
    PTNode  Last;
    PTNode  Current;
    ssize_t Index;
} TList, *PTList;

PTList TList_New(size_t sizeofElem);

bool TList_IsEmpty(const PTList list);

size_t TList_Length(const PTList list);

size_t TList_GetSizeofElem(const PTList list);

PTNode TList_GoTo(const PTList list, ssize_t Pos);

ssize_t TList_GetIndex(const PTList list);

PTNode TList_InsertFirst(const PTList list, void* pNewElt);

bool TList_RemoveFirst(const PTList list, deleteElem_t deleteElem);

PTNode TList_Add(const PTList list, void* pNewElt);

bool TList_RemoveLast(const PTList list, deleteElem_t deleteElem);

PTNode TList_Insert(const PTList list, void* pNewElt);

bool TList_RemoveCurrent(const PTList list, deleteElem_t deleteElem);

void TList_Clear(const PTList list, deleteElem_t deleteElem);

void TList_Delete(const PTList list, deleteElem_t deleteElem);

void TList_Display(const PTList list, displayElem_t display);

// Pile

typedef PTList PTPile;

#define TPile_NEW(sizeofElem) TList_New(sizeofElem)

#define TPile_PUSH(pile, pNewElt) TList_Add(pile, pNewElt)

PTNode TPile_POP(const PTPile pile, deleteElem);

#define TPile_Delete(pile, deleteElem) TList_Delete(pile, deleteElem)

#endif /* end of include guard : LISTE_H */
