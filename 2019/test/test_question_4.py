import unittest

import src.question_4


class TestQuestion4(unittest.TestCase):
    def test_question_4_for_a_single_day(self):
        num_days = 1
        original_array = [1, 0, 0, 0, 0, 1, 0, 0]
        output = [0, 1, 0, 0, 1, 0, 1, 0]
        self.assertEqual(src.question_4.cell_competition(original_array, num_days), output)

    def test_question_4_for_two_days(self):
        num_days = 2
        original_array = [1, 1, 1, 0, 1, 1, 1, 1, ]
        output = [0, 0, 0, 0, 0, 1, 1, 0]
        self.assertEqual(src.question_4.cell_competition(original_array, num_days), output)
