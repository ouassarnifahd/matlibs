#ifndef LISTE_H
#define LISTE_H

#include "common.h"

struct Node {
    void* pElement;
    struct Node *Next;
};

typedef struct Node TNode;

typedef struct Node *PTNode;

struct List {
    size_t  NumElems;
    size_t  SizeofElem;
    PTNode  First;
    PTNode  Last;
    PTNode  Current;
    ssize_t Index;
};

typedef struct List TList;

typedef TList *PTList;

PTList TList_New(size_t sizeofElem);

bool TList_IsEmpty(const PTList this);

size_t TList_Length(const PTList this);

size_t TList_GetSizeofElem(const PTList this);

PTNode TList_GoTo(const PTList this, ssize_t Pos);

ssize_t TList_GetIndex(const PTList this);

PTNode TList_InsertFirst(const PTList this, void* pNewElt);

bool TList_RemoveFirst(const PTList this);

PTNode TList_Add(const PTList this, void* pNewElt);

bool TList_RemoveLast(const PTList this);

PTNode TList_Insert(const PTList this, void* pNewElt);

bool TList_RemoveCurrent(const PTList this);

void TList_Clear(const PTList this);

void TList_Delete(const PTList this);

void TList_Display(const PTList this, void (*display)(const void *));

// Pile

typedef PTList PTPile;

#define TPile_NEW(sizeofElem) TList_New(sizeofElem)

#define TPile_PUSH(this, pNewElt) TList_Add(this, pNewElt)

PTNode TPile_POP(const PTPile this);

#define TPile_Delete(this) TList_Delete(this)

#endif /* end of include guard : LISTE_H */
