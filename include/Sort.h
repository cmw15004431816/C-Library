// This is the implementation of several sort functions
// All these functions will sort the elements in ascending order
// Made by Morgan Willow Chen
// Last modified 6/27/2024

#ifndef SORT_H
#define SORT_H

#include <stdlib.h>

typedef int ElementType;

void InsertionSort(ElementType A[], int N)
{
    int j, P;
    ElementType Tmp;
    for (P = 1; P < N; P++)
    {
        Tmp = A[P];
        for (j = P; j > 0 && A[j - 1] > Tmp; j--)
        {
            A[j] = A[j - 1];
        }
        A[j] = Tmp;
    }
}

void ShellSort(ElementType A[], int N) // Shellsort with Shell's increments
{
    int i, j, Increment;
    ElementType Tmp;
    for (Increment = N / 2; Increment > 0; Increment /= 2)
    {
        for (i = Increment; i < N; i++)
        {
            Tmp = A[i];
            for (j = i; j >= Increment; j -= Increment)
            {
                if (Tmp < A[j - Increment])
                    A[j] = A[j - Increment];
                else
                    break;
            }
            A[j] = Tmp;
        }
    }
}

static void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
    int i, LeftEnd, NumElements, TmpPos;
    LeftEnd = Rpos - 1;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;
    while (Lpos <= LeftEnd && Rpos <= RightEnd)
        if (A[Lpos] <= A[Rpos])
            TmpArray[TmpPos++] = A[Lpos++];
        else
            TmpArray[TmpPos++] = A[Rpos++];
    while (Lpos <= LeftEnd)
        TmpArray[TmpPos++] = A[Lpos++];
    while (Rpos <= RightEnd)
        TmpArray[TmpPos++] = A[Rpos++];
    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TmpArray[RightEnd];
}

static void MSort(ElementType A[], ElementType TmpArray[], int Left, int Right)
{
    int Center;
    if (Left < Right)
    {
        Center = (Left + Right) / 2;
        MSort(A, TmpArray, Left, Center);
        MSort(A, TmpArray, Center + 1, Right);
        Merge(A, TmpArray, Left, Center + 1, Right);
    }
}

void MergeSort(ElementType A[], int N)
{
    ElementType *TmpArray;
    TmpArray = (ElementType *)malloc(N * sizeof(ElementType));
    if (TmpArray != NULL)
    {
        MSort(A, TmpArray, 0, N - 1);
        free(TmpArray);
    }
}

#define Cutoff (10) // When the sequence is too short, use insertion sort for efficiency. You can change this value

static void Swap(ElementType *A, ElementType *B)
{
    ElementType Tmp;
    Tmp = *A;
    *A = *B;
    *B = Tmp;
}

static ElementType Median3(ElementType A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;
    if (A[Left] > A[Center])
        Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right])
        Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center], &A[Right]);
    Swap(&A[Center], &A[Right - 1]); // A[Right] must be greater than A[Center](pivot), so we don't need to deal with A[Right] later
    return A[Right - 1];             // Hide pivot at A[Right - 1], instead of A[Right]
}

void QSort(ElementType A[], int Left, int Right)
{
    int i, j;
    ElementType Pivot;
    if (Left + Pivot <= Right)
    {
        Pivot = Median3(A, Left, Right);
        i = Left;
        j = Right - 1; // After calling Median3, we don't need to deal with A[Right]
        for (;;)
        {
            while (A[++i] < Pivot)
                ;
            while (A[--j] > Pivot)
                ;
            if (i < j)
                Swap(&A[i], &A[j]);
            else
                break;
        }
        Swap(&A[i], &A[Right - 1]); // Restore the pivot
        QSort(A, Left, i - 1);      // Pivot(A[i]) has been on the right place, so we don't need to deal with it anymore
        QSort(A, i + i, Right);     // This time, don't forget to deal with the A[Right]
    }
    else
    {
        InsertionSort(A + Left, Right - Left + 1);
    }
}

void QuickSort(ElementType A[], int N)
{
    QSort(A, 0, N - 1);
}

#undef Cutoff

#endif