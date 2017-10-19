#include "data/liste.h"

PTList TList_New(size_t sizeofElem) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    PTList this = malloc(sizeof(TList));
    alloc_check(this);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'PTList': %zu Octets", sizeof(TList));
    #endif
    this->NumElems = 0;
    this->SizeofElem = sizeofElem;
    this->First = NULL;
    this->Last = NULL;
    this->Current = NULL;
    this->Index = -1;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return this;
}

bool TList_IsEmpty(const PTList this) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    return !this->NumElems;
}

size_t TList_Length(const PTList this) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    return this->NumElems;
}

size_t TList_GetSizeofElem(const PTList this) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    return this->SizeofElem;
}

ssize_t TList_GetIndex(const PTList this) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    return this->Index;
}

PTNode TList_GoTo(const PTList this, ssize_t Pos) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if(TList_Length(this) <= Pos) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return NULL;
    }
    this->Current = this->First;
    this->Index = 0;
    while(this->Index < Pos){
        this->Current = this->Current->Next;
        this->Index++;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return this->Current;
}

PTNode TList_InsertFirst(const PTList this, void* pNewElt) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    PTNode newNode = malloc(sizeof(TNode));
    alloc_check(newNode);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'TNode': %zu Octets", sizeof(TNode));
    #endif
    void* AddNewElt = malloc(TList_GetSizeofElem(this));
    alloc_check(AddNewElt);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'void*': %zu Octets", TList_GetSizeofElem(this));
    #endif
    memcpy(AddNewElt, pNewElt, TList_GetSizeofElem(this));
    newNode->pElement = AddNewElt;
    newNode->Next = this->First;
    if(TList_IsEmpty(this))
        this->Last = newNode;
    this->NumElems++;
    this->Index = 0;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return newNode;
}

bool TList_RemoveFirst(const PTList this, deleteElem_t deleteElem) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if(TList_IsEmpty(this)) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return 0;
    }
    PTNode pNode    = this->First;
    PTNode nextNode = pNode->Next;
    deleteElem(pNode->pElement);
    free(pNode);
    #ifdef DEBUG_FREE
    debug("Memory freed (PTNode)");
    #endif
    this->First = nextNode;
    this->NumElems--;
    this->Index = 0;
    if(TList_IsEmpty(this))
        this->Last = NULL;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return 1;
}

PTNode TList_Add(const PTList this, void* pNewElt) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    PTNode newNode = malloc(sizeof(TNode));
    alloc_check(newNode);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'TNode': %zu Octets", sizeof(TNode));
    #endif
    void* AddNewElt = malloc(TList_GetSizeofElem(this));
    alloc_check(AddNewElt);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'void*': %zu Octets", TList_GetSizeofElem(this));
    #endif
    memcpy(AddNewElt, pNewElt, TList_GetSizeofElem(this));
    newNode->pElement = AddNewElt;
    if(TList_IsEmpty(this))
        this->First = newNode;
    else
        this->Last->Next = newNode;
    this->Last = newNode;
    this->NumElems++;
    this->Index = this->NumElems - 1;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return newNode;
}

bool TList_RemoveLast(const PTList this, deleteElem_t deleteElem) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (TList_IsEmpty(this)) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return 0;
    }
    PTNode prevNode = this->First, pNode = prevNode->Next;
    if (!pNode) {
        deleteElem(prevNode->pElement);
        free(prevNode);
        #ifdef DEBUG_FREE
        debug("Memory freed (PTNode)");
        #endif
        this->First = NULL;
        this->Last = NULL;
    } else {
        while (pNode->Next) {
            prevNode = pNode;
            pNode = pNode->Next;
        }
        deleteElem(pNode->pElement);
        free(pNode);
        #ifdef DEBUG_FREE
        debug("Memory freed (PTNode)");
        #endif
        prevNode->Next = NULL;
        this->Last = prevNode;
    }
    this->NumElems--;
    this->Index = this->NumElems - 1;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return true;
}

