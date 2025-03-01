#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} pair;

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

pair Lomuto(int* arr, size_t len) {
    size_t i = 1;
    for (size_t j = 1; j < len; j++) {
        if (arr[j] < arr[0]) {
            swap(arr + i, arr + j);
            i++;
        }
    }
    swap(arr, arr + i - 1);
    pair res;
    res.a = i - 1;
    res.b = i - 1;
    return res;
}

pair Hoare(int* arr, size_t len) {
    size_t beg = 0;
    size_t end = 0;
    for (size_t i = 1; i < len; i++) {
        if (arr[i] < arr[0]) {
            int tmp = arr[i];
            arr[i] = arr[end + 1];
            arr[end + 1] = arr[beg];
            arr[beg] = tmp;
            beg++;
            end++;
        }
        else if (arr[i] == arr[0]) {
            swap(arr + end + 1, arr + i);
            end++;
        }
    }
    pair res;
    res.a = beg;
    res.b = end;
    return res;
}

void quickSort(int* arr, size_t len, pair partition(int*, size_t)) {
    if (len < 1) {
        return;
    }
    size_t pivot = random() % len;
    swap(arr, arr + pivot);
    pair pivs = partition(arr, len);
    quickSort(arr, pivs.a, partition);
    quickSort(arr + pivs.b + 1, len - pivs.b - 1, partition);
}

int main() {
    size_t len = 8;
    int* arr = (int*) malloc(len * sizeof(int));
    for (size_t i = 0; i < len; i++) {
        scanf("%d", arr + i);
    }
    //quickSort(arr, len, Hoare);
    Hoare(arr, len);
    for (size_t i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}
