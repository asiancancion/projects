
# Tromino Tiling Algorithm Implementation

## Project Overview
This program solves the **Tromino Tiling Problem** using a divide-and-conquer approach. It tiles a \( 2```k \times 2```k \) grid with one forbidden cell using L-shaped trominoes. The solution is visualized with a graphical representation.

---

## Problems and Solutions

### Problem 1: Checking for Forbidden Cells in a Sub-grid
#### Problem Description
- Determine if a given sub-grid of the board contains a forbidden cell.
- Input: Starting and ending row/column indices of the sub-grid.
- Output: Boolean value indicating whether a forbidden cell exists.

#### Approach
- Iterate through the rows and columns of the specified sub-grid.
- Return `true` if a forbidden cell is found; otherwise, return `false`.

#### Code:
```
boolean containsForbidden(int startRow, int endRow, int startCol, int endCol) {
    for (int i = startRow; i <= endRow; i++) {
        for (int j = startCol; j <= endCol; j++) {
            if (trominoBoard[i][j]) {
                return true;
            }
        }
    }
    return false;
}
```

---

### Problem 2: Tiling the Board with Trominoes
#### Problem Description
- Recursively tile the board using trominoes:
  - Divide the grid into four quadrants.
  - Check for forbidden cells in each quadrant.
  - Place a tromino in the center of the grid to cover three quadrants without a forbidden cell.
  - Recursively tile each quadrant.

#### Approach
1. **Base Case**: If the grid size is \( 1 \times 1 \), the cell is filled directly.
2. **Recursive Case**:
   - Calculate the middle row and column.
   - For each quadrant:
     - If it contains the forbidden cell, recursively tile it.
     - Otherwise, place a tromino to create a new forbidden cell and recursively tile it.
   - Display the tromino on the graphical panel.

#### Code:
```
void doTiling(int startRow, int endRow, int startCol, int endCol) {
    Color trominoColor = new Color(rand.nextInt(255), rand.nextInt(255), rand.nextInt(255));
    int size = (endRow + 1) - startRow;

    if (size == 1) {
        g.setColor(Color.BLACK);
        g.fillRect(startCol * cellSize, startRow * cellSize, cellSize, cellSize);
    } else {
        int middleRow = (startRow + endRow) / 2;
        int middleCol = (startCol + endCol) / 2;

        // Top-right quadrant
        if (containsForbidden(startRow, middleRow, middleCol + 1, endCol)) {
            doTiling(startRow, middleRow, middleCol + 1, endCol);
        } else {
            setForbiddenCell(middleRow, middleCol + 1);
            doTiling(startRow, middleRow, middleCol + 1, endCol);
            g.setColor(trominoColor);
            g.fillRect((middleCol + 1) * cellSize, middleRow * cellSize, cellSize, cellSize);
            panel.copyGraphicsToScreen();
        }

        // Top-left quadrant
        if (containsForbidden(startRow, middleRow, startCol, middleCol)) {
            doTiling(startRow, middleRow, startCol, middleCol);
        } else {
            setForbiddenCell(middleRow, middleCol);
            doTiling(startRow, middleRow, startCol, middleCol);
            g.setColor(trominoColor);
            g.fillRect(middleCol * cellSize, middleRow * cellSize, cellSize, cellSize);
            panel.copyGraphicsToScreen();
        }

        // Bottom-left quadrant
        if (containsForbidden(middleRow + 1, endRow, startCol, middleCol)) {
            doTiling(middleRow + 1, endRow, startCol, middleCol);
        } else {
            setForbiddenCell(middleRow + 1, middleCol);
            doTiling(middleRow + 1, endRow, startCol, middleCol);
            g.setColor(trominoColor);
            g.fillRect(middleCol * cellSize, (middleRow + 1) * cellSize, cellSize, cellSize);
            panel.copyGraphicsToScreen();
        }

        // Bottom-right quadrant
        if (containsForbidden(middleRow + 1, endRow, middleCol + 1, endCol)) {
            doTiling(middleRow + 1, endRow, middleCol + 1, endCol);
        } else {
            setForbiddenCell(middleRow + 1, middleCol + 1);
            doTiling(middleRow + 1, endRow, middleCol + 1, endCol);
            g.setColor(trominoColor);
            g.fillRect((middleCol + 1) * cellSize, (middleRow + 1) * cellSize, cellSize, cellSize);
            panel.copyGraphicsToScreen();
        }
    }
}
```

---
