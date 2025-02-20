#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void *nc_malloc(size_t size) {
  void *result = malloc(size);
  if (result == NULL) {
    printf("Out of memory\n");
    exit(1);
  }
  return result;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

size_t merge_and_count(int *arr, size_t beg, size_t mid, size_t end, int *res) {
  size_t ls = mid - beg + 1;
  size_t rs = end - mid;
  size_t len = end - beg + 1;

  size_t i = beg;
  size_t j = mid + 1;
  size_t k = 0;

  size_t split = 0;

  while (k < len && i < ls && j < rs) {
    if (arr[i] <= arr[j]) {
      res[k++] = arr[i++];
    } else {
      split += ls - i;
      res[k++] = arr[j++];
    }
  }
  while (i < ls) {
    res[k++] = arr[i++];
  }
  while (j < rs) {
    res[k++] = arr[j++];
  }

  return split;
}

size_t count_global_inversions(int *arr, size_t beg, size_t end) {
  size_t len = beg - end + 1;
  if (len == 1) {
    return 0;
  }
  size_t mid = (end - beg) / 2 + beg;

  size_t left = count_global_inversions(arr, beg, mid);
  size_t right = count_global_inversions(arr, mid + 1, end);

  int *buffer = (int *)nc_malloc(len * sizeof(int));
  size_t split = merge_and_count(arr, beg, mid, end, buffer);
  memcpy(arr, buffer, len * sizeof(int));

  return left + right + split;
}

size_t count_local_inversions(int *arr, size_t len) {
  size_t local = 0;
  for (size_t i = 0; i < len - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      local++;
    }
  }
  return local;
}

bool Great_Condition(int *arr, size_t len) {
  size_t local = count_local_inversions(arr, len);
  size_t global = count_global_inversions(arr, 0, len - 1);
  return global == local;
}
