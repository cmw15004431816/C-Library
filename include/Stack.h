// This is the definition of stack ADT in C， the stack is implemented using list with a dummy node
// Made by Morgan Willow Chen
// Last modified 6/24/2024

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

struct Node;

typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

typedef int ElementType; // Change the element type to what you want

struct Node
{
    ElementType Element;
    PtrToNode Next;
};

int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

void Pop(Stack S)
{
    PtrToNode FirstCell;
    if (IsEmpty(S))
    {
        printf("Empty stack\n");
        return;
    }
    else
    {
        FirstCell = S->Next;
        S->Next = FirstCell->Next;
        free(FirstCell);
    }
}

void MakeEmpty(Stack S)
{
    if (S == NULL)
    {
        printf("Please create a stack before making it empty!\n");
        return;
    }
    else
        while (!IsEmpty(S))
            Pop(S);
}

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct Node));
    if (S == NULL)
    {
        printf("Out of space!");
        exit(1);
    }
    S->Next = NULL;
    MakeEmpty(S);
    return S;
}

void Push(ElementType X, Stack S)
{
    PtrToNode TmpCell;
    TmpCell = (PtrToNode)malloc(sizeof(struct Node));
    if (TmpCell == NULL)
    {
        printf("Out of space!");
        exit(1);
    }
    else
    {
        TmpCell->Element = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
    }
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Next->Element;
    printf("Empty stack!\n");
    return 0;
}

#endif