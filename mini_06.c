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

void merge_sort(int* arr, size_t beg, size_t end) {
  if (beg >= end) {
    return;
  }
  size_t mid = beg + (end - beg) / 2;
  merge_sort(arr, beg, mid);
  merge_sort(arr, mid + 1, end);

  merge(arr, beg, mid, end);
  printf(" %zu", huhs);
  steps += huhs;
  huhs = 0;
}

int* sortArray(int* arr, size_t len) {
  merge_sort(arr, 0, len - 1);
  return arr;
}

int main() {
    size_t l = 16;
    int* arr = (int*) malloc(l * sizeof(int));
    for (size_t i = 0; i < l; i++) {
        //scanf("%d", arr + i);
        arr[i] = l - i;
    }
    merge_sort(arr, 0, l - 1);
    printf("\n\n");
    for (size_t i = 0; i < l; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%zu\n", steps);
    free(arr);
}
