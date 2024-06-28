// This is the definition of prioriy queue ADT in C
// This is the definition of a min heap
// Made by Morgan Willow Chen
// Last modified 6/26/2024

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MinPQsize 1         // Change it if you want
#define MinData -2147483648 // Change it if you want

#include <stdio.h>
#include <stdlib.h>

struct HeapStruct;
typedef struct HeapStruct *PrioityQueue;
typedef struct HeapStruct *PQ;
typedef struct HeapStruct *MinHeap;
typedef struct HeapStruct *Heap;

typedef int ElementType;

struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Elements;
};

PrioityQueue Initialize(int MaxElements)
{
    PrioityQueue H;
    if (MaxElements < MinPQsize)
    {
        printf("Priority queue size is too small!\n");
        return NULL;
    }
    H = (PrioityQueue)malloc(sizeof(struct HeapStruct));
    if (H == NULL)
    {
        printf("Out of space!\n");
        return NULL;
    }
    H->Elements = (ElementType *)malloc((MaxElements + 1) * sizeof(ElementType));
    if (H->Elements == NULL)
    {
        printf("Out of space!\n");
        return NULL;
    }
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData; // This is the sentinel
    return H;
}
PrioityQueue CreatePriorityQueue(int) __attribute__((alias("Initialize")));
PrioityQueue CreatePQ(int) __attribute__((alias("Initialize")));
PrioityQueue CreateMinHeap(int) __attribute__((alias("Initialize")));
PrioityQueue CreateHeap(int) __attribute__((alias("Initialize")));

int IsFull(PrioityQueue H)
{
    return (H->Size == H->Capacity);
}

int IsEmpty(PrioityQueue H)
{
    return (H->Size == 0);
}

ElementType FindMin(PrioityQueue H)
{
    if (IsEmpty(H))
    {
        printf("Priority queue is empty!\n");
        return MinData;
    }
    return H->Elements[1];
}

void Insert(ElementType X, PrioityQueue H)
{
    int i;
    if (IsFull(H))
    {
        printf("Priority queue is full!\n");
        return;
    }
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}

ElementType DeleteMin(PrioityQueue H)
{
    int i, Child;
    ElementType MinElement, LastElement;
    if (IsEmpty(H))
    {
        printf("Priority queue is empty!\n");
        return H->Elements[0];
    }
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];
    for (i = 1; i * 2 <= H->Size; i = Child)
    {
        Child = i * 2;
        if (Child != H->Size && H->Elements[Child] > H->Elements[Child + 1])
            ++Child;
        if (LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return LastElement;
}

ElementType FindMax(PrioityQueue H) // Use the array feature to find the max element
{
    ElementType Max = H->Elements[0];
    for (int i = 1; i < H->Size; i++)
    {
        if (H->Elements[i] > Max)
            Max = H->Elements[i];
    }
    return Max;
}

int Find(ElementType X, PrioityQueue H) // Use the array feature to find the element
{
    for (int i = 0; i < H->Size; i++)
    {
        if (H->Elements[i] == X)
            return i;
    }
    return -1;
}

void Delete(ElementType X, PrioityQueue H)
{
    int i, Child;
    ElementType LastElement;
    if (IsEmpty(H))
    {
        printf("Priority queue is empty!\n");
        return;
    }
    i = Find(X, H);
    if (i == -1)
    {
        printf("Element %d is not in the priority queue!\n", X);
        return;
    }
    H->Elements[i] = MinData;
    LastElement = H->Elements[H->Size--];
    for (; i * 2 <= H->Size; i = Child)
    {
        Child = 2 * i;
        if (Child != H->Size && H->Elements[Child] > H->Elements[Child + 1])
            ++Child;
        if (LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
}

void Print(PrioityQueue H)
{
    for (int i = 1; i <= H->Size; i++)
        printf("%d ", H->Elements[i]);
    printf("\n");
}

void Distory(PrioityQueue H)
{
    free(H->Elements);
    free(H);
}
void Free(PrioityQueue) __attribute__((alias("Distory")));

#endif