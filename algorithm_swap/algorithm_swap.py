# Complete the `howManySwaps` function below.

def howManySwaps(arr):
    # Write your code here.

    ## My approach
    ## Use two pointers, called j and k. Increment k until you find a pair of elements out of order. Once such a pair is found,
    ## do a swap, and move j up to where k was, and increment k by 1. Continue
    j, k = 0, 1
    swaps = 0

    for j in range(0, len(arr)):
        for k in range(j, len(arr)):
            if arr[j] > arr[k]:
                # elements are out of order
                arr[j], arr[k] = arr[k], arr[j]
                swaps += 1

    return swaps