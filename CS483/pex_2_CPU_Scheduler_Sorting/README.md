# PEX2 CPU Scheduling Simulation

## Project Overview
This project simulates a multi-CPU scheduling environment using various CPU scheduling algorithms. The program models the behavior of processes arriving at different times, waiting to be executed, and completing according to the selected scheduling algorithm. The primary goal is to allow users to observe the effects of different scheduling algorithms (e.g., FIFO, SJF, Priority, Round Robin) in a simulated system with multiple CPUs.

## Features
- Supports the following CPU scheduling algorithms:
  - **First In First Out (FIFO)**
  - **Shortest Job First (SJF)**
  - **Priority Scheduling (preemptive and non-preemptive)**
  - **Round Robin (RR)**
  - **Shortest Remaining Time First (SRTF)**
- Multi-threaded simulation using POSIX threads (`pthread`).
- Semaphores and mutexes for thread synchronization between CPUs and the main control flow.
- Generates random processes during the simulation with attributes such as priority, burst time, and arrival time.
- Allows for both debug output (for observing queue states) and non-debug output modes.
  
## Prerequisites
To run this program, you'll need the following:
- A C compiler (e.g., GCC)
- POSIX thread library (`pthread`)
- Basic familiarity with terminal commands to execute the program

## How to Compile and Run
### Compilation
Compile the program using the following command:

```bash
gcc -o pex2 main.c -lpthread
