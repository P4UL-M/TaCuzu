from functools import lru_cache
from time import time


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


K = 16
A = [i for i in list_lines(K)]
N = len(A)
print(A)
A.sort()
M = (1 << N) - 1
P = 2**(K+1) - 2

print(P)


cache = {}


def ksum(bitset, k, target):
    global cache
    ret = []
    if (bitset, k, target) in cache:
        return cache[(bitset, k, target)]
    if k == 1:
        for i in range(N):
            if A[i] == target and ((bitset & (1 << (N - i - 1))) != 0):
                return [1 << (N - i - 1)]
        return []
    elif k == 2:
        P1 = 0
        P2 = N-1
        while P1 < P2:
            if ((1 << (N - P1 - 1)) & bitset) == 0:
                P1 += 1
                continue
            if ((1 << (N - P2 - 1)) & bitset) == 0:
                P2 -= 1
                continue
            somme = A[P1] + A[P2]
            if somme < target:
                P1 += 1
            elif somme == target:
                ret.append((1 << (N - P1 - 1)) | (1 << (N - P2 - 1)))
                P1 += 1
                P2 -= 1
            else:
                P2 -= 1
        cache[(bitset, k, target)] = ret
        return ret

    else:
        for i in range(N):
            if ((1 << (N-i-1)) & bitset) == 0:
                continue
            elt = A[i]
            newtarget = target - elt
            newbitset = bitset & ((1 << N-i-1)-1)
            for result in ksum(newbitset, k-1, newtarget):
                ret.append(result | (1 << N-i-1))
        cache[(bitset, k, target)] = ret
        return ret


start = time()
for bitset in ksum(M, K, P):
    result = []
    for i in range(N):
        if ((1 << (N-i-1)) & bitset) != 0:
            result.append(A[i])
    print(result, sum(result))
print(round(time() - start, 2))
