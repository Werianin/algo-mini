import numpy as np
import random as rnd
import time
def naive(a, b):
    res = np.zeros((a.shape[0], a.shape[1]))
    for i in range(a.shape[0]):
        for j in range(b.shape[1]):
            for k in range(a.shape[1]):
                res[i, j] += a[i, k] * b[k, j]
    return res

def recursive(x, y):
    if x.shape[0] == 1:
        return np.array([[x[0, 0] * y[0, 0]]])

    if x.shape[0] == 64:
        return naive(x, y)

    mid = x.shape[0] // 2

    a, b = x[:mid, :mid], x[:mid, mid:]
    c, d = x[mid:, :mid], x[mid:, mid:]
    e, f = y[:mid, :mid], y[:mid, mid:]
    g, h = y[mid:, :mid], y[mid:, mid:]

    q1 = np.add(recursive(a, e), recursive(b, g))
    q2 = np.add(recursive(a, f), recursive(b, h))
    q3 = np.add(recursive(c, e), recursive(d, g))
    q4 = np.add(recursive(c, f), recursive(d, h))
    
    upper = np.hstack((q1, q2))
    lower = np.hstack((q3, q4))
    
    return np.vstack((upper, lower))

def strassen(x, y):
    if x.shape[0] == 1:
        return [[x[0, 0] * y[0, 0]]]

    if x.shape[0] == 64:
        return naive(x, y)

    mid = x.shape[0] // 2

    a, b = x[:mid, :mid], x[:mid, mid:]
    c, d = x[mid:, :mid], x[mid:, mid:]
    e, f = y[:mid, :mid], y[:mid, mid:]
    g, h = y[mid:, :mid], y[mid:, mid:]

    p1 = strassen(a, np.subtract(f, h))
    p2 = strassen(np.add(a, b), h)
    p3 = strassen(np.add(c, d), e)
    p4 = strassen(d, np.subtract(g, e))
    p5 = strassen(np.add(a, d), np.add(e, h))
    p6 = strassen(np.subtract(b, d), np.add(g, h))
    p7 = strassen(np.subtract(a, c), np.add(e, f))

    q1 = np.add(np.subtract(np.add(p5, p4), p2), p6)
    q2 = np.add(p1, p2)
    q3 = np.add(p3, p4)
    q4 = np.subtract(np.subtract(np.add(p1, p5), p3), p7)

    upper = np.hstack((q1, q2))
    lower = np.hstack((q3, q4))

    return np.vstack((upper, lower))

def gen_sq_matrix(n: int):
    return np.random.randint(1, 10, (n, n))

def format_table(benchmarks, algos, results):
    benchmarks = list(map(str, benchmarks))
    algos = list(map(str, algos))
    results = [list(map(str, l)) for l in results]
    width_max = [max(len('Benchmark'), max(map(len, benchmarks)))]\
    + [max(max(map(len, [results[i][j] for i in range(len(results))])), len(algos[j])) for j in range(len(algos))]
    table = '| ' + 'Benchmark'.ljust(width_max[0]) + ' | '
    for i in range(len(algos)):
        table += ' ' + algos[i].ljust(width_max[i + 1]) + ' |'
    table += '\n|' + '-' * (len(table) - 2) + '|\n'
    for i in range(len(benchmarks)):
        table += '| ' + benchmarks[i].ljust(width_max[0]) + ' | '
        for j in range(len(algos)):
            table += ' ' + results[i][j].ljust(width_max[j + 1]) + ' |'
        table += '\n'
    print(table)

def benchmarks_formatting(deg):
    bm = []
    for i in range(deg):
        n = str(2 ** i)
        bm.append(n + ' arAvg')
        bm.append(n + ' stdDev')
        bm.append(n + ' geomAvg')
        bm.append('')
    return bm

def arAvg(arr):
    return sum(arr) / len(arr)

def stdDev(avg, arr):
    res = 0
    for n in arr:
        res += (avg - n) ** 2
    return res / len(arr)

def geomAvg(arr):
    res = 1
    for n in arr:
        res *= n
    return res ** (1 / len(arr))

def cmp_of_algos(deg: int):
    benchmarks = benchmarks_formatting(deg)
    algos = ['naive', 'recursive', 'strassen']
    results = [[0] * 3 for _ in range(len(benchmarks))]
    for i in range(deg):
        res = [[0] * 3 for _ in range(3)]
        for j in range(3):
            x = gen_sq_matrix(2 ** i)
            y = gen_sq_matrix(2 ** i)

            start = time.time()
            naive(x, y)
            end = time.time()
            res[0][j] = end - start
        
            start = time.time()
            recursive(x, y)
            end = time.time()
            res[1][j] = end - start

            start = time.time()
            strassen(x, y)
            end = time.time()
            res[2][j] = end - start

        for j in range(3):
            results[i * 4][j] = arAvg(res[j])
            results[i * 4 + 1][j] = stdDev(arAvg(res[j]), res[j])
            results[i * 4 + 2][j] = geomAvg(res[j])
    format_table(benchmarks, algos, results)

cmp_of_algos(10)

