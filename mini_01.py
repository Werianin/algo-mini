import random

def div(dividend, divider):
    if divider == 0:
        print("Division by zero error")
        exit(1)
    digits = str(dividend)
    cnt = 0
    q, r = 0, 0
    for i in range(len(digits)):
        r = r * 10 + int(digits[i])
        res = 0
        while r >= divider:
            cnt += 1
            r -= divider
            res += 1
        q = q * 10 + res
    print(cnt)
    return q, r
div(5454327653, 1)
'''
for _ in range(999999):
    a = random.randint(1, 10**9)
    b = random.randint(1, 10**9)
    if div(a, b) != (a // b, a % b):
        print('Test broke on ', a, b)
        exit(1)
print('All tests passed')
'''