PTNode TList_Insert(const PTList this, void* pNewElt) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (!this->Current) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return NULL;
    }
    if (this->First == this->Current) {
        this->First = TList_InsertFirst(this, pNewElt);
        this->Current = this->First;
    } else {
        PTNode newNode = malloc(sizeof(TNode));
        alloc_check(newNode);
        #ifdef DEBUG_MALLOC
        debug("Memory allocation 'TNode': %zu Octets", sizeof(TNode));
        #endif
        void* AddNewElt = malloc(TList_GetSizeofElem(this));
        alloc_check(AddNewElt);
        #ifdef DEBUG_MALLOC
        debug("Memory allocation 'void*': %zu Octets", TList_GetSizeofElem(this));
        #endif
        memcpy(AddNewElt, pNewElt, TList_GetSizeofElem(this));
        newNode->pElement = AddNewElt;
        newNode->Next = this->Current;
        this->Current = TList_GoTo(this, TList_GetIndex(this) - 1);
        this->Current->Next = newNode;
        this->Current = newNode;
        this->Index++;
        this->NumElems++;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return this->Current;
}

bool TList_RemoveCurrent(const PTList this, deleteElem_t deleteElem) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    bool status = (TList_IsEmpty(this) || !this->Current);
    if (status) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return 0;
    } else if (this->Current == this->First) {
        status = TList_RemoveFirst(this, deleteElem);
        if (status) {
            this->Current = this->First;
            if (!this->Current)
                this->Index = -1;
        }
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return status;
    } else if (this->Current == this->Last) {
        status = TList_RemoveLast(this, deleteElem);
        if (status) {
            this->Current = this->Last;
            if (!this->Current)
                this->Index = -1;
        }
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return status;
    } else {
        PTNode pNodeToRemove = this->Current;
        TList_GoTo(this, TList_GetIndex(this) - 1);
        this->Current->Next = pNodeToRemove->Next;
        deleteElem(pNodeToRemove->pElement);
        free(pNodeToRemove);
        #ifdef DEBUG_FREE
        debug("Memory freed (PTNode)");
        #endif
        this->Current = this->Current->Next;
        this->Index++;
        this->NumElems--;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return 1;
    }
}

void TList_Clear(const PTList this, deleteElem_t deleteElem) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    while(TList_RemoveLast(this, deleteElem));
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void TList_Delete(const PTList this, deleteElem_t deleteElem) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    TList_Clear(this, deleteElem);
    free(this);
    #ifdef DEBUG_FREE
    debug("Memory freed (PTList)");
    #endif
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void TList_Display(const PTList this, displayElem_t display) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    PTNode CurrentNode = this->First;
    size_t currentIndex = TList_GetIndex(this);
    printf("Taille de la liste : %zu\n", TList_Length(this));
    printf("Contenu : ");
    while (CurrentNode) {
        display(CurrentNode->pElement);
        printf(" -> ");
        CurrentNode = CurrentNode->Next;
    }
    printf("(null)\n");
    printf("Position courante : %zu\n", currentIndex);
    if (TList_GetIndex(this) != -1) {
        printf("Element courant = ");
        display(TList_GoTo(this, currentIndex)->pElement);
        printf("\n");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

// Pile

PTNode TPile_POP(const PTPile this, deleteElem_t deleteElem) {
    PTNode pop = malloc(sizeof(TNode));
    alloc_check(pop);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'TNode': %zu Octets", sizeof(TNode));
    #endif
    memcpy(pop, TList_GoTo(this, TList_Length(this) - 1), TList_GetSizeofElem(this));
    if (TList_RemoveLast(this, deleteElem)) {
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return pop;
    } else {
        free(pop);
        #ifdef DEBUG_FREE
        debug("Memory freed (PTNode)");
        #endif
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        return NULL;
    }
}
