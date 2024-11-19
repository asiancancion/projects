# PEX1 Air Force Shell (AFSH)

## Project Overview
This project is a simple shell implementation called **Air Force Shell (AFSH)**. It supports both built-in commands and external commands. The shell accepts user input, processes it, and can handle commands such as changing directories, printing command history, and recalling past commands.

## Features
- **Built-in Commands**:
  - `cd [directory]`: Changes the current working directory. Supports `~` for home directory.
  - `exit`: Exits the shell.
  - `history`: Displays a list of previously entered commands. 
    - Supports displaying a limited number of history entries by providing an optional argument (e.g., `history 5`).
  - `recall [number]`: Recalls a specific command from the history by its index.

- **External Commands**:
  - The shell can execute external commands by forking a new process and using the `execvp` system call to replace the child process with the desired command.
  
- **Command History**:
  - The shell maintains a list of previous commands and avoids duplicating consecutive commands in the history.
  
## Prerequisites
To compile and run this program, you'll need:
- A C compiler (e.g., GCC)
- Basic familiarity with terminal commands

## How to Compile and Run
### Compilation
Use the following command to compile the program:

```bash
gcc -o afsh main.c historyList.c -lpthread
