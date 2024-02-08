"""CSC148 Assignment 0

CSC148 Winter 2024
Department of Computer Science,
University of Toronto

This code is provided solely for the personal and private use of
students taking the CSC148 course at the University of Toronto.
Copying for purposes other than this use is expressly prohibited.
All forms of distribution of this code, whether as given or with
any changes, are expressly prohibited.

Author: Jonathan Calver, Sophia Huynh

All of the files in this directory are
Copyright (c) Jonathan Calver, Diane Horton, Sophia Huynh, and Joonho Kim.

Module Description:

This file contains all of the classes which class FourInARow depends on.
"""
from __future__ import annotations

import python_ta
from python_ta.contracts import check_contracts


###############################################################################
# TODO Task 1:
#      Add at least two doctest examples to each helper below, then
#      implement each helper function according to its docstring.
###############################################################################
@check_contracts
def within_grid(coord: tuple[int, int], n: int) -> bool:
    """
    Return whether <coord> is within an n-by-n grid

    Preconditions:
    - n > 0

    TODO Task 1: add at least two doctests here and implement this function
    >>> within_grid((5,5), 7)
    True
    >>> within_grid((6, 3), 6)
    False
    >>> within_grid((4, 7), 6)
    False
    """
    # TODO: Implement this function
    return coord[0] < n and coord[1] < n

@check_contracts
def all_within_grid(coords: list[tuple[int, int]], n: int) -> bool:
    """
    Return whether every coordinate in <coords> is within an n-by-n grid.

    Preconditions:
    - n > 0

    TODO Task 1: add at least two doctests here and implement this function
    >>> all_within_grid([(3,5), (6,2)], 7)
    True
    >>> all_within_grid([(6,7), (9,8)], 6)
    False
    >>> all_within_grid([(9,11), (7,18), (10, 11)], 10)
    False
    """
    # TODO: Implement this function
    for i in range(len(coords)):
        if coords[i][0] >= int(n) or coords[i][1] >= int(n):
            return False
    return True

@check_contracts
def reflect_vertically(coord: tuple[int, int], n: int) -> tuple[int, int]:
    """
    Return the coordinate that is <coord>, but reflected across the middle
    horizontal of an n-by-n grid. See the handout and supplemental materials
    for a diagram showing an example.

    Preconditions:
    - n > 0
    - within_grid(coord, n)

    TODO Task 1: add at least two doctests here and implement this function
    >>> reflect_vertically((3,2), 5)
    (1, 2)
    >>> reflect_vertically((3, 2), 4)
    (0, 2)
    """
    # TODO: Implement this function
    reflected_row = n - 1 - coord[0]
    return reflected_row, coord[1]

@check_contracts
def reflect_points(line: list[tuple[int, int]],
                   n: int) -> list[tuple[int, int]]:
    """
    Return the given <line> reflected vertically across the middle horizontal
    of an n-by-n grid.

    Preconditions:
    - n > 0
    - all_within_grid(line, n)

    TODO Task 1: add at least two doctests here and implement this function
    >>> reflect_points([(2,3), (2,4), (2, 5), (2, 6)], 7)
    [(4, 3), (4, 4), (4, 5), (4, 6)]
    >>> reflect_points([(1,1), (2,1), (3,1)], 6)
    [(4, 1), (3, 1), (2, 1)]
    >>> reflect_points([(2,0), (3,1), (4,2)], 6)
    [(3, 0), (2, 1), (1, 2)]
    """
    # TODO: Implement this function
    res = []
    for i in range(len(line)):
        reflected = reflect_vertically((line[i][0], line[i][1]), n)
        res.append(reflected)
    return res


