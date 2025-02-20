#include <stdio.h>
#include <stdlib.h>

void in_place_merge(int* arr, size_t beg, size_t mid, size_t end) {
	if (beg >= end){
        return;
    }
	size_t l = beg;
    size_t r = mid + 1;
	while (l <= mid && r <= end) {
		if (arr[l] <= arr[r]) {
            l++;
        }
		else {
			int temp = arr[r];
			for (size_t k = r++; k > l; k--) {
				arr[k] = arr[k - 1];
            }
			arr[l++] = temp;
			mid++;
		}
	}
}

void merge_sort(int* arr, size_t beg, size_t end) {
	if (beg >= end) {
        return;
    }
	size_t mid = (end - beg) / 2 + beg;

	merge_sort(arr, beg, mid);
	merge_sort(arr, mid + 1, end);

	in_place_merge(arr, beg, mid, end);
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
