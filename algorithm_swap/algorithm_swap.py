# Complete the `howManySwaps` function below.

def howManySwaps(arr):
    # Write your code here.

    ## My approach
    ## Use two pointers, called j and k. Increment k until you find a pair of elements out of order. Once such a pair is found,
    ## do a swap, and move j up to where k was, and increment k by 1. Continue
    j, k = 0, 0
    swaps = 0

    while (j < len(arr)) and (k < len(arr)):
        if arr[j] > arr[k]:
            # You found elements out of order, do a swap.
            swaps += 1
            arr[j], arr[k] = arr[k], arr[j]
            j, k = k, k + 1

        else:
            # Elements in correct order.
            if (k < len(arr) - 2):
                k += 1

            else:
                # You've reached the end of the list.
                break

    return swaps