@check_contracts
class Square:
    """
    A class representing a single square in a Four-in-a-Row game.

    Attributes:
    - symbol: the symbol indicating which player, if any, has played here. Note,
              the strings 'X' and 'O' are used as the symbols of the players.
    - coord: the (row, column) coordinate indicating this square's location in
             the grid.

    Representation Invariants:
        - self.symbol is None or self.symbol in ('X', 'O')
        - coord[0] >= 0 and coord[1] >= 0
    """
    symbol: None | str
    coord: tuple[int, int]

    def __init__(self, coord: tuple[int, int], s: None | str = None) -> None:
        """
        Initialize this Square with symbol <s> and coordinate <coord>.

        Note: parameter <s> has a defualt parameter value of None specified for
              this method. This means that if we only provide <coord>, then <s>
              will automatically have a value of None (see example below).

        >>> sq = Square((0, 0))
        >>> sq.symbol is None
        True
        >>> sq = Square((0, 1), 'X')
        >>> sq.symbol
        'X'
        >>> sq.coord
        (0, 1)
        """
        self.symbol = s
        self.coord = coord

    def __str__(self) -> str:
        """
        Return a suitable string representation of this Square.

        This method will determine how our Square class is represented as a
        string, when we use either str or print (see below for an example).

        >>> print(Square((0, 0)))
        -
        >>> print(Square((0, 1), 'X'))
        X
        """
        if self.symbol is not None:
            return self.symbol
        else:
            return '-'


###############################################################################
# TODO Task 2:
#      Line Class and related helpers
#      For each of the three public helper functions below,
#      write at least two pytests in test_a0.py, then implement _is_diagonal.
#      Once these tests are passing, see the Line class for the rest of Task 2.
###############################################################################
@check_contracts
def is_row(squares: list[Square]) -> bool:
    """
    Return whether <squares> is a valid row or not.

    A line is a valid row if all of its row coordinates are the same, and
    the column coordinates all increase by exactly 1 from the previous square.

    Preconditions:
    - len(squares) > 3

    >>> l = [Square((0, 1)), Square((0, 2)), Square((0, 3)), Square((0, 4))]
    >>> is_row(l)
    True
    >>> not_l = [Square((0, 1)), Square((0, 2)), Square((0, 4)), Square((0, 3))]
    >>> is_row(not_l)
    False
    """
    cur_row, cur_col = squares[0].coord
    for square in squares[1:]:
        if square.coord[0] != cur_row or square.coord[1] - cur_col != 1:
            return False
        cur_col = square.coord[1]
    return True


@check_contracts
def is_column(squares: list[Square]) -> bool:
    """
    Return whether <squares> is a valid column or not.

    A line is a valid column if all of its column coordinates are the same, and
    the row coordinates all increase by exactly 1 from the previous square.

    Preconditions:
    - len(squares) > 3

    >>> l = [Square((0, 1)), Square((1, 1)), Square((2, 1)), Square((3, 1))]
    >>> is_column(l)
    True
    >>> not_l = [Square((0, 1)), Square((1, 1)), Square((3, 1)), Square((2, 1))]
    >>> is_column(not_l)
    False
    """
    cur_row, cur_col = squares[0].coord
    for square in squares[1:]:
        if square.coord[1] != cur_col or square.coord[0] - cur_row != 1:
            return False
        cur_row = square.coord[0]
    return True


@check_contracts
def is_diagonal(squares: list[Square]) -> bool:
    """
    Return whether <squares> is a valid diagonal or not.

    A line is a valid diagonal if either of the following are true:

    All of its row coordinates increase by exactly 1
    from the previous square, and all of its column coordinates increase by
    exactly 1 from the previous square. This corresponds to a "down diagonal"

    OR

    All of its row coordinates decrease by exactly 1
    from the previous square, and all of its column coordinates increase by
    exactly 1 from the previous square. This corresponds to an "up diagonal"

    Preconditions:
    - len(squares) > 3

    >>> l = [Square((0, 0)), Square((1, 1)), Square((2, 2)), Square((3, 3))]
    >>> is_diagonal(l)
    True
    >>> not_l = [Square((0, 0)), Square((1, 1)), Square((3, 3)), Square((2, 2))]
    >>> is_diagonal(not_l)
    False
    """
    return _is_diagonal(squares, up=True) or _is_diagonal(squares, up=False)


