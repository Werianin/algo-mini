import random

def netherlands(arr):
    beg, i, end = 0, 0, len(arr) - 1
    while i <= end:
        if arr[i] == 0:
            arr[i], arr[beg] = arr[beg], arr[i]
            beg += 1
            i += 1
        elif arr[i] == 2:
            arr[i], arr[end] = arr[end], arr[i]
            end -= 1
        else:
            i += 1



arr = []
for _ in range(20):
    var = random.randint(0, 2)
    arr.append(var)

print(arr)
netherlands(arr)
print(arr)
