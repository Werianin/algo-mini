import random

counter = 0

def increment():
    global counter
    counter += 1

def swap(array, i, j):
    array[i], array[j] = array[j], array[i]

def insertion_sort_k(array: list, k: int):
    for i in range(k, len(array)):
        j = i
        while j - k >= 0 and array[j - k] > array[j]:
            swap(array, j - k, j)
            j -= k
            increment()

def shell_sort(array: list, sequence: list):
    for k in sequence:
        insertion_sort_k(array, k)

start_l = []
for _ in range(1000):
    var = random.randint(1, 10**4)
    start_l.append(var)


ciura_seq = [44842, 19930, 8858, 3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1]

start_l = [1, 3, 1]

def h_index(array: list):
    shell_sort(array, ciura_seq)

    ind = 0
    for i in range(len(array)):
        cit_cnt = len(array) - i
        if array[i] >= cit_cnt and (i == 0 or array[i - 1] < array[i]):
            ind = max(ind, cit_cnt)
    return ind

print(h_index(start_l))