@check_contracts
def _is_diagonal(squares: list[Square], up: bool) -> bool:
    """
    Helper for is_diagonal. <up> determines if it checks for "up" or "down"
    diagonals.

    Return whether <squares> is the specified kind of diagonal.

    Note: since this is a private helper for is_diagonal, we have
    chosen not to include doctests here. is_diagonal should be tested directly.

    Preconditions:
    - len(squares) > 3
    """
    # TODO: Implement this function
    if up:
        for i in range(len(squares) - 1):
            if (squares[i+1].coord[0] - squares[i].coord[0] != -1 or
                    squares[i+1].coord[1] - squares[i].coord[1] != 1):
                return False
    else:
        for i in range(len(squares) - 1):
            if (squares[i+1].coord[0] - squares[i].coord[0] != 1 or
                    squares[i+1].coord[1] - squares[i].coord[1] != 1):
                return False
    return True

@check_contracts
class Line:
    """
    A class representing a line of squares in a game of Four-in-a-Row.

    A line can be in any direction (horizontal, vertical,
                                    up-diagonal, or down-diagonal).

    Attributes:
    - cells: the squares which this line consists of.
    - _coord_to_location: mapping from coordinate to location in the line

    TODO Task 2: Add two appropriate RIs for the cells attribute based on our
                 definition of what properties a line should have.
                 Do NOT change the two provided RIs or add any extra RIs for
                 the _coord_to_location attribute.
    Representation Invariants:
        - len(self._coord_to_location) == len(self.cells)
        - if this line represents a column, then each square's symbol is
          non-None only if each square below it has a non-None symbol.
        - len(self.cells) >= 4
        - The sequence of Squares in the cells is the same as the sequence of
        - the cells in _coord_to_location
        - All the adjacent cells should have adjacent location in the board
        - The sequence of Squares are in a line
    """
    _coord_to_location: dict[tuple[int, int], int]
    cells: list[Square]

    def __init__(self, lst: list[Square]) -> None:
        """
        Initialize this line so that its cells attribute references
        a copy of <lst>.


        >>> s = Square((0, 0), 'X')
        >>> t = Square((0, 2), 'O')
        >>> try:  # example of how @check_contracts will raise an AssertionError
        ...     l = Line([s, t])
        ... except AssertionError:
        ...     print('RI violation caught!')
        RI violation caught!
        """
        self.cells = lst[:]
        self._coord_to_location = {}
        index_ = 0
        for cell in lst:
            self._coord_to_location[cell.coord] = index_
            index_ += 1

    def __len__(self) -> int:
        """
        Return the length of this line.

        >>> l = Line([Square((0, 1)), Square((0, 2)),
        ...           Square((0, 3)), Square((0, 4))])
        >>> len(l)
        4
        """
        # TODO: Implement this method
        return len(self.cells)

    def __getitem__(self, index: int) -> Square:
        """
        Return the Square at the given <index> in this Line.

        This is just for convenience so that we can use [] indexing.
        So, rather than writing self.cells[index], we can directly write
        self[index], as demonstrated in the doctest example below.

        An IndexError is raised if <index> is not a valid index. That is,
        if <index> < 0 or <index> >= len(self.cells).

        Note: this also allows us to conveniently iterate through a Line object
              using syntax like below in the last doctest example. We'll talk
              more about "special methods" and iterators throughout the term.

        >>> l = Line([Square((0, 1)), Square((0, 2)),
        ...           Square((0, 3)), Square((0, 4))])
        >>> l[0].coord
        (0, 1)
        >>> for sq in l:
        ...    print(sq.coord)
        (0, 1)
        (0, 2)
        (0, 3)
        (0, 4)
        """
        # TODO: Implement this method
        if index < 0 or index >= len(self.cells):
            raise IndexError
        return self.cells[index]

    def __contains__(self, coord: tuple[int, int]) -> bool:
        """
        Return whether this line contains the given <coord>.

        >>> l = Line([Square((0, 1)), Square((0, 2)),
        ...           Square((0, 3)), Square((0, 4))])
        >>> (0, 1) in l
        True
        >>> (0, 0) in l
        False
        """
        # TODO: Implement this method
        for i in range(len(self.cells)):
            if self.cells[i].coord == coord:
                return True
        return False

    def drop(self, item: str) -> int:  # | None:
        """
        Return the row-coordinate of where the <item> landed when dropped into
        this column.

        Dropping refers to inserting the <item> into this column so that the
        Square with the largest row-coordinate that previously had a value of
        None now has <item> as its symbol.

        See the assignment materials for a diagram.

        Preconditions:
        - is_column(self.cells)
        - not self.is_full()
        - item in ('X', 'O')

        >>> l = Line([Square((0, 0)), Square((1, 0)),
        ...           Square((2, 0)), Square((3, 0))])  # an empty column
        >>> row_coord = l.drop('X')
        >>> row_coord
        3
        >>> print(l[row_coord])
        X
        """
        # TODO: Implement this method
        for square in self.cells[::-1]:
            if not square.symbol:
                square.symbol = item
                return square.coord[0]


    def __str__(self) -> str:
        """
        Return a suitable string representation of this Line. The string
        ignores the orientation of the line and only represents its values.

        This method is most suitable for displaying a row for the purposes of
        the game.

        >>> print(Line([Square((0, 1)), Square((0, 2)),
        ...       Square((0, 3)), Square((0, 4))]))
        | - - - - |
        """
        rslt = "|"
        for sq in self.cells:
            rslt += f' {sq}'
        return rslt + ' |'

    def is_full(self) -> bool:
        """
        Return whether this line is full.

        Preconditions:
        - is_column(self.cells)

        >>> empty_line = Line([Square((0, 1)), Square((1, 1)),
        ...                     Square((2, 1)), Square((3, 1))])
        >>> empty_line.is_full()
        False
        >>> full_line = Line([Square((0, 1), 'X'), Square((1, 1), 'X'),
        ...                     Square((2, 1), 'X'), Square((3, 1), 'X')])
        >>> full_line.is_full()
        True
        """
        # TODO: Implement this method
        for cell in self.cells:
            if not cell.symbol:
                return False
        return True

    def has_fiar(self, coord: tuple[int, int]) -> bool:
        """
        Return whether this line contains a four-in-a-row that passes through
        the given <coord>.

        Preconditions:
        - coord in self

        >>> line = Line([Square((0, 1)), Square((0, 2)),
        ...              Square((0, 3)), Square((0, 4))])
        >>> line.has_fiar((0, 2))
        False
        >>> line = Line([Square((0, 1), 'X'), Square((0, 2), 'X'),
        ...              Square((0, 3), 'X'), Square((0, 4), 'X')])
        >>> line.has_fiar((0, 2))
        True
        >>> line = Line([Square((0, 1), 'X'), Square((0, 2), 'X'),
        ...              Square((0, 3), 'X'), Square((0, 4), 'X'),
        ...              Square((0, 5), 'X')])
        >>> line.has_fiar((0, 2))
        True
        """
        # TODO: Implement this method
        symbol = None
        same_in_a_row = 0

        # Start from 3 index before and end with 3 index after
        index = self._coord_to_location[coord]
        # Make sure start and end index is not outside the list
        start = max(0, index - 3)
        end = min(index + 4, len(self.cells))
        for i in range(start, end):
            # Current symbol is different from the last symbol, replace sym with
            # current symbol and reset length to 1
            if self.cells[i].symbol != symbol:
                symbol = self.cells[i].symbol
                same_in_a_row = 1
            # Add one if current symbol is same as last symbol and not None
            elif self.cells[i].symbol:
                same_in_a_row += 1
            # If the current symbol is None, do nothing OOOO, NXXXN
            if same_in_a_row == 4:
                return True
        return False





