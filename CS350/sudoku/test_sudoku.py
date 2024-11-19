import os
import tempfile
from unittest import mock

import pytest

import sudoku


def _assert_puzzles_equal(actual, expected):
    # compare each cell of puzzles
    for i in range(9):  # rows
        for j in range(9):  # columns
            actual_value = actual.get_value(i + 1, j + 1)
            expected_value = expected.get_value(i + 1, j + 1)

            assert actual_value == expected_value, \
                "Incorrect value at {}: {} != {}".format((i + 1, j + 1),
                                                         actual_value,
                                                         expected_value)


def _create_puzzle_from_string(s):
    try:
        # Windows does not allow opening a named temporary file a second time
        # when it is still open *unless* the file is not deleted when it is
        # closed (https://github.com/python/cpython/issues/58451). Thus, the
        # file must be removed manually after it is used.
        with tempfile.NamedTemporaryFile(mode='w', delete=False) as stream:
            stream.write(s)
            stream.flush()

        return sudoku.Puzzle.load(stream.name)
    finally:
        os.remove(stream.name)


def _create_incomplete_puzzle():
    puzzle = sudoku.Puzzle()

    # puzzle:
    #   5 3 . . 7 . . . .
    #   6 . . 1 9 5 . . .
    #   . 9 8 . . . . 6 .
    #   8 . . . 6 . . . 3
    #   4 . . 8 . 3 . . 1
    #   7 . . . 2 . . . 6
    #   . 6 . . . . 2 8 .
    #   . . . 4 1 9 . . 5
    #   . . . . 8 . . 7 9
    values = [
        (1, 1, 5), (1, 2, 3), (1, 5, 7),
        (2, 1, 6), (2, 4, 1), (2, 5, 9), (2, 6, 5),
        (3, 2, 9), (3, 3, 8), (3, 8, 6),
        (4, 1, 8), (4, 5, 6), (4, 9, 3),
        (5, 1, 4), (5, 4, 8), (5, 6, 3), (5, 9, 1),
        (6, 1, 7), (6, 5, 2), (6, 9, 6),
        (7, 2, 6), (7, 7, 2), (7, 8, 8),
        (8, 4, 4), (8, 5, 1), (8, 6, 9), (8, 9, 5),
        (9, 5, 8), (9, 8, 7), (9, 9, 9),
    ]
    for row, column, value in values:
        puzzle.set_value(row, column, value)

    return puzzle


def _create_solved_puzzle():
    puzzle = sudoku.Puzzle()

    # puzzle:
    #   5 3 4 6 7 8 9 1 2
    #   6 7 2 1 9 5 3 4 8
    #   1 9 8 3 4 2 5 6 7
    #   8 5 9 7 6 1 4 2 3
    #   4 2 6 8 5 3 7 9 1
    #   7 1 3 9 2 4 8 5 6
    #   9 6 1 5 3 7 2 8 4
    #   2 8 7 4 1 9 6 3 5
    #   3 4 5 2 8 6 1 7 9
    values = [
        [5, 3, 4, 6, 7, 8, 9, 1, 2],
        [6, 7, 2, 1, 9, 5, 3, 4, 8],
        [1, 9, 8, 3, 4, 2, 5, 6, 7],
        [8, 5, 9, 7, 6, 1, 4, 2, 3],
        [4, 2, 6, 8, 5, 3, 7, 9, 1],
        [7, 1, 3, 9, 2, 4, 8, 5, 6],
        [9, 6, 1, 5, 3, 7, 2, 8, 4],
        [2, 8, 7, 4, 1, 9, 6, 3, 5],
        [3, 4, 5, 2, 8, 6, 1, 7, 9],
    ]
    for i, row in enumerate(values, start=1):
        for j, value in enumerate(row, start=1):
            puzzle.set_value(i, j, value)

    return puzzle


