from math import log
import subsetsum

K = 8


def ksum(A: list, k: int, target: int):
    # 1-SUM, O(n)
    if k == 1:
        if target not in A:
            return None, None
        res = A.copy()
        res.remove(target)
        return [target], res
    # 2-SUM, O(n log n)
    elif k == 2:
        A.sort()
        N = len(A)
        P1 = 0
        P2 = N-1
        while P1 < P2:
            somme = A[P1] + A[P2]
            if somme < target:
                P1 += 1
            elif somme == target:
                # Check maybe erreur P2 = N-1
                yield [A[P1], A[P2]], A[:P1] + A[P1+1:P2] + A[P2+1:]
                P1 += 1
                P2 -= 1
            else:
                P2 -= 1
    else:
        for i in A:
            res = A.copy()
            res.remove(i)
            for j, res2 in ksum(res, k - 1, target - i):
                yield [i] + j, res2


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


lines = [i for i in list_lines(K)]
print(lines, len(lines))

# for solution in ksum(lines, K, 2**(K + 1) - 2):
#     # pass
#     print(solution)


target = (2**(K) - 1)*K//2
nums = lines

has_solution = subsetsum.has_solution(nums, target)
print(f"Can {nums} sum to {target}? {has_solution}")
solutions = []

for solution in subsetsum.solutions(nums, target):
    # `solution` contains indices of elements in `nums`
    subset = set(nums[i] for i in solution)
    if len(subset) == K:
        solutions.append(subset)

print(len(solutions))
