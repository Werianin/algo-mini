#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int* lomuto_partition_branchfree(int* first, int* last) {
    assert(first <= last);
    if (last - first < 2)
        return first;
    --last;
    if (*first > *last)
        swap(first, last);
    int* pivot_pos = first;
    int pivot = *first;
    do {
        ++first;
        assert(first <= last);
    } while (*first < pivot);
    for (int* read = first + 1; read < last; ++read) {
        int x = *read;
        int less = -1 * (x < pivot);
        int delta = less & (read - first);
        first[delta] = *first;
        read[-delta] = x;
        first -= less;
    }
    assert(*first >= pivot);
    --first;
    *pivot_pos = *first;
    *first = pivot;
    return first;
}

void quickSort_Lomuto(int* first, int* last) {
    if (last - first <= 1) {
        return;
    }
    int* pivo = lomuto_partition_branchfree(first, last);
    quickSort_Lomuto(first, pivo);
    quickSort_Lomuto(pivo + 1, last);
}

int main() {
    size_t len = 8;
    int* arr = (int*) malloc(len * sizeof(int));
    for (size_t i = 0; i < len; i++) {
        scanf("%d", arr + i);
    }
    quickSort_Lomuto(arr, arr + len);
    for (size_t i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}

