#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
    size_t pivot = random() % len;
    swap(arr, arr + pivot);
    size_t i = 1;
    for  (size_t j = 1; j < len; j++) {
        if (arr[j] < arr[0]) {
            swap(arr + i, arr + j);
            i++;
        }
    }
    swap(arr, arr + i - 1);
    quickSort_Lomuto(arr, i - 1);
    quickSort_Lomuto(arr + i, len - i);
}

int Hoare(int* arr, int beg, int end)
{
    srand(time(NULL));
    size_t piv_i = beg + random() % (end - beg);
    swap(arr + beg, arr + piv_i);

    size_t pivot = arr[beg];
    size_t i = beg - 1, j = end + 1;
 
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

int main() {
    size_t len = 10;
    int* arr = (int*) malloc(len * sizeof(int));
    for (size_t i = 0; i < len; i++) {
        scanf("%d", arr + i);
    }
    quickSort_Hoare(arr, 0, len - 1);
    for (size_t i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}
