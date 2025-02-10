import random
def karazuba(ab, cd):
    l_ab = len(str(ab))
    l_cd = len(str(cd))

    if(l_ab == 1 or l_cd == 1):
        return ab * cd

    l = max(l_ab, l_cd)
    l2 = l // 2

    a = ab // 10**(l2)
    b = ab % 10**(l2)
    c = cd // 10**(l2)
    d = cd % 10**(l2)

    ac = karazuba(a, c)
    bd = karazuba(b, d)
    st3 = karazuba(a + b, c + d)
    ad_bc = st3 - ac - bd

    xy = ac * 10**(2 * l2) + ad_bc * 10**(l // 2) + bd

    return xy

for i in range(10000):
    a = random.randint(1, 10**9)
    b = random.randint(1, 10**9)
    if karazuba(a, b) != a*b:
        print("Test broke on ", a, b)
        exit(1)
print("All tests passed")
