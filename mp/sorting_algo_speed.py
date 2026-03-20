import time
import random
import matplotlib.pyplot as plt


def mesure_time(func):
    def inner(*args):
        start = time.time()
        a = func(*args)
        end = time.time()
        return end - start

    return inner


@mesure_time
def bubble_sort(nums: list[int]):
    n = len(nums)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if nums[j] > nums[j + 1]:
                nums[j], nums[j + 1] = nums[j + 1], nums[j]
                swapped = True
        if not swapped:
            break
    return nums


@mesure_time
def selection_sort(nums: list[int]):
    n = len(nums)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            if nums[j] < nums[min_idx]:
                min_idx = j
        nums[i], nums[min_idx] = nums[min_idx], nums[i]
    return nums


@mesure_time
def cocktail_sort(nums: list[int]):
    n = len(nums)
    swapped = True
    start = 0
    end = n - 1
    while swapped:
        swapped = False
        for i in range(start, end):
            if nums[i] > nums[i + 1]:
                nums[i], nums[i + 1] = nums[i + 1], nums[i]
                swapped = True
        if not swapped:
            break
        swapped = False
        end = end - 1
        for i in range(end - 1, start - 1, -1):
            if nums[i] > nums[i + 1]:
                nums[i], nums[i + 1] = nums[i + 1], nums[i]
                swapped = True
        start = start + 1
    return nums


@mesure_time
def insertion_sort(nums: list[int]):
    n = len(nums)
    for i in range(1, n):
        key = nums[i]
        j = i - 1
        while j >= 0 and key < nums[j]:
            nums[j + 1] = nums[j]
            j -= 1
        nums[j + 1] = key
    return nums


times: dict[str, list[float]] = {
    "bubble": [],
    "cocktail": [],
    "insertion": [],
    "selection": [],
}

with open("test.txt", "r") as file:
    data = file.readlines()
    for nums in data:
        nums = nums.split(" ")
        nums = [int(n) for n in nums]
        times["bubble"].append(bubble_sort(nums.copy()))
        times["cocktail"].append(cocktail_sort(nums.copy()))
        times["selection"].append(selection_sort(nums.copy()))
        times["insertion"].append(insertion_sort(nums.copy()))

x = list(times.keys())
y = [sum(a) / 10 for a in times.values()]
plt.bar(x, y)
plt.xlabel("alogrithm")
plt.ylabel("avg time in seconds (10 tests)")
plt.savefig("wykres.png")
