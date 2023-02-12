//
// Created by Bowin on 2023/2/11.
//

#ifndef CLANDEMO_BINARYTREE_H
#define CLANDEMO_BINARYTREE_H
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

typedef struct treeNode{
    int val;
    struct treeNode *left, *right;
} BinaryTree;

BinaryTree *createTree();

int getTreeDepth(BinaryTree *root);

void preorder_traverse(BinaryTree* root);


#endif //CLANDEMO_BINARYTREE_H
