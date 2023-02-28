import functools
import math


def gcd(num: int, arr: list) -> int:
    """
    :param num: The number of elements in arr.
    :param arr: The array of elements over which you want to find the GCD of.
    :return: The GCD.
    """
    return functools.reduce(math.gcd, arr)
