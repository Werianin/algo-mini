#include <stdio.h>
#include <stdlib.h>

size_t steps = 0;
size_t huhs = 0;

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void merge(int* arr, size_t beg, size_t mid, size_t end) {
  size_t len = end - beg + 1;
  size_t step = (len + 1) / 2;
  while (step > 0) {
    size_t i = beg;
    size_t j = beg + step;
    while (j <= end) {
      huhs++;
      if (arr[i] > arr[j]) {
        swap(arr + i, arr + j);
        steps++;
      }
      i++;
      j++;
    }
    if (step == 1) {
        step = 0;
    }
    else {
        step = (step + 1) / 2;
    }
  }
}

void new_merge(int* arr, size_t beg, size_t mid, size_t end) {

}

void merge_sort(int* arr, size_t beg, size_t end) {
  if (beg >= end) {
    return;
  }
  size_t mid = beg + (end - beg) / 2;
  merge_sort(arr, beg, mid);
  merge_sort(arr, mid + 1, end);

  merge(arr, beg, mid, end);
}

int* sortArray(int* arr, size_t len) {
  merge_sort(arr, 0, len - 1);
  return arr;
}

int main() {
    size_t l = 10;
    int* arr = (int*) malloc(l * sizeof(int));
    for (size_t i = 0; i < l; i++) {
        scanf("%d", arr + i);
    }
    merge_sort(arr, 0, l - 1);
    for (size_t i = 0; i < l; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%zu %zu\n", huhs, steps);
    free(arr);
}