###############################################################################
# TODO Task 3:
#  Grid class and related helpers (see Tasks 3.1 and 3.2 below)
###############################################################################
@check_contracts
def create_squares(n: int) -> list[list[Square]]:
    """
    Return a grid of Square objects representing an n-by-n grid.

    Note: the returned squares are oriented in terms of rows, as demonstrated
          in the doctest below.

    Preconditions:
    - n > 0

    >>> squares = create_squares(4)
    >>> squares[0][0].coord
    (0, 0)
    >>> squares[1][3].coord
    (1, 3)
    """
    squares = []
    for r in range(n):
        row = []
        for c in range(n):
            row.append(Square((r, c), None))
        squares.append(row)
    return squares


@check_contracts
def create_rows_and_columns(squares: list[list[Square]]) -> \
        tuple[list[Line], list[Line]]:
    """
    Return rows and columns for the given <squares>.

    Preconditions:
    - len(squares) > 0
    - every sublist has length equal to the length of <squares>
    - <squares> is oriented in terms of rows, so squares[r][c] gives you the
          Square at coordinate (r, c).

    >>> squares = create_squares(4)
    >>> rows, columns = create_rows_and_columns(squares)
    >>> rows[0][0] is columns[0][0]  # check that the proper aliasing exists
    True
    >>> rows[0][0] is squares[0][0]  # check that the proper aliasing exists
    True
    """
    # TODO: Implement this function
    n = len(squares[0])
    row_list, col_list = [[] for i in range(n)], [[] for i in range(n)]
    # Loop over all squares
    for i in range(n):
        for j in range(n):
            row_list[i].append(squares[i][j])
            col_list[j].append(squares[i][j])
    # Convert the squares in the same line to Line
    for i in range(n):
        row_list[i] = Line(row_list[i])
        col_list[i] = Line(col_list[i])
    return row_list, col_list

