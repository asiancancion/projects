# N-Queens Problem

## Project Overview
This program solves the **N-Queens Problem** using a backtracking algorithm. The objective is to place \( n \) queens on an \( n \times n \) chessboard such that no two queens threaten each other. The program:
1. Finds all possible solutions.
2. Counts the number of promising nodes (nodes that lead to valid partial solutions).
3. Calculates the total number of nodes in the search tree.
4. Computes the ratio of promising nodes to total nodes.
5. Tracks the runtime of the algorithm.

---

## Problems and Solutions

### Problem 1: Solving the N-Queens Problem
#### Problem Description
- Place \( n \) queens on an \( n \times n \) board.
- Ensure no two queens:
  1. Share the same row.
  2. Share the same column.
  3. Lie on the same diagonal.

#### Approach
1. Use a recursive backtracking algorithm.
2. At each step:
   - Check if placing a queen in the current column is **promising**.
   - If promising, recursively attempt to place queens in subsequent columns.
3. Stop when all queens are placed on the board.

#### Code:
```
public static void queens(int i) {
    int j;
    if (promising(i)) {
        if (i == n) {
            counter += 1;  // Increment the solution count
        } else {
            for (j = 1; j <= n; j++) {
                col[i + 1] = j;  // Place queen
                queens(i + 1);   // Recurse to the next column
            }
        }
    }
}
```

---

### Problem 2: Checking for Promising Nodes
#### Problem Description
- A position is promising if placing a queen in the current column does not threaten any previously placed queens.

#### Approach
1. Iterate through previously placed queens.
2. Check:
   - If they share the same column.
   - If they lie on the same diagonal.
3. If promising, increment the **promising node counter**.

#### Code:
```
public static boolean promising(int i) {
    boolean condition = true;
    int k = 1;
    while (k < i && condition) {
        if (col[i] == col[k] || Math.abs(col[i] - col[k]) == i - k) {
            condition = false;
        }
        k++;
    }
    if (condition) {
        promisingCounter += 1;
    }
    return condition;
}
```

---

### Problem 3: Tracking Runtime and Statistics
#### Problem Description
- Track the runtime of the algorithm in nanoseconds.
- Compute the total number of nodes in the search tree:
  \[
  \text{numberNodes} = \frac{n```{n+1} - 1}{n - 1}
  \]
- Compute the ratio of promising nodes to total nodes.
