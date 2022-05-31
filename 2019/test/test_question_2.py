import unittest

import src.question_2


class TestQuestion2(unittest.TestCase):
    def test_question_2_where_there_is_only_optimal_route(self):
        max_travel_distance = 7000

        forwardRouteList = [[1, 2000],
                            [2, 4000],
                            [3, 6000]]

        returnRouteList = [[1, 2000]]

        output = [[2, 1]]

        self.assertEqual(src.question_2.optimalUtilization(max_travel_distance, forwardRouteList, returnRouteList),
                         output)
        ##  Explanation:
        # There are only three combinations which have a total of 4000, 6000, and 8000 miles, respectively.
        # Since 6000 is the largest use that does not exceed 7000, [2,1] is the optimal pair.

    def test_question_2_where_there_are_more_than_one_optimal_route(self):
        max_travel_distance = 10000

        forwardRouteList = [[1, 3000],
                            [2, 5000],
                            [3, 7000],
                            [4, 10000]]

        returnRouteList = [[1, 2000],
                           [2, 3000],
                           [3, 4000],
                           [4, 5000]]

        output = [[2, 4], [3, 2]]

        self.assertCountEqual(src.question_2.optimalUtilization(max_travel_distance, forwardRouteList, returnRouteList),
                              output)
        ## Explanation
        # There are two pairs of forward and return shipping routes possible that optimally utilizes
        # the given aircraft.
        # Shipping route ID #2 from the forward shipping route list requires 5000 miles travelled, and shipping route ID # 4 from the return shipping route list also requires 5000 miles travelled -- combined, they add up to 10000 miles travelled.
        #
        # Similarly, shipping route #3 from the forward shipping routes list requires 7000 miles travelled, and shipping route ID #2 from return shipping route list requires
        # 3000 miles travelled. These also add up to 10000 miles travelled.
        # Therefore, the pairs of forward and return routes that optimally utilize the aircraft
        # are [2,4] and [3,2].
