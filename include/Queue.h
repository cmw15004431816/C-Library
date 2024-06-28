// This is the definition of queue ADT in C， the queue is implemented using array
// This queue is implemented using the circular array
// Made by Morgan Willow Chen
// Last modified 6/25/2024

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

struct QueueRecord;

typedef struct QueueRecord *Queue;

typedef int ElementType; // Change the element type to what you want

struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElementType *Array;
};

void MakeEmpty(Queue Q)
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

Queue CreateQueue(int Capacity)
{
    if (Capacity <= 1)
    {
        printf("Queue capacity must be greater than 1!\n");
        return NULL;
    }
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QueueRecord));
    Q->Capacity = Capacity;
    MakeEmpty(Q);
    Q->Array = (ElementType *)malloc(sizeof(ElementType) * Capacity);
    return Q;
}

int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

int IsFull(Queue Q)
{
    return Q->Size == Q->Capacity;
}

static int Succ(int Value, Queue Q)
{
    if (++Value == Q->Capacity)
        return 0;
    return Value;
}

void Enqueue(ElementType X, Queue Q)
{
    if (IsFull(Q))
    {
        printf("Queue is full\n");
        return;
    }
    Q->Size++;
    Q->Rear = Succ(Q->Rear, Q);
    Q->Array[Q->Rear] = X;
}

void Dequeue(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("Queue is empty\n");
        return;
    }
    Q->Size--;
    Q->Front = Succ(Q->Front, Q);
}

ElementType Front(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("Queue is empty\n");
        return 0;
    }
    return Q->Array[Q->Front];
}

ElementType FrontAndDequeue(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("Queue is empty\n");
        return 0;
    }
    ElementType Tmp = Q->Array[Q->Front];
    Q->Size--;
    Q->Front = Succ(Q->Front, Q);
    return Tmp;
}

void PrintQueue(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("Queue is empty\n");
        return;
    }
    for (int i = Q->Front; i != Q->Rear; i = Succ(i, Q))
    {
        printf("%d ", Q->Array[i]);
    }
    printf("%d\n", Q->Array[Q->Rear]);
}

#endif