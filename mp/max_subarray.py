def max_subarray_naive(arr: list[int]) -> tuple[list[int], int | float]:
    n: int = len(arr)
    max_subarray: list[int] = []
    max_val = float("-inf")
    for i in range(0, n):
        curr_val: int = 0
        for j in range(i, n):
            curr_val += arr[j]
            if curr_val >= max_val:
                max_subarray = arr[i : j + 1]
                max_val = curr_val
    return (max_subarray, max_val)


def max_subarray_brutforce(arr: list[int]) -> tuple[list[int], int | float]:
    n: int = len(arr)
    max_subarray: list[int] = []
    max_val = float("-inf")
    for i in range(0, n):
        for j in range(i, n):
            curr_subarray: list[int] = arr[i : j + 1]
            curr_val = sum(curr_subarray)
            if curr_val >= max_val:
                max_val = curr_val
                max_subarray = curr_subarray

    return (max_subarray, max_val)


def max_subarray_kadne(arr: list[int]) -> tuple[list[int], int]:
    n: int = len(arr)
    start: int = 0
    end: int = 0
    temp_start: int = 0
    max_val: int = arr[0]
    curr_val: int = arr[0]
    for i in range(1, n):
        if arr[i] > curr_val + arr[i]:
            curr_val = arr[i]
            temp_start = i
        else:
            curr_val += arr[i]

        if curr_val >= max_val:
            max_val = curr_val
            start = temp_start
            end = i

    return (arr[start : end + 1], max_val)


tests: list[list[int]] = [
    [1, 2, 4, -4, 5],
    [12, -4, 45, -2, 42, -1, 10, 15, -13],
    [1, 4, 12, -2, -3, -42, 7, 2],
    [-14, -2, -2, -1, -25],
    [1, 25, 5, 6, 6, 7],
]

for test in tests:
    print("arr", test)
    print("brutforce:", max_subarray_brutforce(test))
    print("naive", max_subarray_naive(test))
    print("kadne", max_subarray_kadne(test))
    print("\n")
