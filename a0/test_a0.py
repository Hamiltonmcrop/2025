"""CSC148 Assignment 0

=== CSC148 Winter 2024 ===
Department of Computer Science,
University of Toronto

This code is provided solely for the personal and private use of
students taking the CSC148 course at the University of Toronto.
Copying for purposes other than this use is expressly prohibited.
All forms of distribution of this code, whether as given or with
any changes, are expressly prohibited.

Author: Jonathan Calver and Sophia Huynh

All of the files in this directory and all subdirectories are:
Copyright (c) Jonathan Calver, Diane Horton, and Sophia Huynh.

=== Module Description ===

This file contains some provided tests for the assignment and is where
you will write additional tests.

To run the tests in this file, right-click here and select the option
that says "Run 'Python tests in test...'"

Note: We will not run pyTA on this file when grading your assignment.

"""
from __future__ import annotations

from four_in_a_row import *
from a0 import *


# TODO add tests for each method and function as indicated in the assignment
#      Note: we have scaffolded some code below for you to add your tests into.
#      Make sure each test has a unique name and that each test starts
#      with test_
#      The tests below are organized into classes to help keep related tests
#      grouped together. In PyCharm you can choose to run all tests in a single
#      class by using the run button beside the class name (just like how you
#      can choose to run a single test). Alternatively, you can run all tests
#      in the file by right-clicking the file name and choosing to run tests.

class TestHelpers:
    """
    These are provided tests related to Task 1, which are meant to remind you
    of the structure of a pytest for later tasks. For Task 1, you are asked
    to write doctests instead.

    While not required, you are welcome to add other pytests here as you
    develop your code.
    """

    def test_within_grid_in_grid(self):
        """Test that (0, 0) is inside a 4-by-4 grid."""
        assert within_grid((0, 0), 4)

    def test_within_grid_outside_grid(self):
        """Test that (4, 4) is outside a 4-by-4 grid."""
        assert not within_grid((4, 4), 4)

    def test_all_within_grid_all_in_grid(self):
        """Test when the four coordinates are all within a 4-by-4 grid."""
        assert all_within_grid([(0, 0), (1, 1), (2, 2), (3, 3)], 4)

    def test_reflect_vertically_above(self):
        """Test reflecting vertically for a coordinate above the middle."""
        assert reflect_vertically((0, 1), 5) == (4, 1)

    def test_reflect_vertically_middle(self):
        """Test reflecting vertically for a coordinate on the middle row."""
        assert reflect_vertically((2, 1), 5) == (2, 1)

    def test_reflect_points(self):
        """Test reflecting a very short line"""
        assert reflect_points([(0, 1), (1, 2)], 5) == [(4, 1), (3, 2)]


class TestLine:
    """
    TODO Task 2: add tests for the Line methods and related functions
                 You must write two tests for each of:
                   - is_row, is_column, and is_diagonal
                   - Line.drop, Line.is_full, and Line.has_fiar
    """
    def test_is_row_1(self):
        """Test if a sequence of squares are in a row"""
        assert is_row([Square((0, 1)), Square((0, 2)), Square((0, 3)), Square((0, 4))])

    def test_is_row_2(self):
        assert is_row([Square((0, 4)), Square((0, 5)), Square((0, 6)), Square((0, 7))])

    def test_is_column_1(self):
        """Test if a sequence of squares are in a column"""
        assert is_column([Square((0, 1)), Square((1, 1)), Square((2, 1)), Square((3, 1))])

    def test_is_column_2(self):
        assert is_column([Square((0, 3)), Square((1, 3)), Square((2, 3)), Square((3, 3))])

    def test_is_diagonal_1(self):
        """Test if a sequences of squared are in a diagonal"""
        assert is_diagonal([Square((0, 0)), Square((1, 1)), Square((2, 2)), Square((3, 3))])

    def test_is_diagonal_2(self):
        assert is_diagonal([Square((4, 0)), Square((3, 1)), Square((2, 2)), Square((1, 3))])

    def test_is_full_1(self):
        """Test if a all Sqaures in a line has a not null symbol"""
        empty_line = Line([Square((0, 1)), Square((1, 1)),
                           Square((2, 1), 'X'), Square((3, 1))])
        assert not empty_line.is_full()

    def test_is_full_2(self):
        full_line = Line([Square((0, 1), 'X'), Square((1, 1), 'X'),
                          Square((2, 1), 'X'), Square((3, 1), 'X')])
        assert full_line.is_full()

    def test_has_fiar_1(self):
        """Test if the line has a four in a row which passes coord"""
        line1 = Line([Square((0, 1)), Square((0, 2)),
                Square((0, 3)), Square((0, 4))])
        assert not line1.has_fiar((0, 1))

    def test_has_fiar_2(self):
        line2 = Line([Square((0, 1), 'X'), Square((0, 2), 'X'),
                      Square((0, 3), 'X'), Square((0, 4), 'X')])
        assert line2.has_fiar((0, 3))

    def test_has_fiar_3(self):
        line3 = Line([Square((0, 1), 'X'), Square((0, 2)),
                             Square((0, 3), 'X'), Square((0, 4), 'X'),
                             Square((0, 5), 'X'), Square((0, 6), 'X')])
        assert line3.has_fiar((0, 6))

