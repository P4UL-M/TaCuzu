from time import time
import sys
sys.setrecursionlimit(10**9)


def list_lines(size: int):
    for i in range(2**size):
        nb = size - 2
        for digit in range(nb):
            c, b, a = getbit(i, digit), getbit(
                i, digit + 1), getbit(i, digit + 2)
            if a == b == c:
                break
        else:
            if countSetBits(i) == size/2:
                yield i


def countSetBits(n):
    count = 0
    while (n):
        n &= (n-1)
        count += 1

    return count


def getbit(nb, n):
    return nb >> n & 1


K = 8
A = [i for i in list_lines(K)]
N = len(A)
A.sort()
M = (1 << N) - 1
P = 2**(K+1) - 2

print(len(A), P)


memo = {}


def knapsack(i, target, k):
    global memo
    if i > N - k:
        return []
    if target == 0 and k == 0:
        return [[]]
    if k <= 0:
        return []
    if (i, target, k) in memo:
        return memo[(i, target, k)]
    ret = []
    for subtaken in knapsack(i + 1, target - A[i], k - 1):
        new = subtaken.copy()
        new.append(A[i])
        ret.append(new)
    ret.extend(knapsack(i + 1, target, k))
    memo[(i, target, k)] = ret
    return ret


start = time()
for subset in knapsack(0, P, K):
    print(subset, sum(subset))
print(round(time() - start, 5))
