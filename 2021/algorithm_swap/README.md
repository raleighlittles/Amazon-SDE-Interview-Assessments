# Question description

You're a new Amazon Software Development Engineer (SDE). You've been asked to evaluate the efficiency of an old sorting
algorithm. The following algorithm is used to sort an array of distinct `n` integers.

For the input array `arr` of size `n` do:

* Try to find the smallest pair of indices:

0 \leq i < j \leq n - 1

such that arr[i] > arr[j]. Here 'smallest' means usual alphabetical ordering of pairs, i.e. (i_1, j_1) < (i_2, j_2)
if and only if i_1 < i_2 or (i_1 = j_1 and j_1 < j_2).

* If there is no such pair, stop.
* Otherwise, swap a[i] and a[j] and repeat finding the next pair.

How efficient is this algorithm? Write a function that calculate the number of swaps performed by the above algorithm.

For example, if the initial array is [5, 1, 4, 2], then the algorithm first picks pair (5, 1) and swaps it to produce
array [1,5,4,2]. Next, it picks pair (5,4) and swaps it to produce array [1,4,5,2]. Next, pair (4,2) is picked and
swapped to produce array [1,2,5,4], and finally pair (5,4) is swapped to produce the final sorted array [1,2,4,5], so
the number of swaps performed is 4.

## Function description

Complete the function `howManySwaps` in the editor below. The function should return an integer that denotes the number
of swaps performed by the proposed algorithm on the input array.

The function has the following parameter(s):

* `arr`: integer array of size `n` with all unique elements

## Constraints

* 1 <= n <= 10^5
* 1 <= arr[i] <= 10^9
* all elements of `arr` are unique

# Sample Case 0

## Sample Input

```
3
7
1
2
```

## Sample output

2

## Explanation

There are 3 elements in the array, 7, 1, and 2 respectively.

* Initially, there are two pairs of indices `i < j` for which `a[i] > a[j]`. These pairs are (0, 1) and (0, 2). Since (
  0, 1) is smaller of them, the algorithm swaps elements a[0] and a[1]. The resulting array is [1, 7, 2].
* Next, in the second iteration there is only a single pair of indices `i < j` for which `a[i] > a[j]`. This pair is (1,
  2)
  and the algorithm swaps `a[1]` with `a[2]`. The resulting array is [1, 2, 7].
* After that, the algorithm tries to find the next pair of indices to swap but since there is none, the algorithm stops.

The number of swaps it performed is 2.

# Sample Case 1

## Sample input

```
2
7
12
```

## Sample output

0

## Explanation

There are 2 elements in the array, 7, and 12. The algorithm cannot find any pair in its main loop, so it does not
perform any swaps and stops. The number of performed swaps is 0. 