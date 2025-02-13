import random

def swap(array, i, j):
    array[i], array[j] = array[j], array[i]

def insertion_sort_k(array, k):
    for i in range(k, len(array)):
        j = i
        while j - k >= 0 and array[j - k] > array[j]:
            swap(array, j - k, j)
            j -= k

def shell_sort(array: list, sequence: list):
    for k in sequence:
        insertion_sort_k(array, k)

def merge(left, right):
    res = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            res.append(left[i])
            i += 1
        else:
            res.append(right[j])
            j += 1
    res.extend(left[i:])
    res.extend(right[j:])
    return res

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])

    return merge(left, right)

ciura_seq = [44842, 19930, 8858, 3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1]

l = [1, 5, 3, 1, 0, 7]
print(merge_sort(l))

'''
for _ in range(20):
    var = random.randint(1, 10**3)
    l.append(var)
shell_sort(l, ciura_seq)
mid = len(l) // 2
left, right = l[:mid], l[mid:]
l = []
for _ in range(mid):
    l.append(right.pop(0))
    l.append(left.pop(0))
if right:
    l.append(right.pop(0))

print(l)

def wiggleSort(nums):
    shell_sort(nums, ciura_seq)
    mid = len(nums) // 2
    left, right = nums[:mid], nums[mid:]
    for i in range(mid):
        nums[2 * i] = right[i]
        nums[2 * i + 1] = left[i]
    if len(right) > len(left):
        nums[-1] = right[-1]
wiggleSort(l)
print(l)
'''
