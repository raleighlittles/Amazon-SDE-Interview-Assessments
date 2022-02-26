import unittest

from algorithm_swap import algorithm_swap


class TestHowManySwaps(unittest.TestCase):
    def test_sample_case(self):
        arr = [5, 1, 4, 2]
        expected_output = 4
        self.assertEqual(algorithm_swap.howManySwaps(arr), expected_output)

    def test_case_0(self):
        arr = [7, 1, 2]
        expected_output = 2
        self.assertEqual(algorithm_swap.howManySwaps(arr), expected_output)

    def test_case_1(self):
        arr = [7, 12]
        expected_output = 0
        self.assertEqual(algorithm_swap.howManySwaps(arr), expected_output)


if __name__ == '__main__':
    unittest.main()
