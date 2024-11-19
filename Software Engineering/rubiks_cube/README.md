# Rubik's Cube Solver and Tester

## Project Overview
This project implements a **Rubik's Cube simulator** in Python that supports basic operations like face rotations (clockwise and counterclockwise). Additionally, it provides a unit testing suite to verify the correctness of cube operations and transformations. The project uses Python's **unittest** and **pytest** frameworks for validation.

## Features

### Rubik's Cube Class
- **Cube Representation**: The Rubik's Cube is modeled as a 3D structure with six faces, each containing a 3x3 grid of cubelets.
- **Initialization**: Supports initialization from a 54-character string representing cubelet colors.
- **Face Operations**:
  - Rotate faces clockwise and counterclockwise.
  - Update adjacent cubelets when a face rotates.
- **Validation**:
  - Retrieve specific cubelet colors for a given face and position.
  - Raise appropriate errors for invalid operations.
- **String Representation**: Convert the cube back to its 54-character string for output or debugging.
- **Printing**: Visually display the cube's state.

### Rubik's Cube Tester
- **Unit Tests**:
  - Validate basic operations like `get_color_at` and face rotations.
  - Test cube state after transformations.
- **Integration Tests**:
  - Simulate sequences of moves and validate final cube state.
  - Check if the cube returns to its solved state after a set of operations.

---

## Code Breakdown

### Cube Class
#### Initialization
Initializes a Rubik's Cube from a 54-character string:
```
class Cube:
    def __init__(self, colors=' '.join([c * 9 for c in 'WGRBOY'])):
        self.cube = colors
        separate = self.cube.replace(" ", "")
        cubeletsSplit = [separate[i:i+9] for i in range(0, len(separate), 9)]
        self.cubelets = [list(cubeletsSplit) for cubeletsSplit in cubeletsSplit]
```

#### Face Operations
Rotate faces and update adjacent cubelets:
```
def _move_front(self):
    # Rotate front face
    self.cubelets[2][0], self.cubelets[2][1], self.cubelets[2][2], ... = \
        self.cubelets[2][6], self.cubelets[2][3], self.cubelets[2][0], ...
```

#### String Representation
Convert the cube into a 54-character string:
```
def __str__(self):
    faces = [''.join(face) for face in self.cubelets]
    self.cube = ''.join(faces)
    return self.cube
```

### Main Function
Simulate cube moves from an input file:
```
def main(args):
    input_cube = open(args[1], 'r')
    contents = input_cube.read()
    lines = contents.split('\n')
    lines.remove('')
    cube = Cube(lines.pop(0))
    while len(lines) > 0:
        next_move = lines.pop(0)
        if len(next_move) == 2:
            cube.move(next_move[0], clockwise=False)
        else:
            cube.move(next_move, clockwise=True)
    cube.print_cube()
```

---

## Testing Suite
The `pytest` suite validates the correctness of the cube operations.

### Unit Tests
#### Validate Cube Colors
```
def test_get_color_at(self):
    cube = rubik.Cube()
    _check_cube(cube, dict(zip('ULFRBD', 'WGRBOY')))
```

#### Rotate Faces
Validate the cube's state after face rotations:
```
def test_move(self):
    cube = rubik.Cube()
    cube.move('F', True)
    _check_cube(cube, expected_colors_after_F_rotation)
```

### Integration Tests
#### Apply Move Sequences
Simulate multiple moves and check cube state:
```
@pytest.mark.integration
@pytest.mark.parametrize("configuration,moves", [
    ("GWOGWORRY WWBYGRYGG WWBGRBOYY RWWYBOGBO BBRYOGYOG WRROYROBB",
     "F,R,U,B,L,D".split(',')),
])
def test_moves(configuration, moves):
    cube = rubik.Cube(configuration)
    for move in moves:
        cube.move(move[0], not move.endswith("'"))
    _check_cube(cube, solved_colors)
```

---

## How to Run
### Run the Cube Simulator
To simulate moves from a file:
```
python rubik.py puzzles/moves.txt
```

### Run the Tests
To execute the testing suite:
```
pytest rubik_tests.py
```

This project provides a comprehensive simulation and validation suite for Rubik's Cube operations, ensuring correctness and robustness.

