//
// Created by Bowin on 2022/12/18.
//

#include "ArrayHelper.h"

void arrayExample() {
    int arr[3][4] = {1, 2, 3, 4,
                     5, 6, 7, 8,
                     9, 10, 11, 12};

    printf("the pt of first element: %d\n",arr);
    printf("the pt of whole array: %d\n",&arr);
    printf("the ele is: %d\n",*(*(*(&arr))));
    printf("the pt of next array: %d\n",&arr+1);
    printf("the pt of first row: %d\n",&arr[0]);
    printf("the pt of second row: %d\n",&arr[0]+1);
    printf("the pt of the first element int the first row: %d\n",arr[0]);

    printf("the pt of the second element int the first row: %d\n",arr[0]+1);
}

void bubbleSort(int arr[], int len) {
    int i, j, temp;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

}
