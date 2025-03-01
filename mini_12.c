#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <wchar.h>

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void quickSort_Lomuto(int* arr, size_t len) {
    if (len < 1) {
        return;
    }
    srand(time(NULL));
    size_t piv_i = random() % len;
    swap(arr, arr + piv_i);
    int pivot = arr[0];
    size_t l, h;
    l = h = 0;
    for (size_t i = 1; i < len; i++) {
        if (arr[i] < pivot) {
            int tmp = arr[i];
            arr[i] = arr[h + 1];
            arr[h + 1] = arr[l];
            arr[l] = tmp;
            l++;
            h++;
        }
        else if (arr[i] == pivot) {
            swap(arr + h + 1, arr + i);
            h++;
        }
    }
    quickSort_Lomuto(arr, l);
    quickSort_Lomuto(arr + h + 1, len - h - 1);
}


int Hoare(int* arr, int beg, int end)
{
    int piv_i = beg + random() % (end - beg);
    swap(arr + beg, arr + piv_i);

    int pivot = arr[beg];
    int i = beg - 1, j = end + 1;
 
    while (1) {
        do {i++;} while (arr[i] < pivot);
        do {j--;} while (arr[j] > pivot);
        if (i >= j) return j;
        swap(arr + i, arr + j);
    }
}

void quickSort_Hoare(int* arr, int beg, int end)
{
    if (beg >= end) {
        return;
    }
    int piv_i = Hoare(arr, beg, end);
    quickSort_Hoare(arr, beg, piv_i);
    quickSort_Hoare(arr, piv_i + 1, end);
}

int* lomuto_partition_branchfree(int* first, int* last) {
    if (last - first < 2)
        return first;
    --last;
    if (*first > *last)
        swap(first, last);
    int* pivot_pos = first;
    int pivot = *first;
    do {
        ++first;
    } while (*first < pivot);
    for (int* read = first + 1; read < last; ++read) {
        int x = *read;
        int less = -1 * (x < pivot);
        int delta = less & (read - first);
        first[delta] = *first;
        read[-delta] = x;
        first -= less;
    }
    --first;
    *pivot_pos = *first;
    *first = pivot;
    return first;
}

void quickSort_LomutoBranchfree(int* first, int* last) {
    if (first >= last) {
        return;
    }
    int* pivo = lomuto_partition_branchfree(first, last);
    quickSort_LomutoBranchfree(first, pivo);
    quickSort_LomutoBranchfree(pivo + 1, last);
}

int main() {
    srand(time(NULL));
    size_t len = 30000000;
    int* arr1 = (int*) malloc(len * sizeof(int));
    int* arr2 = (int*) malloc(len * sizeof(int));
    int* arr3 = (int*) malloc(len * sizeof(int));

    for (size_t i = 0; i < len; i++) {
        arr1[i] = rand() % 1000000000;
    }
    memcpy(arr2, arr1, len * sizeof(int));
    memcpy(arr3, arr1, len * sizeof(int));

    clock_t start, stop;
    printf("lenght of array: %zu\n\n", len);
    start = clock();
    quickSort_Lomuto(arr1, len);
    stop = clock();
    printf("Lomuto %f s\n", ((double) (stop - start)) / CLOCKS_PER_SEC);
    
    start = clock();
    quickSort_Hoare(arr2, 0, len - 1);
    stop = clock();
    printf("Hoare: %f s\n", ((double) (stop - start)) / CLOCKS_PER_SEC);

    start = clock();
    quickSort_LomutoBranchfree(arr3, arr3 + len);
    stop = clock();
    printf("LomutoComeback: %f s\n", ((double) (stop - start)) / CLOCKS_PER_SEC);
}

