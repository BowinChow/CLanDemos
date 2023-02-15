#include <stdio.h>
#include "include/BinaryTree.h"
#include "include/ArrayHelper.h"
#include "include/Sortor.h"
#include <math.h>
#include <string.h>

void primeNumber(int number) {
    int upLine = sqrt(number);
    for (int i = 1; i < upLine + 1; ++i) {
        if (number % i == 0) {
            printf("the factor of prime number: %d\n", i);
        }
    }
}

char *mergeTwoString(char *str1, char *str2) {

    if (str1 == NULL && str2 == NULL) {
        return NULL;
    } else if (str1 == NULL && str2 != NULL) {
        return str2;
    } else if (str2 == NULL && str1 != NULL) {
        return str1;
    }
    int len1, len2;
    len1 = strlen(str1);
    len2 = strlen(str2);
    char *res = (char *) malloc(len1 + len2 + 1);
    for (int i = 0; i < len1; ++i) {
        res[i] = str1[i];
    }

    for (int j = 0; j < len2; ++j) {
        res[len1 + j] = str2[j];
    }

    res[len1 + len2] = '\0';
    return res;

}

int *twoSum(int *nums, int target) {
//    static int res[2];

    int *res = (int *) malloc(2 * sizeof(int));
    int numSize = sizeof(nums) / sizeof(nums[0]);
    for (int i = 0; i < numSize - 1; ++i) {
        for (int j = i + 1; j < numSize; ++j) {
            if (nums[i] + nums[j] == target) {
                printf("i: %d and j: %d\n", i, j);
                res[0] = i;
                res[1] = j;
                return res;
            }
        }
    }
    return NULL;
}

void remove_space(char *pStr) {
    char *p_space, *p_char;

    if (pStr == NULL)
        return;
    //p_space指向第一个空格字符
    for (p_space = pStr; *p_space != ' '; ++p_space);
    //当p_space不指向字符串结尾时，寻找它后面的第一个非空格字符
    while (*p_space != '\0') {
        for (p_char = p_space; *p_char == ' '; ++p_char);

        if (*p_char == '\0')
            break;
        else {
            *p_space = *p_char;
            *p_char = ' ';
            ++p_space;
        }
    }
    *p_space = '\0'; //新的结束标记
    return;
}

void stripStr(char *target) {
    char *space, *str;
    if (target == NULL) {
        return;
    }

    for (space = target; *space != ' '; ++space);
    while (*space != '\0') {
        for (str = space; *str == ' '; ++str);
        if (*str == '\0') {
            break;
        } else {
            *space = *str;
            *str = ' ';
            ++space;
        }
    }
    *space = '\0';
}


void treeDemo() {
    BinaryTree *tree = createTree();
    preorder_traverse(tree);
    printf("get depth of tree: %d\n", getTreeDepth(tree));

}

void sortDemo() {
    int arr[] = {9, 2, 8, 11, 3, 5, 9, 13};
    int size = (int) sizeof(arr) / sizeof(arr[0]);
    printArray(arr, size);
    quickSort(arr, 0, size - 1);
    printf("----------------------------------------------------\n");
    printArray(arr, size);
}

int main() {
    printf("main\n");
    sortDemo();
    return 0;
}
