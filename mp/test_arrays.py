import random


def generate_test_cases(size=10000):
    """
    Generates 10 different types of large arrays to cover various edge cases
    for sorting algorithms. Returns a dictionary of labeled lists.
    """
    test_cases = {}

    # 1. Random Array: Completely unordered elements
    test_cases["Random"] = [random.randint(0, size * 10) for _ in range(size)]

    # 2. Sorted Array (Ascending): Best case for some algorithms (e.g., Insertion Sort)
    test_cases["Sorted (Ascending)"] = list(range(size))

    # 3. Sorted Array (Descending): Worst case for many algorithms
    test_cases["Sorted (Descending)"] = list(range(size, 0, -1))

    # 4. Almost Sorted Array: Mostly sorted, but with 5% of elements randomly swapped
    almost_sorted = list(range(size))
    for _ in range(int(size * 0.05)):
        idx1, idx2 = random.sample(range(size), 2)
        almost_sorted[idx1], almost_sorted[idx2] = (
            almost_sorted[idx2],
            almost_sorted[idx1],
        )
    test_cases["Almost Sorted"] = almost_sorted

    # 5. Many Duplicates: Very few unique values (e.g., only 5 unique numbers)
    test_cases["Many Duplicates"] = [
        random.choice([1, 2, 3, 4, 5]) for _ in range(size)
    ]

    # 6. All Identical Elements: Every element is exactly the same
    test_cases["All Identical"] = [42] * size

    # 7. Negative and Positive Numbers: Mixed signs across a large range
    test_cases["Negative & Positive"] = [
        random.randint(-size, size) for _ in range(size)
    ]

    # 8. Alternating Values: E.g., high, low, high, low pattern
    test_cases["Alternating High/Low"] = [
        size if i % 2 == 0 else 0 for i in range(size)
    ]

    # 9. Sorted with Random Elements at the End: E.g., adding unsorted data to an existing sorted list
    random_end_count = int(size * 0.10)
    sorted_part = list(range(size - random_end_count))
    random_part = [random.randint(0, size) for _ in range(random_end_count)]
    test_cases["Sorted + Random End"] = sorted_part + random_part

    # 10. Sorted with Random Elements at the Beginning:
    random_start_count = int(size * 0.10)
    random_start = [random.randint(0, size) for _ in range(random_start_count)]
    sorted_rest = list(range(random_start_count, size))
    test_cases["Random Start + Sorted"] = random_start + sorted_rest
    file = open("test.txt", "w")
    for b in test_cases.values():
        b = [str(x) for x in b]
        x = " ".join(b)
        print(x)
        file.write(x)
        file.write("\n")


if __name__ == "__main__":
    # Quick test to ensure generation works without printing the whole array
    cases = generate_test_cases(10000)
    print(f"Generated {len(cases)} test cases.")
    for name, arr in cases.items():
        print(f" - {name}: length {len(arr)}, first 3 elements: {arr[:3]}...")
