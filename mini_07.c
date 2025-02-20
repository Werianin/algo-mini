#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void* nc_malloc(size_t size) {
  void* result = malloc(size);
  if (result == NULL) {
    printf("Out of memory\n");
    exit(1);
  }
  return result;
}

size_t merge_and_count(int* arr, size_t beg, size_t mid, size_t end, int* res) {
  size_t ls = mid - beg + 1;
  size_t rs = end - mid;
  size_t len = end - beg + 1;

  size_t i, j, k;
  i = j = k = 0;

  size_t split = 0;

  while (k < len && i < ls && j < rs) {
    if (arr[beg + i] <= arr[mid + 1 + j]) {
      res[k++] = arr[beg + i++];
    } else {
      split += ls - i;
      res[k++] = arr[mid + 1 + j++];
    }
  }
  while (i < ls) {
    res[k++] = arr[beg + i++];
  }
  while (j < rs) {
    res[k++] = arr[mid + 1 + j++];
  }

  return split;
}

size_t count_global_inversions(int* arr, size_t beg, size_t end, int* buffer) {
  if (beg == end) {
    return 0;
  }
  size_t mid = (end - beg) / 2 + beg;

  size_t left = count_global_inversions(arr, beg, mid, buffer);
  size_t right = count_global_inversions(arr, mid + 1, end, buffer);

  size_t split = merge_and_count(arr, beg, mid, end, buffer);
  memcpy(arr + beg, buffer, (end - beg + 1) * sizeof(int));

  return left + right + split;
}

size_t count_local_inversions(int* arr, size_t len) {
  size_t local = 0;
  for (size_t i = 0; i < len - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      local++;
    }
  }
  return local;
}

size_t isIdealPermutation(int* arr, int len) {
  size_t local = count_local_inversions(arr, len);
  int* buffer = (int*) nc_malloc(len * sizeof(len));
  size_t global = count_global_inversions(arr, 0, len - 1, buffer);
  free(buffer);
  return global == local;
}


int main() {
    size_t l = 3;
    int* arr = (int*) nc_malloc(l * sizeof(int));
    for (size_t i = 0; i < l; i++) {
        scanf("%d", arr + i);
    }
    //int* arr = (int*) nc_malloc(l * sizeof(int));
    printf("\nresult: %zu\n", isIdealPermutation(arr, l));
    for (size_t i = 0; i < l; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}
