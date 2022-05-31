import unittest
from robot_rodeo import robot_rodeo


class TestDoesCircleExist(unittest.TestCase):

    def test_sample_case(self):
        robot_input = ["RG"]
        expected_output = ["YES"]
        self.assertEqual(robot_rodeo.doesCircleExist(robot_input), expected_output)

    def test_case_0(self):
        robot_input = ["G", "L"]
        expected_output = ["NO", "YES"]
        self.assertEqual(robot_rodeo.doesCircleExist(robot_input), expected_output)

    def test_case_1(self):
        robot_input = ["GRGL"]
        expected_output = ["NO"]
        self.assertEqual(robot_rodeo.doesCircleExist(robot_input), expected_output)
