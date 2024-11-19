#!/usr/bin/env python
#Documentation: Looked up how to separate a string every nth character and used it to split string into arrays and then split those arrays and how to rejoin
#               on the Internet. Got EI from Maj Birrer 11/28 because I was lowkey going crazy with the faces and orientation and he helped me fix my faces.

class Cube:

    def __init__(self, colors=' '.join([c * 9 for c in 'WGRBOY'])):
        #create cube from 54 character string
        self.cube = colors
        #remove all spaces from 54 character string
        separate = self.cube.replace(" ","")
        #split string every 9 characters into arrays
        cubeletsSplit = [separate[i:i+9] for i in range(0, len(separate), 9)]
        #split the 9 characters in each array
        self.cubelets = [list(cubeletsSplit) for cubeletsSplit in cubeletsSplit]

    def __str__(self):
        #join arrays into 54 character string so it is ready to be printed
        faces = [''.join(face) for face in self.cubelets]
        self.cube = ''.join(faces)
        return self.cube

    def get_color_at(self,face, row, column):
        #Create array of faces
        faces = ["U","L","F","R","B","D"]
        error = True
        #Check for Invalid Face
        for i in range (6):
            if (faces[i] == face):
                error = False
        #Raise error for Invalid Face
        if (error == True):
            raise ValueError
        #Raise error for out of bounds index
        if (row > 3 or row < 1 or column > 3 or column < 1):
            raise IndexError
        #remove all of the spaces from 54 character string
        separate = self.cube.replace(" ","")
        index = faces.index(face)
        #get index from 54 character string based on row number + column number + what face
        indexFace = ((row-1)*3) + (column-1) + (index*9)
        return separate[indexFace] 

    def move(self,face, clockwise):
        #if clockwise is true run move function once, if it is counter clockwise run
        #move function 3 times
        #check for front face
        if (face == "F"):
            if (clockwise == True):
                self._move_front()
            elif (clockwise == False):
                self._move_front()
                self._move_front()
                self._move_front()
        #check for left face
        elif (face == "L"):
            if (clockwise == True):
                self._move_left()
            elif (clockwise == False):
                self._move_left()
                self._move_left()
                self._move_left()
        #check for right face
        elif (face == "R"):
            if (clockwise == True):
                self._move_right()
            elif (clockwise == False):
                self._move_right()
                self._move_right()
                self._move_right()
        #check for up (top) face
        elif (face == "U"):
            if (clockwise == True):
                self._move_up()
            elif (clockwise == False):
                self._move_up()
                self._move_up()
                self._move_up()
        #check for down (bottom) face
        elif (face == "D"):
            if (clockwise == True):
                self._move_down()
            elif (clockwise == False):
                self._move_down()
                self._move_down()
                self._move_down()
        #check for back face
        elif (face == "B"):
            if (clockwise == True):
                self._move_back()
            elif (clockwise == False):
                self._move_back()
                self._move_back()
                self._move_back()
        #Convert arrays back into 54 character string
        Cube.__str__(self)
    
    def _move_front(self):
        #rotate front face
        self.cubelets[2][0],self.cubelets[2][1],self.cubelets[2][2],self.cubelets[2][3],self.cubelets[2][5],self.cubelets[2][6],self.cubelets[2][7],self.cubelets[2][8] = \
        self.cubelets[2][6],self.cubelets[2][3],self.cubelets[2][0],self.cubelets[2][7],self.cubelets[2][1],self.cubelets[2][8],self.cubelets[2][5],self.cubelets[2][2]
        #rotate cubelets connected to front face
        self.cubelets[0][6],self.cubelets[0][7],self.cubelets[0][8],self.cubelets[1][2],self.cubelets[1][5],self.cubelets[1][8],self.cubelets[3][0],self.cubelets[3][3],self.cubelets[3][6],self.cubelets[5][0],self.cubelets[5][1],self.cubelets[5][2] = \
        self.cubelets[1][8],self.cubelets[1][5],self.cubelets[1][2],self.cubelets[5][0],self.cubelets[5][1],self.cubelets[5][2],self.cubelets[0][6],self.cubelets[0][7],self.cubelets[0][8],self.cubelets[3][6],self.cubelets[3][3],self.cubelets[3][0]

    def _move_left(self):
        #rotate left face
        self.cubelets[1][0],self.cubelets[1][1],self.cubelets[1][2],self.cubelets[1][3],self.cubelets[1][5],self.cubelets[1][6],self.cubelets[1][7],self.cubelets[1][8] = \
        self.cubelets[1][6],self.cubelets[1][3],self.cubelets[1][0],self.cubelets[1][7],self.cubelets[1][1],self.cubelets[1][8],self.cubelets[1][5],self.cubelets[1][2]
        #rotate cubelets connected to left face
        self.cubelets[0][0],self.cubelets[0][3],self.cubelets[0][6],self.cubelets[2][0],self.cubelets[2][3],self.cubelets[2][6],self.cubelets[5][0],self.cubelets[5][3],self.cubelets[5][6],self.cubelets[4][2],self.cubelets[4][5],self.cubelets[4][8] = \
        self.cubelets[4][8],self.cubelets[4][5],self.cubelets[4][2],self.cubelets[0][0],self.cubelets[0][3],self.cubelets[0][6],self.cubelets[2][0],self.cubelets[2][3],self.cubelets[2][6],self.cubelets[5][6],self.cubelets[5][3],self.cubelets[5][0]

    def _move_right(self):
        #rotate right face
        self.cubelets[3][0],self.cubelets[3][1],self.cubelets[3][2],self.cubelets[3][3],self.cubelets[3][5],self.cubelets[3][6],self.cubelets[3][7],self.cubelets[3][8] = \
        self.cubelets[3][6],self.cubelets[3][3],self.cubelets[3][0],self.cubelets[3][7],self.cubelets[3][1],self.cubelets[3][8],self.cubelets[3][5],self.cubelets[3][2]   
        #rotate cubelets connected to right face
        self.cubelets[0][2],self.cubelets[0][5],self.cubelets[0][8],self.cubelets[4][0],self.cubelets[4][3],self.cubelets[4][6],self.cubelets[5][2],self.cubelets[5][5],self.cubelets[5][8],self.cubelets[2][2],self.cubelets[2][5],self.cubelets[2][8] = \
        self.cubelets[2][2],self.cubelets[2][5],self.cubelets[2][8],self.cubelets[0][8],self.cubelets[0][5],self.cubelets[0][2],self.cubelets[4][6],self.cubelets[4][3],self.cubelets[4][0],self.cubelets[5][2],self.cubelets[5][5],self.cubelets[5][8]

    def _move_up(self):
        #rotate up (top) face
        self.cubelets[0][0],self.cubelets[0][1],self.cubelets[0][2],self.cubelets[0][3],self.cubelets[0][5],self.cubelets[0][6],self.cubelets[0][7],self.cubelets[0][8] = \
        self.cubelets[0][6],self.cubelets[0][3],self.cubelets[0][0],self.cubelets[0][7],self.cubelets[0][1],self.cubelets[0][8],self.cubelets[0][5],self.cubelets[0][2]
        #rotate cubelets connected to up face
        self.cubelets[1][0],self.cubelets[1][1],self.cubelets[1][2],self.cubelets[2][0],self.cubelets[2][1],self.cubelets[2][2],self.cubelets[3][0],self.cubelets[3][1],self.cubelets[3][2],self.cubelets[4][2],self.cubelets[4][1],self.cubelets[4][0] = \
        self.cubelets[2][0],self.cubelets[2][1],self.cubelets[2][2],self.cubelets[3][0],self.cubelets[3][1],self.cubelets[3][2],self.cubelets[4][0],self.cubelets[4][1],self.cubelets[4][2],self.cubelets[1][2],self.cubelets[1][1],self.cubelets[1][0]

    def _move_down(self):
        #rotate down (bottom) face
        self.cubelets[5][0],self.cubelets[5][1],self.cubelets[5][2],self.cubelets[5][3],self.cubelets[5][5],self.cubelets[5][6],self.cubelets[5][7],self.cubelets[5][8] = \
        self.cubelets[5][6],self.cubelets[5][3],self.cubelets[5][0],self.cubelets[5][7],self.cubelets[5][1],self.cubelets[5][8],self.cubelets[5][5],self.cubelets[5][2]
        #rotate cubelets connected to down face
        self.cubelets[2][6],self.cubelets[2][7],self.cubelets[2][8],self.cubelets[1][6],self.cubelets[1][7],self.cubelets[1][8],self.cubelets[4][8],self.cubelets[4][7],self.cubelets[4][6],self.cubelets[3][6],self.cubelets[3][7],self.cubelets[3][8] = \
        self.cubelets[1][6],self.cubelets[1][7],self.cubelets[1][8],self.cubelets[4][6],self.cubelets[4][7],self.cubelets[4][8],self.cubelets[3][8],self.cubelets[3][7],self.cubelets[3][6],self.cubelets[2][6],self.cubelets[2][7],self.cubelets[2][8]
        
    def _move_back(self):
        #rotate back face
        self.cubelets[4][0],self.cubelets[4][1],self.cubelets[4][2],self.cubelets[4][3],self.cubelets[4][5],self.cubelets[4][6],self.cubelets[4][7],self.cubelets[4][8] = \
        self.cubelets[4][6],self.cubelets[4][3],self.cubelets[4][0],self.cubelets[4][7],self.cubelets[4][1],self.cubelets[4][8],self.cubelets[4][5],self.cubelets[4][2]
        #rotate cubelets connected to back face
        self.cubelets[0][0],self.cubelets[0][1],self.cubelets[0][2],self.cubelets[1][0],self.cubelets[1][3],self.cubelets[1][6],self.cubelets[5][6],self.cubelets[5][7],self.cubelets[5][8],self.cubelets[3][2],self.cubelets[3][5],self.cubelets[3][8] = \
        self.cubelets[3][2],self.cubelets[3][5],self.cubelets[3][8],self.cubelets[0][2],self.cubelets[0][1],self.cubelets[0][0],self.cubelets[1][0],self.cubelets[1][3],self.cubelets[1][6],self.cubelets[5][8],self.cubelets[5][7],self.cubelets[5][6] 
        

    def print_cube(self):
        #print up face
        tracker = 0
        for i in range(3):
            print("        ", end= " ")
            for j in range(3):
                print(self.cubelets[0][tracker], end= " ")
                tracker+=1
            print()
        print()
        #print left, front, right, back faces
        #reset tracker
        tracker = 0
        for i in range(3):
            #print left face
            for j in range(3):
                print(self.cubelets[1][tracker], end= " ")
                tracker+=1
            print("  ", end = " ")
            #subtract tracker by 3
            tracker-= 3
            #print front face
            for j in range(3):
                print(self.cubelets[2][tracker], end= " ")
                tracker+=1
            print("  ", end = " ")
            tracker-= 3
            #print left face
            for j in range(3):
                print(self.cubelets[3][tracker], end= " ")
                tracker+=1
            print("  ", end = " ")
            tracker-= 3
            #print right face
            for j in range(3):
                print(self.cubelets[4][tracker], end= " ")
                tracker+=1
            print("  ", end = " ")
            print()
        print()
        #print down face
        #print up face
        tracker = 0
        for i in range(3):
            print("        ", end= " ")
            for j in range(3):
                print(self.cubelets[5][tracker], end= " ")
                tracker+=1
            print()
        print()

def main(args):
    #get file to read in cube
    input_cube = open(args[1], 'r')
    contents = input_cube.read()
    #read in the moves and Rubik's cube as an array
    lines = contents.split('\n')
    #remove the blank spaces in array
    lines.remove('')
    #grab the first line which is the Rubik's Cube 54 character string
    cube = Cube(lines.pop(0))
    loop = True
    #loop through all the moves until the array of moves is empty
    while (loop == True):
        if (len(lines) == 0):
            break
        #get the next move
        next_move = lines.pop(0)
        #if the length of the string of the next move is 2 then it is a counterclockwise rotation
        if (len(next_move) == 2):
            cube.move(next_move[0],clockwise=False)
        #else it is a clockwise rotation
        else:
            cube.move(next_move,clockwise=True)
    cube.print_cube()    

if '__main__' == __name__:
    import sys
    main(["sudoku.py","puzzles/all-rotations-counterclockwise.txt"]) #run main with filename of puzzle
