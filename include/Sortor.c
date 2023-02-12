
//
// Created by Bowin on 2023/2/12.
//
#include "Sortor.h"

void printArray(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertSort(int *arr, int size) {
    for (int i = 1; i < size; ++i) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && temp < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void quickSort(int *arr, int start, int end) {
    int i = start, j = end, temp = arr[start];
    if (i >= j) {
        return;
    }
    while (i < j) {
        while (i < j && arr[j] >= temp) {
            j--;
        }
        if (i < j) {
            arr[i++] = arr[j];
        }
        while (i < j && arr[i] < temp) {
            i++;
        }
        if (i < j) {
            arr[j--] = arr[i];
        }
    }
    arr[i] = temp;
    quickSort(arr, start, i - 1);
    quickSort(arr, i + 1, end);
}