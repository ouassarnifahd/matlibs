#include "libs/liste.h"

PTList TList_New(size_t sizeofElem) {
    PTList this = malloc(sizeof(TList));
    alloc_check(this);
    this->NumElems = 0;
    this->SizeofElem = sizeofElem;
    this->First = NULL;
    this->Last = NULL;
    this->Current = NULL;
    this->Index = -1;
    return this;
}

bool TList_IsEmpty(const PTList this) {
    return !this->NumElems;
}

size_t TList_Length(const PTList this) {
    return this->NumElems;
}

size_t TList_GetSizeofElem(const PTList this) {
    return this->SizeofElem;
}

ssize_t TList_GetIndex(const PTList this) {
    return this->Index;
}

PTNode TList_GoTo(const PTList this, ssize_t Pos) {
    if(TList_Length(this) <= Pos) return NULL;
    this->Current = this->First;
    this->Index = 0;
    while(this->Index < Pos){
        this->Current = this->Current->Next;
        this->Index++;
    }
    return this->Current;
}

PTNode TList_InsertFirst(const PTList this, void* pNewElt) {
    PTNode newNode = malloc(sizeof(TNode));
    alloc_check(newNode);
    void* AddNewElt = malloc(TList_GetSizeofElem(this));
    alloc_check(AddNewElt);
    memcpy(AddNewElt, pNewElt, TList_GetSizeofElem(this));
    newNode->pElement = AddNewElt;
    newNode->Next = this->First;
    if(TList_IsEmpty(this))
        this->Last = newNode;
    this->NumElems++;
    this->Index = 0;
    return newNode;
}

bool TList_RemoveFirst(const PTList this) {
    if(TList_IsEmpty(this)) return 0;
    PTNode pNode    = this->First;
    PTNode nextNode = pNode->Next;
    free(pNode->pElement);
    free(pNode);
    this->First = nextNode;
    this->NumElems--;
    this->Index = 0;
    if(TList_IsEmpty(this))
        this->Last = NULL;
    return 1;
}

PTNode TList_Add(const PTList this, void* pNewElt) {
    PTNode newNode = malloc(sizeof(TNode));
    alloc_check(newNode);
    void* AddNewElt = malloc(TList_GetSizeofElem(this));
    alloc_check(AddNewElt);
    memcpy(AddNewElt, pNewElt, TList_GetSizeofElem(this));
    newNode->pElement = AddNewElt;
    if(TList_IsEmpty(this))
        this->First = newNode;
    else
        this->Last->Next = newNode;
    this->Last = newNode;
    this->NumElems++;
    this->Index = this->NumElems - 1 ;
    return newNode;
}

bool TList_RemoveLast(const PTList this) {
    if (TList_IsEmpty(this)) return 0;
    PTNode prevNode = this->First, pNode = prevNode->Next;
    if (!pNode) {
        free(prevNode->pElement);
        free(prevNode);
        this->First = NULL;
        this->Last = NULL;
    } else {
        while (pNode->Next) {
            prevNode = pNode;
            pNode = pNode->Next;
        }
        free(pNode->pElement);
        free(pNode);
        prevNode->Next = NULL;
        this->Last = prevNode;
    }
    this->NumElems--;
    this->Index = this->NumElems - 1 ;
    return true;
}

PTNode TList_Insert(const PTList this, void* pNewElt) {
    if (!this->Current) return NULL;
    if (this->First == this->Current) {
        this->First = TList_InsertFirst(this, pNewElt);
        this->Current = this->First;
    } else {
        PTNode newNode = malloc(sizeof(TNode));
        alloc_check(newNode);
        void* AddNewElt = malloc(TList_GetSizeofElem(this));
        alloc_check(AddNewElt);
        memcpy(AddNewElt, pNewElt, TList_GetSizeofElem(this));
        newNode->pElement = AddNewElt;
        newNode->Next = this->Current;
        this->Current = TList_GoTo(this, TList_GetIndex(this) - 1);
        this->Current->Next = newNode;
        this->Current = newNode;
        this->Index++;
        this->NumElems++;
    }
    return this->Current;
}

bool TList_RemoveCurrent(const PTList this) {
    bool status = (TList_IsEmpty(this) || !this->Current);
    if (status) {
        return 0;
    } else if (this->Current == this->First) {
        status = TList_RemoveFirst(this);
        if (status) {
            this->Current = this->First;
            if (!this->Current)
                this->Index = -1;
        }
        return status;
    } else if (this->Current == this->Last) {
        status = TList_RemoveLast(this);
        if (status) {
            this->Current = this->Last;
            if (!this->Current)
                this->Index = -1;
        }
        return status;
    } else {
        PTNode pNodeToRemove = this->Current;
        TList_GoTo(this, TList_GetIndex(this) - 1);
        this->Current->Next = pNodeToRemove->Next;
        free(pNodeToRemove->pElement);
        free(pNodeToRemove);
        this->Current = this->Current->Next;
        this->Index++;
        this->NumElems--;
        return 1;
    }
}

void TList_Clear(const PTList this) {
    while(TList_RemoveLast(this));
}

void TList_Delete(const PTList this) {
    TList_Clear(this);
    free(this);
}

void TList_Display(const PTList this ,void (*display)(const void *)) {
    PTNode CurrentNode = this->First;
    size_t currentIndex = TList_GetIndex(this);
    printf("Taille de la liste : %d\n", TList_Length(this));
    printf("Contenu : ");
    while (CurrentNode) {
        display(CurrentNode->pElement);
        printf(" -> ");
        CurrentNode = CurrentNode->Next;
    }
    printf("(null)\n");
    printf("Position courante : %d\n", currentIndex);
    if (TList_GetIndex(this) != -1) {
        printf("Element courant = ");
        display(TList_GoTo(this, currentIndex)->pElement);
    }

}

// Pile

PTNode TPile_POP(const PTPile this) {
    PTNode pop = malloc(sizeof(TNode));
    alloc_check(pop);
    memcpy(pop, TList_GoTo(this, TList_Length(this) - 1), TList_GetSizeofElem(this));
    if (TList_RemoveLast(this)) {
        return pop;
    } else {
        free(pop);
        return NULL;
    }
}
