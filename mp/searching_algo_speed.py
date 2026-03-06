import time
import random


def mesure_time(func):
    def inner(*args):
        start = time.time()
        a = func(*args)
        end = time.time()
        return end - start

    return inner


@mesure_time
def lienear_search(arr: list[int], target: int) -> int:
    return arr.index(target)


@mesure_time
def bin_search(arr: list[int], target: int) -> int:
    l = 0
    r = len(arr) - 1
    while l <= r:
        middle = (l + r) // 2
        if arr[middle] == target:
            return middle
        elif arr[middle] > target:
            l = middle + 1
        elif arr[middle] < target:
            r = middle - 1
    return -1


@mesure_time
def interpolary_search(arr: list[int], target: int, l: int, r: int) -> int:
    if l <= r and target in range(arr[l], arr[r]):
        pos = l + int((r - l) / (arr[r] - arr[l])) * (target - arr[l])
        if arr[pos] == target:
            return pos
        elif arr[pos] < target:
            return interpolary_search(arr, target, pos + 1, r)
        elif arr[pos] > target:
            return interpolary_search(arr, target, l, pos - 1)
    return -1


for i in [10000, 1000000, 100000000]:
    arr = [j for j in range(i)]
    target = random.choice(arr)
    print("linear", lienear_search(arr, target))
    print("binary", bin_search(arr, 1))
    print("interpolary", interpolary_search(arr, target, 0, len(arr) - 1))
    print("\n")