@check_contracts
def create_mapping( squares: list[list[Square]]) -> \
        dict[tuple[int, int], list[Line]]:
    """
    Return a mapping from coordinate to the list of lines which cross
    that coordinate, for the given <squares>.

    Note: <squares> is oriented in terms of rows, so squares[r][c] gives you the
          Square at coordinate (r, c).

    The Line objects in the lists in the returned mapping are ordered by:

    horizontal line, then vertical line, then down-diagonal (if it exists),
    and then up-diagonal (if it exists).

    Hint: Your implementation of this function must rely on at least
          two of the defined helpers.

    Preconditions:
    - len(squares) > 0
    - every sublist has length equal to the length of <squares>
    - <squares> is oriented in terms of rows, so squares[r][c] gives you the
          Square at coordinate (r, c).

    >>> squares = create_squares(6)
    >>> mapping = create_mapping(squares)
    >>> lines = mapping[(2,0)]
    >>> len(lines)
    3
    >>> is_row(lines[0].cells)
    True
    >>> is_column(lines[1].cells)
    True
    >>> is_diagonal(lines[2].cells)
    True
    """
    # TODO: Implement this function
    res = {}
    rows, cols = create_rows_and_columns(squares)
    # All down diag then all up diag
    all_diag = all_diagonals(squares)
    # Add row and col, which exists for every coord
    for row in rows:
        cells = row.cells
        for cell in cells:
            res[cell.coord] = [row]

    for col in cols:
        cells = col.cells
        for cell in cells:
            res[cell.coord] = res.get(cell.coord) + [col]

    # all_diagonals returns first down diag then up diag
    for diag in all_diag:
        cells = diag.cells
        for cell in cells:
            res[cell.coord] = res.get(cell.coord) + [diag]

    # for line in all_diag:
    #     cells = line.cells
    #     for cell in cells:
    #         if cell.coord in res.keys():
    #             res[cell.coord] = res.get(cell.coord) + [line]
    #         else:
    #             res[cell.coord] = [line]
    return res

@check_contracts
def get_down_diagonal_starts(n: int) -> list[tuple[int, int]]:
    """
    Return a list of the valid down diagonal start coordinates in
    an n-by-n grid.

    The list must be ordered starting from the bottom-most starting coordinate
    and ending with the right-most starting coordinate. See the examples below
    and the diagrams in the supplemental materials for clarification.

    Hint: this requires no helper to implement

    Preconditions:
    - n >= 4

    >>> get_down_diagonal_starts(4)
    [(0, 0)]
    >>> get_down_diagonal_starts(5)
    [(1, 0), (0, 0), (0, 1)]
    >>> get_down_diagonal_starts(6)
    [(2, 0), (1, 0), (0, 0), (0, 1), (0, 2)]
    """
    # TODO: Implement this function
    res = []
    for i in range(n - 4, -1, -1):
        for j in range(0, n - 3):
            # Diagonal starts are on edge
            if i == 0 or j == 0:
                res.append((i, j))
    return res