@pytest.mark.unit
class TestPuzzle:
    def test_load(self):
        actual = _create_puzzle_from_string("\n".join([
            '5 3 . . 7 . . . .',
            '6 . . 1 9 5 . . .',
            '. 9 8 . . . . 6 .',
            '8 . . . 6 . . . 3',
            '4 . . 8 . 3 . . 1',
            '7 . . . 2 . . . 6',
            '. 6 . . . . 2 8 .',
            '. . . 4 1 9 . . 5',
            '. . . . 8 . . 7 9',
        ]))

        expected = _create_incomplete_puzzle()
        _assert_puzzles_equal(actual, expected)

    def test_get_value_1_based_indexing(self):
        puzzle = sudoku.Puzzle()
        for index in [0, 10]:  # row indices
            with pytest.raises(IndexError):
                puzzle.get_value(index, 5)
        for index in [0, 10]:  # column indices
            with pytest.raises(IndexError):
                puzzle.get_value(5, index)

    def test_set_value_1_based_indexing(self):
        puzzle = sudoku.Puzzle()
        with pytest.raises(IndexError):
            puzzle.set_value(0, 0, None)
        with pytest.raises(IndexError):
            puzzle.set_value(10, 10, None)

    def test_is_valid_empty_puzzle(self):
        puzzle = sudoku.Puzzle()
        assert puzzle.is_valid()

    def test_is_valid_incomplete_puzzle(self):
        puzzle = _create_incomplete_puzzle()
        assert puzzle.is_valid()

    def test_is_valid_invalid_row(self):
        # first row
        puzzle = _create_incomplete_puzzle()
        puzzle.set_value(1, 8, 3)
        print(puzzle.is_valid())
        print(puzzle)
        assert not puzzle.is_valid()

        # last row
        puzzle = _create_incomplete_puzzle()
        puzzle.set_value(9, 1, 9)
        assert not puzzle.is_valid()

        # middle row
        puzzle = _create_incomplete_puzzle()
        puzzle.set_value(5, 5, 4)
        assert not puzzle.is_valid()

    def test_is_valid_invalid_column(self):
        # first column
        puzzle = _create_incomplete_puzzle()
        puzzle.set_value(3, 1, 4)
        assert not puzzle.is_valid()

        # last column
        puzzle = _create_incomplete_puzzle()
        puzzle.set_value(9, 2, 3)
        assert not puzzle.is_valid()

        # middle column
        puzzle = _create_incomplete_puzzle()
        puzzle.set_value(5, 5, 7)
        assert not puzzle.is_valid()

    def test_is_valid_invalid_block(self):
        # top-left block
        puzzle = _create_incomplete_puzzle()
        puzzle.set_value(2, 2, 8)
        assert not puzzle.is_valid()

        # bottom-right block
        puzzle = _create_incomplete_puzzle()
        puzzle.set_value(8, 8, 2)
        assert not puzzle.is_valid()

        # middle block
        puzzle = _create_incomplete_puzzle()
        puzzle.set_value(6, 6, 8)
        assert not puzzle.is_valid()

    def test_is_valid_complete_puzzle(self):
        puzzle = _create_solved_puzzle()
        assert puzzle.is_valid()

    def test_is_solved_empty_board(self):
        puzzle = sudoku.Puzzle()
        assert not puzzle.is_solved()

    def test_is_solved_incomplete_puzzle(self):
        puzzle = _create_incomplete_puzzle()
        assert not puzzle.is_solved()

    def test_is_solved_invalid_puzzle(self):
        puzzle = _create_solved_puzzle()
        puzzle.set_value(2, 2, None)
        print(puzzle)

        puzzle = _create_solved_puzzle()
        puzzle.set_value(9, 9, 8)
        assert not puzzle.is_solved()

        puzzle = _create_solved_puzzle()
        puzzle.set_value(5, 5, 7)
        assert not puzzle.is_solved()

    def test_is_solved_complete_puzzle(self):
        puzzle = _create_solved_puzzle()
        assert puzzle.is_solved()


