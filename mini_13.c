#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

size_t main_oil_pipeline(int* arr, size_t len, int* first, int* last) {
    size_t mid = len / 2;

    if (first >= last && first - arr != mid) {
        exit(1);
    }

    int* pivo = lomuto_partition_branchfree(first, last);
    size_t position = pivo - arr;

    if (position == mid) {
        return arr[position];
    }
    if (mid < position) {
        return main_oil_pipeline(arr, len, first, pivo);
    }
    if (position < mid) {
        return main_oil_pipeline(arr, len, pivo + 1, last);
    }
    return 0;
}

int main() {
    srand(time(NULL));
    size_t len = 300;
    int* arr = (int*) malloc(len * sizeof(int));

    for (size_t i = 0; i < len; i++) {
        arr[i] = rand() % 1000;
        printf("%d ", arr[i]);
    }
    size_t ans = main_oil_pipeline(arr, len, arr, arr + len);
    printf("\n\n%zu is the best spot\n", ans);
}