@check_contracts
def get_down_diagonal(start: tuple[int, int], n: int) -> list[tuple[int, int]]:
    """
    Given a <start> coordinate, return the list of coordinates for the down
    diagonal starting from that coordinate in an n-by-n grid.

    Hint: this requires no helper to implement

    Preconditions:
    - n > 3
    - within_grid(start, n)
    - start <= (0, n - 4) or start <= (n- 4, 0)

    >>> get_down_diagonal((0, 0), 4)
    [(0, 0), (1, 1), (2, 2), (3, 3)]
    >>> get_down_diagonal((0, 0), 4)
    [(0, 0), (1, 1), (2, 2), (3, 3)]
    >>> get_down_diagonal((0, 0), 5)
    [(0, 0), (1, 1), (2, 2), (3, 3), (4, 4)]
    >>> get_down_diagonal((1, 0), 6)
    [(1, 0), (2, 1), (3, 2), (4, 3), (5, 4)]
    >>> get_down_diagonal((0, 1), 6)
    [(0, 1), (1, 2), (2, 3), (3, 4), (4, 5)]
    """
    # TODO: Implement this function
    row = start[0]
    col = start[1]
    res = []
    while row < n and col < n:
        res.append((row, col))
        row += 1
        col += 1
    return res


@check_contracts
def get_all_down_diagonals(n: int) -> list[list[tuple[int, int]]]:
    """
    Return all the down diagonals in an n-by-n grid.
    The order of the returned diagonals should be consistent with the ordering
    returned by get_down_diagonal_starts.

    Hint: Your implementation of this function must rely on two of the defined
          helpers.

    Preconditions:
    - n > 3

    >>> get_all_down_diagonals(4)
    [[(0, 0), (1, 1), (2, 2), (3, 3)]]
    """
    # TODO: Implement this function
    res = []
    starts = get_down_diagonal_starts(n)
    for start in starts:
        diagonal = get_down_diagonal(start, n)
        res.append(diagonal)
    return res


@check_contracts
def get_coords_of_diagonals(n: int) -> list[list[tuple[int, int]]]:
    """
    Return the coordinates of all the diagonals in an n-by-n grid.
    All down diagonals will appear before the up diagonals in the returned
    list.

    Hint: first find the coordinates of all down diagonals using a helper.

    Hint: each down diagonal has a corresponding up diagonal; a helper you
          defined much earlier in Task 1 should help you conveniently obtain
          each corresponding up diagonal.

    Preconditions:
    - n > 3

    >>> diag_coords = get_coords_of_diagonals(4)
    >>> diag_coords[0]  # the down diagonal
    [(0, 0), (1, 1), (2, 2), (3, 3)]
    >>> diag_coords[1]  # the up diagonal
    [(3, 0), (2, 1), (1, 2), (0, 3)]
    """
    # TODO: Implement this function
    down_diagonals = get_all_down_diagonals(n)
    length = len(down_diagonals)
    up_diagonals = []
    for i in range(length):
        up_diagonal = reflect_points(down_diagonals[i], n)
        up_diagonals.append(up_diagonal)
    return down_diagonals + up_diagonals


@check_contracts
def all_diagonals(squares: list[list[Square]]) -> list[Line]:
    """
    Return a list of all the diagonal lines in the given <grid>.

    Note: <squares> is oriented in terms of rows, so squares[r][c] gives you the
          Square at coordinate (r, c).

    Hint: Your implementation of this function must rely on one of the defined
          helpers.

    >>> squares = create_squares(4)
    >>> diagonals = all_diagonals(squares)
    >>> len(diagonals)
    2
    >>> diagonals[0][0].coord
    (0, 0)
    >>> diagonals[1][0].coord
    (3, 0)
    """
    # TODO: Implement this function
    res = []
    n = len(squares)
    diag_coords = get_coords_of_diagonals(n)
    for coord in diag_coords:
        squ = []
        # squ is a list of squares
        for square in coord:
            squ.append(Square(square))
        line = Line(squ)
        res.append(line)
    return res


