import unittest

import src.question_1


class TestQuestion1(unittest.TestCase):
    def test_question_1(self):
        num_orders = 6
        orderList = ["zld 93 12",
                     "fp kindle book",
                     "10a echo show",
                     "17g 12 25 6",
                     "ab1 kindle book",
                     "125 echo dot second generation"]

        expectedOutput = ["125 echo dot second generation",
                          "10a echo show",
                          "ab1 kindle book",
                          "fp kindle book",
                          "zld 93 12",
                          "17g 12 25 6"]

        self.assertEqual(src.question_1.sortOrders(num_orders, orderList), expectedOutput)

## Explanation
# There are four 4 prime orders (lines with words) in this order list. Because "echo" comes before kindle, those lines should come first, with "dot" coming before "show". Because two lines have the same metadata -- "kindle book", their tie should be broken by the identifier, where "ab1" comes before "fp". Finally, the non-Prime numeric orders should come last, in their original order as they were in the input.
