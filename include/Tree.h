// This is the definition of binary search tree ADT in C
// We assume that all keys in the tree are different
// Made by Morgan Willow Chen
// Last modified 6/25/2024

#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

struct TreeNode;

typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef struct TreeNode *BST;
typedef struct TreeNode *Tree;

typedef int ElementType; // Change the element type to what you want

struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, SearchTree T)
{
    if (T == NULL)
        return NULL; // Not found
    if (X < T->Element)
        return Find(X, T->Left);
    else if (X > T->Element)
        return Find(X, T->Right);
    else
        return T;
}

/*A iteritive version instead
Position Find(ElementType X, SearchTree T)
{
    Position P = T;
    if (T == NULL)
        return NULL;
    while (P != NULL && P->Element != X)
    {
        if (X < P->Element)
            P = P->Left;
        else if(X > P->Element)
            P = P->Right;
    }
    return P;
}
*/

Position FindMin(SearchTree T)
{
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

/*A iteritive version instead
Position FindMin(SearchTree T)
{
    if (T != NULL)
        while (T->Left != NULL)
            T = T->Left;
    return T;
}
*/

Position FindMax(SearchTree T)
{
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;
    return T;
}

/*A recursive version instead
Position FindMax(SearchTree T)
{
    if (T == NULL)
        return NULL;
    else if (T->Right == NULL)
        return T;
    else
        return FindMax(T->Right);
}
*/

SearchTree CreateSearchTree(ElementType Element) // When creating a search tree, you must provide the first element
{
    SearchTree T = (SearchTree)malloc(sizeof(struct TreeNode));
    if (T == NULL)
    {
        printf("Out of space!\n");
        exit(1);
    }
    else
    {
        T->Element = Element;
        T->Left = T->Right = NULL;
    }
    return T;
}
SearchTree CreateBST(ElementType) __attribute__((alias("CreateSearchTree")));

SearchTree Insert(ElementType X, SearchTree T)
{
    // If the element is already in the tree, then do nothing and return. You can choose whether to include the check in the function or not.
    /*
    if (Find(X, T) == NULL)
        return T;
    */
    if (T == NULL)
    {
        T = (SearchTree)malloc(sizeof(struct TreeNode));
        if (T == NULL)
        {
            printf("Out of space!\n");
            exit(1);
        }
        else
        {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    }
    else if (X < T->Element)
        T->Left = Insert(X, T->Left);
    else if (X > T->Element)
        T->Right = Insert(X, T->Right);
    // If the element is already in the tree, then do nothing
    return T;
}

SearchTree Delete(ElementType X, SearchTree T) // An implementation by adjusting the right subtree
{
    Position TmpCell;
    if (T == NULL)
    {
        printf("Element not found!\n");
        return T;
    }
    else if (X < T->Element)
        T->Left = Delete(X, T->Left);
    else if (X > T->Element)
        T->Right = Delete(X, T->Right);
    else if (T->Left && T->Right)
    {
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    }
    else
    {
        TmpCell = T;
        if (T->Left == NULL)
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(TmpCell);
    }
    return T;
}

/*
SearchTree Delete(ElementType X, SearchTree T) // An implementation by adjusting the left subtree
{
    Position TmpCell;
    if (T == NULL)
    {
        printf("Element not found!\n");
        return T;
    }
    else if (X < T->Element)
        T->Left = Delete(X, T->Left);
    else if (X > T->Element)
        T->Right = Delete(X, T->Right);
    else if (T->Left && T->Right)
    {
        TmpCell = FindMax(T->Left);
        T->Element = TmpCell->Element;
        T->Left = Delete(T->Element, T->Left);
    }
    else
    {
        TmpCell = T;
        if (T->Left == NULL)
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(TmpCell);
    }
    return T;
}
*/

void PrintTree(SearchTree T) // You need to manually add a new line after calling this function if you want
{
    if (T != NULL)
    {
        PrintTree(T->Left);
        printf("%d ", T->Element);
        PrintTree(T->Right);
    }
}
void Inorder(SearchTree) __attribute__((alias("PrintTree")));

void Preorder(SearchTree T) // You need to manually add a new line after calling this function if you want
{
    if (T != NULL)
    {
        printf("%d ", T->Element);
        Preorder(T->Left);
        Preorder(T->Right);
    }
}

void Postorder(SearchTree T) // You need to manually add a new line after calling this function if you want
{
    if (T != NULL)
    {
        Postorder(T->Left);
        Postorder(T->Right);
        printf("%d ", T->Element);
    }
}

void iter_Inorder(SearchTree T) // You need to manually add a new line after calling this function if you want
{
    Tree stack[100]; // Make sure that the stack is big enough, you can change the size of the stack
    stack[0] = NULL;
    int i = 1;
    for (;;)
    {
        for (; T; T = T->Left)
            stack[i++] = T;
        T = stack[--i];
        if (!T)
            break;
        printf("%d ", T->Element);
        T = T->Right;
    }
}

void iter_Preorder(SearchTree T) // You need to manually add a new line after calling this function if you want
{
    Tree stack[100]; // Make sure that the stack is big enough, you can change the size of the stack
    stack[0] = NULL;
    int i = 1;
    for (;;)
    {
        for (; T; T = T->Left)
        {
            stack[i++] = T;
            printf("%d ", T->Element);
        }
        T = stack[--i];
        if (!T)
            break;
        T = T->Right;
    }
}

// void iter_Postorder(SearchTree T) // Hard to implement, ommited here
#endif