class TestGrid:
    """
    TODO Task 3.1: add tests for the Grid methods and related functions
                 You must write two tests for each of:
                   - Grid.drop, Grid.is_full
                   - create_rows_and_columns

    TODO Task 3.2: add tests for the Grid methods and related functions
                 You must write two tests for each of:
                   - Grid.has_fiar
                   - create_mapping
    """
    def test_is_full_1(self):
        g = Grid(4)
        for c in range(4):  # fill the grid and check again
            for r in range(4):
                res = g.drop(c, 'X')
        assert g.is_full()

    def test_is_full_2(self):
        g = Grid(5)
        assert not g.is_full()

    def test_has_fiar_1(self):
        g = Grid(4)
        for i in range(4):
            res = g.drop(i, 'X')
        assert not g.has_fiar((0, 0))

    def test_has_fiar_2(self):
        g = Grid(5)
        for i in range(5):
            res = g.drop(i, 'X')
        assert g.has_fiar((4, 0))

    def test_has_fiar_3(self):
        g = Grid(5)
        for i in range(5):
            res = g.drop(i, 'X')
        assert not g.has_fiar((3, 0))

    def test_drop_1(self):
        g = Grid(4)
        row = g.drop(0, 'X')
        assert row == 3

    def test_drop_2(self):
        g = Grid(5)
        row = g.drop(1, 'X')
        row = g.drop(1, 'X')
        assert row == 3

    def test_create_rows_and_columns_1(self):
        squares = create_squares(4)
        rows, columns = create_rows_and_columns(squares)
        assert rows[0][0] is columns[0][0]

    def test_create_rows_and_columns_1(self):
        squares = create_squares(5)
        rows, columns = create_rows_and_columns(squares)
        assert rows[4][4] is squares[4][4]

    def test_create_mapping_1(self):
        squares = create_squares(6)
        mapping = create_mapping(squares)
        lines = mapping[(2,0)]
        assert is_row(lines[0].cells)

    def test_create_mapping_2(self):
        squares = create_squares(6)
        mapping = create_mapping(squares)
        lines = mapping[(2,0)]
        assert is_diagonal(lines[2].cells)

    def test_create_mapping_3(self):
        squares = create_squares(10)
        mapping = create_mapping(squares)
        lines = mapping[(5,0)]
        assert len(lines) == 4

class TestFourInARow:
    """
    TODO TASK 4:
     - run check_coverage.py to get the code coverage report.
     - Using the code coverage report, identify which branches of the code
       are not currently being tested.
     - add tests below in order to achieve 100% code coverage when you run
       check_coverage.py. Your tests should follow a similar structure
       to the test_x_wins test defined below.
    """

    def test_x_wins(self) -> None:
        """
        Provided test demonstrating how you can test FourInARow.play using
        a StringIO object to "script" the input.

        See both the handout and the Task 4 section of the supplemental slides
        for a detailed explanation of this example.
        """
        fiar = play_game(GAME_SCRIPT_X_WINS)

        assert fiar.result == WIN

    def test_y_wins(self) -> None:
        """
        Check if player Y wins the game
        """
        fiar = play_game(GAME_SCRIPT_O_WINS)

        assert not fiar.result == WIN

    def test_bot(self) -> None:
        """
        Check if player Y wins the game
        """
        script = '6 False False\n'
        fiar = play_game(script)

        assert fiar.result in (DRAW, WIN, LOSS)

    # def test_in_progress(self) -> None:
    #     """
    #     Check if a game is in progress
    #     """
    #     fiar = play_game(GAME_SCRIPT_IN_PROGRESS)
    #
    #     assert fiar.result == IN_PROGRESS
    # TODO Add your tests for Task 4 here. Make sure each test has a unique name
    #      and that each test starts with test_


if __name__ == '__main__':
    import pytest

    pytest.main(['test_a0.py'])
