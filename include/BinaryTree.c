//
// Created by Bowin on 2023/2/11.
//
#include "BinaryTree.h"

BinaryTree *createTree() {
    int c;
    BinaryTree *root = NULL;
    scanf("%d", &c);
    if (c == -1) {
        root = NULL;
        return root;
    } else {
        root = (BinaryTree *) malloc(sizeof(struct treeNode));
        root->val = c;
        printf("the current tree node val is: %d\n", c);
        root->left = createTree();
        root->right = createTree();
        return root;
    }
}

void preorder_traverse(BinaryTree *root) {
    if (root == NULL) {
        return;
    }
    printf("preorder: %d\n", root->val);
    preorder_traverse(root->left);
    preorder_traverse(root->right);
}

int getTreeDepth(BinaryTree *root) {
    if (root == NULL) {
        return 0;
    } else {
        return getTreeDepth(root->left) > getTreeDepth(root->right) ? getTreeDepth(root->left) + 1 :
               getTreeDepth(root->right) + 1;
    }
}