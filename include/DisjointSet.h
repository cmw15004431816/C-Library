// This is the definition of disjoint set ADT in C
// The element with index 0 is unused in the disjoint set
// The root contains the negative of the size of the set/tree
// Our Union/SetUnion takes the union-by-size strategy
// Made by Morgan Willow Chen
// Last modified 6/26/2024

#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#define NumSets 100 // Change it if you want

typedef int DisjSet[NumSets + 1];
typedef int SetType;
typedef int ElementType;
typedef int Set[NumSets + 1];

void Initialize(DisjSet S)
{
    int i;
    for (i = NumSets; i > 0; i--)
        S[i] = -1; // All sets are of size 1, so initialize -1 in the array
}
void CreateDisjSet(DisjSet) __attribute__((alias("Initialize")));
void CreateSet(DisjSet) __attribute__((alias("Initialize")));

SetType Find(ElementType X, DisjSet S)
{
    if (S[X] <= 0)
        return X;
    else
        return S[X] = Find(S[X], S);
    // Path conpression applied. If you don't want this, use the next line instead:
    // return Find(S[X], S);
    // When using union-by-height/rank, path compression should not be applied
}

/*Union arbitrarily
void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
    S[Root2] = Root1; // You can also choose to use the next line of code:
    // S[Root1] = Root2;
}
*/
void SetUnion(DisjSet S, SetType Root1, SetType Root2) // Assume Root1 and Root2 are root of the sets. \
I didn't do the check, so if not, the function will give a wrong result without any notice.\
This is the union-by-size implementation, so assume that S[Root] is the negative of the size of the set/tree.\
If not, the function will give a wrong result without any notice.
{
    if (S[Root2] < S[Root1]) // You can choose to use < or <= here
    {
        S[Root2] = S[Root1] + S[Root2];
        S[Root1] = Root2;
    }
    else
    {
        S[Root1] = S[Root1] + S[Root2];
        S[Root2] = Root1;
    }
}
/*
void SetUnion(DisjSet S, SetType Root1, SetType Root2) // Assume Root1 and Root2 are root of the sets. \
I didn't do the check, so if not, the function will give a wrong result without any notice.\
This is the union-by-height/rank implementation, so assume that S[Root] is the negative of the height of the set/tree.\
If not, the function will give a wrong result without any notice.
{
    if (S[Root2] < S[Root1])
        S[Root1] = Root2;
    else
    {
        if (S[Root2] == S[Root1])
            --S[Root1];
        S[Root2] = Root1;
    }
}
*/
void Union(DisjSet, SetType, SetType) __attribute__((alias("SetUnion")));

#endif