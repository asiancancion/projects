# Sudoku Solver: Backtracking Algorithm Implementation

## Project Overview
This project implements a **Sudoku solver** in Python using the **Backtracking algorithm**. It defines a `Puzzle` class for handling the Sudoku grid and operations, and a `Solver` class hierarchy to encapsulate different solving strategies. The Backtracking algorithm systematically explores all possible solutions to determine if the puzzle can be solved.

## Features

### Puzzle Class
- **Board Representation**: A 9x9 grid initialized with `.` for empty cells.
- **File Loading**: Loads a Sudoku puzzle from a text file with rows separated by newline characters and columns separated by spaces.
- **Set and Get Values**: Methods to set and retrieve values from the grid.
- **Validation**:
  - Ensures the puzzle adheres to Sudoku rules (no duplicates in rows, columns, or 3x3 subgrids).
  - Checks if the puzzle is completely solved.
- **String Representation**: Converts the grid into a human-readable string for easy visualization.

### Solver Class
- **Abstract Base Class (ABC)**: Defines a blueprint for all solving strategies with a `solve()` method.

### Backtracking Class
- Implements the Backtracking algorithm for solving the puzzle:
  - Finds the next empty cell.
  - Tries numbers 1 through 9 in the empty cell.
  - Recursively attempts to solve the puzzle.
  - Backtracks if no solution is found, resetting the cell to empty.
- Efficiently ensures all Sudoku rules are respected during the solving process.

---

## Code Breakdown

### Puzzle Class
#### Initialization
Creates a 9x9 grid filled with dots (`.`) representing empty cells:
```
self.board = [['.' for i in range(9)] for j in range(9)]
```

#### Load Puzzle from File
Loads a Sudoku puzzle from a text file:
```
@staticmethod
def load(path):
    new_puzzle = Puzzle()
    with open(path, 'r') as input_board:
        contents = input_board.read()
        lines = contents.split('\n')
        for i in range(9):
            for j in range(9):
                cell_value = lines[i].strip().split(' ')[j]
                new_puzzle.board[i][j] = int(cell_value) if cell_value != '.' else cell_value
    return new_puzzle
```

#### Validation
Checks for rule compliance:
- Rows, columns, and subgrids have unique non-empty values.
- No conflicts in current board state.

#### Solved Check
Verifies the puzzle is completely solved:
```
def is_solved(self):
    for row in self.board:
        if '.' in row:
            return False
    # Additional checks for rows, columns, and subgrids
    return True
```

### Backtracking Class
#### Find Next Empty Cell
Identifies the next empty cell:
```
def find_next(puzzle):
    for i in range(9):
        for j in range(9):
            if puzzle.board[i][j] == '.':
                return i, j
    return -1, -1
```

#### Solve Using Backtracking
Implements the solving logic:
```
def solve(self, puzzle):
    row, col = Backtracking.find_next(puzzle)
    if row == -1:
        return puzzle.is_solved()
    for num in range(1, 10):
        puzzle.set_value(row + 1, col + 1, num)
        if puzzle.is_valid():
            if self.solve(puzzle):
                return True
    puzzle.set_value(row + 1, col + 1, '.')
    return False
```

### Main Function
Runs the Sudoku solver:
```
if "__main__" == __name__:
    import sys
    main(["sudoku.py", "data/puzzle.txt"])
```
