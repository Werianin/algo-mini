#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define TEST_COUNT 10000

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
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

double main_oil_pipeline(int* arr, size_t len,
                         int* first, int* last,
                         int* result, size_t* step) {
    size_t mid1 = len / 2;
    size_t mid2 = (len - 1) / 2;

    int* pivo = lomuto_partition_branchfree(first, last);
    size_t position = pivo - arr;

    if (position == mid1 || position == mid2) {
        if (mid1 == mid2) {
            return arr[position];
        }
        else if (*step == 1) {
            return ((double) (*result + arr[position])) / 2;
        }
        *result = arr[position];
        *step = 1;
    }
    if (mid1 < position || mid2 < position) {
        return main_oil_pipeline(arr, len, first, pivo, result, step);
    }
    if (position < mid1 || position < mid2) {
        return main_oil_pipeline(arr, len, pivo + 1, last, result, step);
    }
    return 0;
}

int main() {
    srand(time(NULL));

    for (size_t t = 0; t < TEST_COUNT; t++) {
        size_t len = rand() % 1000 + 1;
        int* arr = (int*) malloc(len * sizeof(int));
        for (size_t i = 0; i < len; i++) {
            arr[i] = rand() % 10000;
        }
        int result = 0;
        size_t step = 0;
        double ans = main_oil_pipeline(arr, len, arr, arr + len, &result, &step);
        quickSort_LomutoBranchfree(arr, arr + len);
        double correct = ((double) (arr[len / 2] + arr[(len - 1) / 2])) / 2;

        free(arr);
        assert(ans == correct);
    }
    printf("All %d tests passed!\n", TEST_COUNT);
}

