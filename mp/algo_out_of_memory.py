from sys import prefix


def kadane(arr: list[int]) -> int:
    curr_max = arr[0]
    sub_max = arr[0]
    for i in range(1, len(arr)):
        curr_max = max(arr[i], curr_max + arr[i])
        sub_max = max(sub_max, curr_max)
    return sub_max


arr = [1, -25, 2, 5, -1, 10, -2, -2, -2, 125]
print(kadane(arr))


def binary_search(arr: list[int], t):
    l = 0
    r = len(arr) - 1
    while l <= r:
        mid = (r + l) // 2
        if t > l:
            l = mid + 1
        elif t < l:
            r = mid - 1
        elif mid == t:
            return mid
    return -1


def interpolation_search(arr: list[int], l, r, t):
    if l <= r and t in range(arr[l], arr[r]) and arr[l] != arr[r]:
        mid = l + (r - l) // (arr[r] - arr[l]) * (t - arr[l])
        if arr[mid] == t:
            return mid
        elif arr[mid] < t:
            return interpolation_search(arr, mid + 1, r, t)
        elif arr[mid] > t:
            return interpolation_search(arr, l, mid - 1, t)
    if arr[l] == arr[r]:
        return l
    return -1


def bubble_sort(arr: list[int]):
    n = len(arr)
    # zmiwnna swaped jesli wszystkie elementy sa posrodtwane to zwaca liste
    for i in range(1, n):
        swaped = True
        for j in range(i, n):
            if arr[j - 1] > arr[j]:
                arr[j - 1], arr[j] = arr[j], arr[j - 1]
                swaped = False
        if swaped:
            return arr
    return arr


def counting_sort(arr: list[int]):
    freq = [0] * (max(arr) + 1)
    prefix = [0] * len(arr)
    for a in arr:
        freq[a] += 1
    for i in range(1, len(arr)):
        prefix[i] = prefix[i - 1]
    for i in range(len(arr), -1, -1):
        v = arr[i]
        ans[]
    ans = []
    print(counts)


print(counting_sort(arr))


print(interpolation_search([1, 1, 1, 1, 1, 1, 2, 3], 0, 3, 1))
