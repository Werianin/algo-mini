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

ciura_seq = [44842, 19930, 8858, 3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1]

l = []
for _ in range(20):
    var = random.randint(1, 10**3)
    l.append(var)


shell_sort(l, ciura_seq)
mid = len(l) // 2
left, right = l[:mid], l[mid:]
res = []
for _ in range(mid):
    res.append(right.pop(0))
    res.append(left.pop(0))
if right:
    res.append(right.pop(0))

print(l)
print(res)