@check_contracts
class Grid:
    """
    A class representing the board on which Four-in-a-Row is played.

    Attributes:
    - n: the width and height of the square board
    - _rows: a list of all horizontal lines in the grid, indexed from
             top to bottom
    - _columns: a list of all vertical lines in the grid, indexed from
                left to right
    _mapping: a mapping from coordinate to a list of lines that intersect
              the given coordinate

    Representation Invariants:
    - self.n > 3
    - len(self._mapping) == self.n * self.n
    - len(self._rows) == self.n
    - len(self._columns) == self.n
    """

    n: int
    _rows: list[Line]
    _columns: list[Line]
    _mapping: dict[tuple[int, int], list[Line]]

    def __init__(self, n: int) -> None:
        """
        Initialize this grid to be of size <n> by <n>.

        Preconditions:
        - n > 3

        >>> grid = Grid(4)
        >>> grid.n
        4
        """
        # create the squares which will form our grid. Note, we call this once
        # and pass it to the two helpers below to allow us to make use of
        # aliasing to form various Line objects with common Square objects
        # inside of them.
        squares = create_squares(n)

        self.n = n

        # TODO Task 3.1: Implement the create_rows_and_columns helper
        self._rows, self._columns = create_rows_and_columns(squares)

        # TODO Task 3.2: Implement the create_mapping helper
        self._mapping = create_mapping(squares)

    def __str__(self) -> str:
        """
        Return a suitable string representation of this Grid.

        This method will determine how our Grid class is represented as a
        string, when we use either str or print (see below for an example).

        >>> print(Grid(4))
        | - - - - |
        | - - - - |
        | - - - - |
        | - - - - |
        """
        rslt = ""
        for row in self._rows:
            rslt += f'{row}\n'
        return rslt.rstrip('\n')

    def drop(self, col: int, item: str) -> int | None:
        """
        Return the row-coordinate of where the <item> landed if <item> was
        successfully 'dropped' into the column with
        index <col> or None otherwise.

        Preconditions:
        - 0 <= col < self.n
        - item in ('O', 'X')

        >>> g = Grid(4)
        >>> g.drop(1, 'X')  # will land in the bottom row
        3
        >>> g.drop(1, 'X')  # will land in on top of the previously dropped 'X'
        2
        """
        # TODO: Implement this method
        if self._columns[col].is_full():
            return None
        col = self._columns[col]
        return col.drop(item)
        # for square in col[::-1]:
        #     if not square.symbol:
        #         square.symbol = item

    def has_fiar(self, coord: tuple[int, int]) -> bool:
        """
        Return whether any of the lines containing the square at the
        given <coord> contains a four-in-a-row. The four-in-a-row must include
        the square with the given <coord>.

        Preconditions:
        - 0 <= coord[0] < self.n and 0 <= coord[1] < self.n

        >>> g = Grid(4)
        >>> g.has_fiar((0, 0))
        False
        >>> for _ in range(4):  # make a four-in-a-row
        ...     _ = g.drop(0, 'X')
        >>> g.has_fiar((0, 0))
        True
        """
        # TODO: Implement this method
        lines = self._mapping[coord]
        for line in lines:
            if line.has_fiar(coord):
                return True
        return False

    def is_full(self) -> bool:
        """
        Return True if no more moves could be played.

        >>> g = Grid(4)
        >>> g.is_full()
        False
        >>> for c in range(4):  # fill the grid and check again
        ...     for r in range(4):
        ...         rslt = g.drop(c, 'X')
        >>> g.is_full()
        True
        """
        # TODO: Implement this method
        # check all the squares in all rows
        n = self.n
        for i in range(n):
            for j in range(n):
                if not self._rows[i].cells[j].symbol:
                    return False
        return True

if __name__ == '__main__':
    CHECK_PYTA = True
    if CHECK_PYTA:
        python_ta.check_all(
            config={
                "allowed-import-modules": ["doctest",
                                           "python_ta",
                                           "python_ta.contracts",
                                           "__future__"],
                "disable": ["R1713"]
            }
        )