@pytest.mark.integration
class TestBacktracking:
    @pytest.mark.parametrize("puzzle,solution", [
        ("\n".join([
            '5 3 . . 7 . . . .',
            '6 . . 1 9 5 . . .',
            '. 9 8 . . . . 6 .',
            '8 . . . 6 . . . 3',
            '4 . . 8 . 3 . . 1',
            '7 . . . 2 . . . 6',
            '. 6 . . . . 2 8 .',
            '. . . 4 1 9 . . 5',
            '. . . . 8 . . 7 9',
         ]), "\n".join([
            '5 3 4 6 7 8 9 1 2',
            '6 7 2 1 9 5 3 4 8',
            '1 9 8 3 4 2 5 6 7',
            '8 5 9 7 6 1 4 2 3',
            '4 2 6 8 5 3 7 9 1',
            '7 1 3 9 2 4 8 5 6',
            '9 6 1 5 3 7 2 8 4',
            '2 8 7 4 1 9 6 3 5',
            '3 4 5 2 8 6 1 7 9',
         ])),
        ("\n".join([
            '. . 2 3 . . . . 4',
            '. 7 . . 1 . . 9 .',
            '1 . . . . 6 5 . .',
            '6 . . . . 9 8 . .',
            '. 2 . . 5 . . 7 .',
            '. . 5 6 . . . . 9',
            '. . 8 5 . . . . 2',
            '. 5 . . 6 . . 3 .',
            '7 . . . . 3 1 . .',
         ]), "\n".join([
            '9 6 2 3 8 5 7 1 4',
            '5 7 3 4 1 2 6 9 8',
            '1 8 4 7 9 6 5 2 3',
            '6 3 7 2 4 9 8 5 1',
            '4 2 9 1 5 8 3 7 6',
            '8 1 5 6 3 7 2 4 9',
            '3 9 8 5 7 1 4 6 2',
            '2 5 1 8 6 4 9 3 7',
            '7 4 6 9 2 3 1 8 5',
         ])),
        ("\n".join([
            '. . . 6 . 3 . . .',
            '. 3 . . 1 . . 5 .',
            '. . 9 . . . 2 . .',
            '7 . . 1 . 6 . . 9',
            '. 2 . . . . . 8 .',
            '1 . . 4 . 9 . . 3',
            '. . 8 . . . 1 . .',
            '. 5 . . 9 . . 7 .',
            '. . . 7 . 4 . . .',
         ]), "\n".join([
            '5 4 2 6 7 3 9 1 8',
            '8 3 7 9 1 2 4 5 6',
            '6 1 9 5 4 8 2 3 7',
            '7 8 3 1 2 6 5 4 9',
            '9 2 4 3 5 7 6 8 1',
            '1 6 5 4 8 9 7 2 3',
            '3 7 8 2 6 5 1 9 4',
            '4 5 6 8 9 1 3 7 2',
            '2 9 1 7 3 4 8 6 5',
         ])),
    ])
    @pytest.mark.timeout(65)  # provide some leeway for initialization
    def test_solve(self, puzzle, solution):
        puzzle = _create_puzzle_from_string(puzzle)

        backtracking = sudoku.Backtracking()
        backtracking.solve(puzzle)

        solution = _create_puzzle_from_string(solution)
        _assert_puzzles_equal(puzzle, solution)


@mock.patch.object(sudoku.Backtracking, 'solve')
@mock.patch.object(sudoku.Puzzle, 'load')
@mock.patch('builtins.print')
@pytest.mark.integration
def test_main(mock_print, mock_load, mock_solve):
    puzzle = _create_incomplete_puzzle()
    mock_load.return_value = puzzle

    sudoku.main(['sudoku.py', 'fake-path'])
    mock_load.assert_called_once_with('fake-path')
    mock_solve.assert_called_once_with(puzzle)
    mock_print.assert_called_once_with(puzzle)


# support running this file directly (e.g., within an IDE)
if '__main__' == __name__:
    pytest.main()
