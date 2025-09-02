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

dividend, divider = int(input()), int(input())
print(div(dividend, divider))
