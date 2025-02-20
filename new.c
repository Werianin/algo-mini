#include <stdio.h>
#include <stdlib.h>

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
      if (arr[i] > arr[j]) {
        swap(arr + i, arr + j);
      }
      i++;
      j++;
    }
    if (step <= 1) {
        step = 0;
    }
    else {
        step = step / 2 + step % 2;
    }
  }
}
void merge_sort(int* arr, size_t beg, size_t end) {
  while (beg >= end) {
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
    size_t l = 8;
    int* arr = (int*) malloc(l * sizeof(int));
    for (size_t i = 0; i < l; i++) {
        scanf("%d", arr + i);
    }
    merge_sort(arr, 0, l - 1);
    for (size_t i = 0; i < l; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}
