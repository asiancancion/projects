# PEX0 - C Proficiency

## Project Overview
This project is a basic C program designed to test proficiency in using C language constructs such as arrays, pointers, linked lists, and dynamic memory allocation. The program demonstrates handling of command-line arguments, loops, function usage, and basic linked list operations.

## Features
- **Command-Line Argument Handling**: The program accepts command-line arguments and prints the first argument passed.
- **Looping and Conditions**: It prints numbers from 1 to 20 that are divisible by 3.
- **Function Call**: The program defines a function (`func1`) that accepts an integer array and returns the first element multiplied by 2.
- **Linked List Implementation**: A basic linked list with statically and dynamically allocated nodes.
- **Dynamic Memory Allocation**: Demonstrates memory allocation for a node using `malloc`.

## Code Explanation

### func1
This function accepts an integer array as a parameter and returns the first element multiplied by 2.
```c
int func1(int array[]) {
    return (array[0] * 2);
}
