// This is the definition of list ADT in C, the list has a dummy node
// This list contains the following operations
// Find the length
// Print
// Make empty
// Find
// Insert
// Delete
// Find next
// Find previous
// Made by Morgan Willow Chen
// Last modified 6/24/2024

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

struct Node;

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

typedef int ElementType; // Change the element type to what you want

struct Node
{
    ElementType Element;
    Position Next;
};

List MakeEmpty(List L)
{
    L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    return L;
}

int IsEmpty(List L)
{
    return L->Next == NULL;
}

ElementType IsLast(Position P, List L) // Parameter L is unused in this function
{
    return P->Next == NULL;
}

Position Find(ElementType X, List L)
{
    Position P;
    P = L->Next;
    while (P != NULL && P->Element != X)
        P = P->Next;
    return P; // If find, return the position of X; else return NULL
}

Position FindPrevious(ElementType X, List L)
{
    Position P;
    P = L;
    while (P->Next != NULL && P->Next->Element != X)
        P = P->Next;
    return P; // If X is in the list, return the position of the previous element of X; else return the position of the last element
}

void Delete(ElementType X, List L)
{
    Position P, TmpCell;
    P = FindPrevious(X, L);
    if (!IsLast(P, L)) // X is in the list, remove it, otherwise, do nothing
    {
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
}

void Insert(ElementType X, List L, Position P)
{
    Position TmpCell;
    TmpCell = (Position)malloc(sizeof(struct Node));
    if (TmpCell == NULL)
    {
        printf("Out of space!");
        exit(1);
    }
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void DeleteList(List L)
{
    Position P, Tmp;
    P = L->Next;
    L->Next = NULL;
    while (P != NULL)
    {
        Tmp = P->Next;
        free(P);
        P = Tmp;
    }
}

#endif