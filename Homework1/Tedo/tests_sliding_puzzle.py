import unittest
from solution_sliding_puzzle import is_solvable, ida_star, generate_final_state


class TestNPuzzleSolver(unittest.TestCase):
    def test_case_4(self):
        """Test case for input:
        8
        -1
        1 2 3
        4 5 6
        0 7 8
        """
        initial_state = [[1, 2, 3], [4, 5, 6], [0, 7, 8]]
        rows = 3
        blank_index = -1
        goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
        self.assertEqual(generate_final_state(8, rows, blank_index), goal_state)
        self.assertTrue(is_solvable(initial_state, rows))
        length, steps = ida_star(initial_state, goal_state, rows)
        self.assertEqual(length, 2)
        self.assertEqual(steps, ["left", "left"])

    def test_case_3(self):
        """Test case for input:
        8
        8
        1 2 3
        4 5 6
        0 7 8
        """
        initial_state = [[1, 2, 3], [4, 5, 6], [0, 7, 8]]
        rows = 3
        blank_index = 8
        goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
        self.assertEqual(generate_final_state(8, rows, blank_index), goal_state)

        self.assertTrue(is_solvable(initial_state, rows))
        length, steps = ida_star(initial_state, goal_state, rows)
        self.assertEqual(length, 2)
        self.assertEqual(steps, ["left", "left"])

    def test_case_2(self):
        """Test case for input:
        8
        4
        1 0 3
        4 2 5
        6 7 8
        """
        initial_state = [[1, 0, 3], [4, 2, 5], [6, 7, 8]]
        rows = 3
        blank_index = 4
        goal_state = [[1, 2, 3], [4, 0, 5], [6, 7, 8]]
        self.assertEqual(generate_final_state(8, rows, blank_index), goal_state)
        self.assertTrue(is_solvable(initial_state, rows))
        length, steps = ida_star(initial_state, goal_state, rows)
        self.assertEqual(length, 1)
        self.assertEqual(steps, ["up"])

    def test_case_1(self):
        """Test case for input:
        8
        0
        1 2 0
        3 4 5
        6 7 8
        """
        initial_state = [[1, 2, 0], [3, 4, 5], [6, 7, 8]]
        rows = 3
        blank_index = 0
        goal_state = [[0, 1, 2], [3, 4, 5], [6, 7, 8]]
        self.assertEqual(generate_final_state(8, rows, blank_index), goal_state)
        self.assertTrue(is_solvable(initial_state, rows))
        length, steps = ida_star(initial_state, goal_state, rows)
        self.assertEqual(steps, ["right", "right"])
        self.assertEqual(length, 2)

    def test_unsolvable_case(self):
        """Test case for unsolvable puzzle:
        8
        -1
        1 2 3
        4 5 6
        8 7 0
        """
        initial_state = [[1, 2, 3], [4, 5, 6], [8, 7, 0]]
        rows = 3
        blank_index = -1
        goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
        self.assertEqual(generate_final_state(8, rows, blank_index), goal_state)

        self.assertFalse(is_solvable(initial_state, rows))

    def test_solved(self):
        """Test case for unsolvable puzzle:
        8
        -1
        1 2 3
        4 5 6
        7 8 0
        """
        initial_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
        rows = 3
        blank_index = -1
        goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
        self.assertEqual(generate_final_state(8, rows, blank_index), goal_state)
        self.assertTrue(is_solvable(initial_state, rows))
        length, steps = ida_star(initial_state, goal_state, rows)
        self.assertEqual(length, 0)
        self.assertEqual(steps, [])

    def test_solved2(self):
        """Test case for unsolvable puzzle:
        8
        4
        1 2 3
        4 0 5
        6 7 8
        """
        initial_state = [[1, 2, 3], [4, 0, 5], [6, 7, 8]]
        rows = 3
        blank_index = 4
        goal_state = [[1, 2, 3], [4, 0, 5], [6, 7, 8]]
        self.assertEqual(generate_final_state(8, rows, blank_index), goal_state)
        self.assertTrue(is_solvable(initial_state, rows))
        length, steps = ida_star(initial_state, goal_state, rows)
        self.assertEqual(length, 0)
        self.assertEqual(steps, [])

    def test_hard(self):
        """Test case for hard puzzle:
        8
        -1
        6 5 3
        2 4 8
        7 0 1
        """
        initial_state = [[6, 5, 3], [2, 4, 8], [7, 0, 1]]
        rows = 3
        blank_index = -1
        goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
        self.assertEqual(generate_final_state(8, rows, blank_index), goal_state)
        self.assertTrue(is_solvable(initial_state, rows))
        length, steps = ida_star(initial_state, goal_state, rows)
        self.assertEqual(length, 21)
        self.assertEqual(
            steps,
            [
                "left",
                "down",
                "down",
                "right",
                "right",
                "up",
                "left",
                "up",
                "right",
                "down",
                "left",
                "down",
                "left",
                "up",
                "right",
                "down",
                "right",
                "up",
                "up",
                "left",
                "left",
            ],
        )


if __name__ == "__main__":
    unittest.main()
