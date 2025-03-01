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
    size_t piv_i = random() % len;
    swap(arr, arr + piv_i);
    int pivot = arr[0];
    size_t l, h;
    l = h = 0;
    for (size_t i = 1; i < len; i++) {
        if (arr[i] < pivot) {
            int tmp = arr[i];
            arr[i] = arr[h + 1];
            arr[h + 1] = arr[l];
            arr[l] = tmp;
            l++;
            h++;
        }
        else if (arr[i] == pivot) {
            swap(arr + h + 1, arr + i);
            h++;
        }
    }
    quickSort_Lomuto(arr, l);
    quickSort_Lomuto(arr + h + 1, len - h - 1);
}


int Hoare(int* arr, int beg, int end)
{
    int piv_i = beg + random() % (end - beg);
    swap(arr + beg, arr + piv_i);

    int pivot = arr[beg];
    int i = beg - 1, j = end + 1;
 
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
    size_t len = 8;
    int* arr = (int*) malloc(len * sizeof(int));
    for (size_t i = 0; i < len; i++) {
        scanf("%d", arr + i);
    }
    quickSort_Lomuto(arr, len);
    for (size_t i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}
