#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

void swap(int* ptr1, int* ptr2) {
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void merge(int* arr1, int l1, int* arr2, int l2, int* buffer) {
    size_t i = 0, j = 0, k = 0;
    while (i < l1 && j < l2) {
        if (arr1[i] <= arr2[j]) {
            //buffer[k++] = arr1[i++];
            swap(buffer + k++, arr1 + i++);
        }
        else {
            //buffer[k++] = arr2[j++];
            swap(buffer + k++, arr2 + j++);
        }
    }
    while (i < l1) {
        //buffer[k++] = arr1[i++];
        swap(buffer + k++, arr1 + i++);
    }
    while (j < l2) {
        //buffer[k++] = arr2[j++];
        swap(buffer + k++, arr2 + j++);
    }
}

void merge_sort_impl(int* arr, size_t l, int* buffer) {
    if (l <= 1) {
        return;
    }
    if (l == 2) {
        if (arr[0] > arr[1]) {
            swap(arr + 0, arr + 1);
        }
        return;
    }
    size_t mid = l / 2;
    merge_sort_impl(arr, mid, buffer);
    merge_sort_impl(arr + mid, mid + l % 2, buffer);

    merge(arr, mid, arr + mid, mid + l % 2, buffer);

    //memcpy(arr, buffer, l * sizeof(int));
}

void scaryAlert_mergeSort(int* arr, size_t l) {
    if (l <= 1) {
        return;
    }
    
    size_t mid = l / 2;
    scaryAlert_mergeSort(arr, mid);
    scaryAlert_mergeSort(arr + mid, mid + l % 2);

    merge(arr, mid, arr + mid, mid + l % 2, )
}

/*
void merge_sort(int* arr, size_t l) {
    int* result = (int*) malloc(l * sizeof(int));
    merge_sort_impl(arr, l, result);
}*/
/*
void scaryAlert_mergeSort(int* arr, size_t l) {
    size_t unsorted = l / 2 + l % 2;
    merge_sort_impl(arr, l / 2, arr + unsorted);
    /*
    while (unsorted > 1) {
        size_t cur_len = unsorted / 2;
        int* buffer = arr + unsorted / 2 + unsorted % 2;
        merge_sort_impl(arr, cur_len, buffer);
        merge(arr, cur_len, arr + unsorted, l - unsorted, arr + cur_len);
        unsorted = unsorted / 2 + unsorted % 2;
    }
    */
}
*/

int main() {
    size_t l = 16;
    int* arr = (int*) malloc(l * sizeof(int));
    for (size_t i = 0; i < l; i++) {
        scanf("%d", arr + i);
    }
    scaryAlert_mergeSort(arr, l);
    for (size_t i = 0; i < l; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
