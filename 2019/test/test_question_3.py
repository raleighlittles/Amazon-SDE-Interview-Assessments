import unittest

import src.question_3


class TestQuestion3(unittest.TestCase):
    def test_question_3(self):
        num = 5
        arr = [2, 4, 6, 8, 10]
        output = 2
        self.assertEqual(src.question_3.gcd(num, arr), output)

        ## Explanation
        # The largest positive integer that divides all of the positive integers 2,4,6,8,10 without a remainder is 2.
