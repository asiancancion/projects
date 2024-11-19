#!/usr/bin/env python
# Documentation: Watched this video:
# https://www.youtube.com/watch?v=tvP_FZ-D9Ng
# for a general overview and used it to write some comments on 
# what to do, Got EI from Maj Birrer where I figured out that I read
# the table first as strings so my comparisons didn't work, 
# Used copilot for autocomplete like when I had to replicate functions,
# looked on tutorials point and w3schools for syntax
import abc


class Puzzle:

    def __init__(self):
        # intialize 9x9 board with dots
        self.board = [['.' for i in range (9)] for j in range (9)] 
    
    @staticmethod
    def load(path):
        new_puzzle = Puzzle()
        input_board = open(path, 'r')
        contents = input_board.read()
        lines = contents.split('\n')
        for i in range(9):
            for j in range(9):
                #if the value is a dot, set it to a dot
                if (lines[i].strip().split(' ')[j] == '.'): 
                    new_puzzle.board[i][j] = lines[i].strip().split(' ')[j]
                #if the value is not a dot, set it to an int
                else:
                    new_puzzle.board[i][j] = int(lines[i].strip().split(' ')[j])
        input_board.close()
        return new_puzzle
    
    def set_value(self,row, col, value):
        # user will input a 1 if they want it in the first row, but the first row is actually 0
        # same for column user will input 1 for first column, but it is actually 0
        if(row > 0 and row < 10 and col > 0 and col < 10): #check to see if the row and col are valid
            self.board[row-1][col-1] = value #set them to the value
        else:
            raise IndexError #raise index error if not in range
    
    def get_value(self,row,col):
        # user will input a 1 if they want it in the first row, but the first row is actually 0
        # same for column user will input 1 for first column, but it is actually 0
        if (row > 0 and row < 10 and col > 0 and col < 10): #check to see if row and col are valid
            return self.board[row-1][col-1]
        else:
            raise IndexError #raise index error if not in range

    #final check at the end of the program to see if the puzzle is solved
    def is_solved(self):
        #check to see if there are any empty spots
        for i in range(9):
            for j in range(9):
                if self.board[i][j] == '.':
                    return False
        #check for duplicates in a row
        for i in range(1,10):
            row = []
            for j in range (1,10):
                if(Puzzle.get_value(self,i,j) != "."):
                    row.append(Puzzle.get_value(self,i,j))
            if (len(set(row)) != 9):
                return False
        #check for duplicates in a column
        for i in range(1,10):
            row = []
            for j in range (1,10):
                if(Puzzle.get_value(self,j,i) != "."):
                    row.append(Puzzle.get_value(self,j,i))
            if (len(set(row)) != 9):
                return False
        #check for duplicates in all 3x3 squares
        for k in range(0,3):
            for l in range(0,3):
                square = []
                for i in range(3*k,3*k+3):
                    for j in range(3*l,3*l+3):
                        if (Puzzle.get_value(self,i+1,j+1) != "."):
                            square.append(Puzzle.get_value(self,i+1,j+1))
                if (len(set(square)) != 9):
                    return False
        return True
    
    def is_valid(self):
        #if all empty return True
        for k in range(1,10):
            for l in range(1,10):
                if Puzzle.get_value(self,k,l) != ".":
                    break
                if (k==9 and l==9):
                    return True
        #check rows for duplicates
        for i in range(1,10):
            row = []
            for j in range (1,10):
                if(Puzzle.get_value(self,i,j) != "." and Puzzle.get_value(self,i,j) != None):
                        row.append(Puzzle.get_value(self,i,j))
            if (len(set(row)) != len(row)):
                return False
        #check cols for duplicates
        for i in range(1,10):
            row = []
            for j in range (1,10):
                if(Puzzle.get_value(self,j,i) != "." and Puzzle.get_value(self,j,i) != None):
                    row.append(Puzzle.get_value(self,j,i))
            if (len(set(row)) != len(row)):
                return False
        #check box for duplicates
        for k in range(0,3):
            for l in range(0,3):
                square = []
                for i in range(3*k,3*k+3):
                    for j in range(3*l,3*l+3):
                        if (Puzzle.get_value(self,i+1,j+1) != "."):
                            square.append(Puzzle.get_value(self,i+1,j+1))
                if (len(set(square)) != len(square)):
                    return False
        return True
    
    def __str__(self):
        return_string = ""
        for i in range(9):
            for j in range(9):
                return_string += str(self.board[i][j])
                return_string += " "
            return_string += "\n"
        #return a table of the board
        return return_string


class Solver(abc.ABC):

    @abc.abstractmethod
    def solve(self, puzzle):
        raise NotImplementedError
    

class Backtracking(Solver):

    def find_next(puzzle):
        #go through the board and find the next empty spot
        for i in range(0,9):
            for j in range(0,9):
                #if the spot is empty return the row and col
                if puzzle.board[i][j] == '.':
                    return i,j
        #if there are no empty spots return -1,-1
        return -1,-1
    
    def solve(self,puzzle):
        #find the next empty spot
        row,col = Backtracking.find_next(puzzle)
        #if there are no empty spots run Puzzle.is_solved
        if row == -1:
            return Puzzle.is_solved(puzzle)
        #if there are empty spots, try to fill them in starting with row 1 col 1
        for i in range(1,10):
            Puzzle.set_value(puzzle,row+1,col+1,i) #set the value to i
            if Puzzle.is_valid(puzzle): #check to see if it is valid
                if Backtracking.solve(self,puzzle): #if it is valid, recurse
                    return True #if it is solved return true
        Puzzle.set_value(puzzle,row+1,col+1,'.') #if it is not valid, set the value back to a dot
        return False #return false if it is an Unsolvable puzzle
       

def main(args):
    newPuzzle = Puzzle() #create new Puzzle object
    newPuzzle = Puzzle.load(args[1]) #load the puzzle from the file
    backtracking = Backtracking() #create new Backtracking object
    if (backtracking.solve(newPuzzle)): #if the puzzle is solvable, print it
        print(newPuzzle) #print the puzzle
    else:
        print("Unsolvable") #if the puzzle is not solvable, print Unsolvable
    

if "__main__" == __name__:
    import sys
    main(["sudoku.py","data/puzzle.txt"]) #run main with the file name