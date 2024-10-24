# Vector Calculator

## Project Overview
The **Vector Calculator** is a command-line utility written in Java that allows users to perform various vector operations, including addition, subtraction, dot product, normalization, magnitude calculation, direction finding, and scaling. The program runs in an infinite loop until the user inputs `exit`, prompting for vector expressions and executing operations accordingly.

## Features
- **Vector Addition and Subtraction**: Add or subtract two vectors.
- **Dot Product**: Compute the dot product of two vectors.
- **Magnitude Calculation**: Compute the magnitude (or norm) of a vector.
- **Vector Normalization**: Normalize a vector to make its magnitude 1.
- **Vector Direction**: Compute the direction (angle) of a vector in both radians and degrees.
- **Vector Scaling**: Scale a vector by a scalar value.

## Usage Instructions

### Commands
1. **Addition and Subtraction**: 
   - Syntax: `<x1, y1> + <x2, y2>` or `<x1, y1> - <x2, y2>`
   - Example: `<3, 4> + <1, 2>` results in `<4, 6>`
   
2. **Dot Product**:
   - Syntax: `<x1, y1> . <x2, y2>`
   - Example: `<3, 4> . <1, 2>` results in `11`
   
3. **Magnitude**:
   - Syntax: `|<x, y>|`
   - Example: `|<3, 4>|` results in `5.00000`
   
4. **Normalization**:
   - Syntax: `unit <x, y>`
   - Example: `unit <3, 4>` results in `<0.60000, 0.80000>`
   
5. **Direction (Angle)**:
   - Syntax: `dir <x, y>`
   - Example: `dir <1, 1>` results in `0.78540 radians (45.00000 degrees)`
   
6. **Scaling**:
   - Syntax: `scale * <x, y>`
   - Example: `2 * <3, 4>` results in `<6, 8>`

### Example of Usage
Upon running the program, it will prompt for input:

Enter vector expression: <3, 4> + <1, 2> Result is <4, 6>

Enter vector expression: |<3, 4>| Result is 5.00000

Enter vector expression: exit Thank you for using the Vector Calculator. Goodbye.



## Code Explanation

### `VectorCalc(Scanner s)`
This method runs the vector calculator in an infinite loop, prompting the user for input until the user types `exit`. It takes a `Scanner` object as a parameter to read the user's input and parses the expression using the `parseExpression()` method.

### `parseExpression(Scanner s)`
This method parses the user input to determine the operation. It handles the following operations:
- **Magnitude** (`|vector|`)
- **Addition, Subtraction, Dot Product** (`<vector1> + <vector2>`, etc.)
- **Scaling** (e.g., `2 * <vector>`)
- **Direction** (`dir <vector>`)
- **Normalization** (`unit <vector>`)

### Helper Methods
- `parseDirectionExpression()`: Parses a vector and prints the direction in radians and degrees.
- `parseNormalizeExpression()`: Parses and normalizes a vector.
- `parseNormExpression()`: Parses a vector and prints its magnitude.
- `parseScaleExpression()`: Parses a vector and scales it by a scalar.
- `parseVectorExpression()`: Parses two vectors and performs addition, subtraction, or dot product based on the operator provided.


## Error Handling
If the user enters an invalid expression or syntax, the program will catch the exception and print an error message. Example:

