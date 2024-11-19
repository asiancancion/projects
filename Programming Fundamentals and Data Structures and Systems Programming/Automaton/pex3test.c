/** pex3test.h
 * =============================================================
 * Name: Caleb Song, 11/07/22
 * Section:  T6 Sample
 * Project:  PEX 3 - Automaton
 * Purpose:  Test createBoard, copyBoard, compareBoards, updateBoard functions
 * ============================================================= */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "pex3test.h"
#include "pex3functs.h"
void runAllTests() {
    testCreateBoard();
    testCopyBoard();
    testCompareBoards();
    testUpdateBoard();
    //If all functions pass tests, prints "all tests passed"
    printf("All tests passed!\n");
}


void testCreateBoard(){
    int rows;
    int cols;
    rows = 10;
    cols = 11;
    //shows the middle card of top row is Filled
    assert(createBoard(rows, cols)[0][5] == FILLED);
    //Test rows 2-10 to be blank
    for (int i =1; i< rows; i++){
        for (int j=0; j<cols;j++){
        assert(createBoard(rows, cols)[i][j] == BLANK);
        }
    }
    //Test row 1 from columns 0 to 4 to be blank
    for (int j=0; j<5;j++){
        assert(createBoard(rows, cols)[0][j] == BLANK);
    }
    //Test row 1 from columns 0 to 4 to be blank
    for (int j=6; j<cols;j++){
        assert(createBoard(rows, cols)[0][j] == BLANK);
    }
}

void testCopyBoard(){
    int rows = 10;
    int cols = 11;
    char** board1 = createBoard(rows,cols);
    //shows the middle card of top row is Same and filled
    assert(copyBoard(board1, rows, cols)[0][5] == FILLED);
    assert(copyBoard(board1, rows, cols)[0][5] == board1[0][5]);
    //Test rows 2-10 to be blank
    for (int i =1; i< rows; i++){
        for (int j=0; j<cols;j++){
        assert(createBoard(rows, cols)[i][j] == BLANK);
        assert(copyBoard(board1, rows, cols)[i][j] == board1[i][j]);
        }
    }
    //Test row 1 from columns 0 to 4 to be same and blank
    for (int j=0; j<5;j++){
        assert(createBoard(rows, cols)[0][j] == BLANK);
        assert(copyBoard(board1, rows, cols)[0][j] == board1[0][j]);
    }
    //Test row 1 from columns 0 to 4 to be same blank
    for (int j=6; j<cols;j++){
        assert(createBoard(rows, cols)[0][j] == BLANK);
        assert(copyBoard(board1, rows, cols)[0][j] == board1[0][j]);
    }

}

void testCompareBoards(){
    int rows = 10;
    int cols = 11;
    char** board1 = createBoard(rows,cols);
    char** board2 = createBoard(rows, cols);
    //shows that identical boards returns 0
    assert(compareBoards(board1, board2, rows, cols) == 0);
    //changing board1
    board1 = updateBoard(board1, 94, rows, cols);
    //shows that changed board does not return 0
    assert(compareBoards(board1, board2, rows, cols) != 0);
}

void testUpdateBoard(){
    int rows = 10;
    int cols = 11;
    char** board1 = createBoard(rows,cols);
    //For even automata 90 after first iteration shows that under the middle two sides are filled
    assert(updateBoard(board1, 90, rows, cols)[1][4] == FILLED);
    board1 = createBoard(rows,cols);
    assert(updateBoard(board1, 90, rows, cols)[1][6] == FILLED);
    board1 = createBoard(rows,cols);

    //For odd automata 95 shows that after first iteration all but sides are filled
    for (int i =1; i< cols-1; i++){
        assert(updateBoard(board1, 95, rows, cols)[1][i] == FILLED);
        board1 = createBoard(rows,cols);
    }
}