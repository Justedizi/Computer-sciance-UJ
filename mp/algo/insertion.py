def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] >= key:
            arr[j] = arr[j + 1]
            j -= 1
        arr[j + 1] = key
    return arr

def selection_sort(arr):
    for i in range(len(arr) - 1):
        min_i = i
        for j in range(i + 1, len(arr)):
            if arr[min_i] > arr[j]:
                min_i = j
        arr[i], arr[min_i] = arr[min_i], arr[i]
    return arr


arr = [12, 1, 1, 2, 7, 125, 14, 4, 124]
print(insertion_sort(arr))
print(selection_sort(arr))
