def counting_sort(arr):
    n = len(arr)
    max_val = max(arr)
    res = [0] * n
    counter = [0] * (max_val + 1)
    for a in arr:
        counter[a] += 1

    for i in range(1, max_val + 1):
        counter[i] += counter[i - 1]

    for i in range(n - 1, -1, -1):
        val = arr[i]
        res[counter[val] - 1] = val
        counter[val] -= 1
    return res


def counting_sort_radix(arr, exp):
    n = len(arr)
    res = [0] * n
    counter = [0] * 10
    for a in arr:
        counter[(a // exp) % 10] += 1

    for i in range(1, 10):
        counter[i] += counter[i - 1]

    for i in range(n - 1, -1, -1):
        val = arr[i] // exp
        res[counter[val % 10] - 1] = arr[i]
        counter[val % 10] -= 1
    return res


def radix_sort(arr):
    exp = 1
    max_val = max(arr)
    while max_val // exp > 0:
        arr = counting_sort_radix(arr, exp)
        exp *= 10
    return arr


def bucket_sort(arr):
    n = len(arr)
    buckets = [[] for _ in range(n)]
    for a in arr:
        bucket = int(a * n)
        buckets[bucket].append(a)
    for bucket in buckets:
        bucket.sort()
    # list comprehension na odwrot
    res = []
    for bucket in buckets:
        for b in bucket:
            res.append(b)
    return res


arr = [12, 1, 1, 4, 2, 3, 44, 2, 4, 5, 66, 2]
arr_floating = [0.21, 0.1, 0.002, 0.534, 0.45]
# print counting_sort(arr)
# print(radix_sort(arr))
print(bucket_sort(arr_floating))
