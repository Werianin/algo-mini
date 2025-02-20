def merge(left, right, res):
    ls, rs = len(left), len(right)
    n = len(res)
    i = j = k = 0
    while k < n and i < ls and j < rs:
        if left[i] <= right[j]:
            res[k] = left[i]
            i += 1
        else:
            res[k] = right[j]
            j += 1
        k += 1

    while i < ls:
        res[k] = left[i]
        k += 1
        i += 1
    while j < rs:
        res[k] = right[j]
        k += 1
        j += 1

def merge_sort_impl(arr, buffer, beg, end):
    if len(arr) <= 1:
        return
    mid = len(arr) // 2
    merge_sort_impl(arr[:mid], buffer)
    merge_sort_impl(arr[mid:], buffer)

    merge(arr[:mid], arr[mid:], buffer)
    arr[:] = buffer

def merge_sort(arr):
    buffer = [0] * len(arr)
    merge_sort_impl(arr, buffer)


def in_place_mergesort(arr, beg, end):
    if len(arr) <= 1:
        return
    mid = len(arr) // 2
    in_













