# LRU Stack-Based Page Replacement Simulation

## Project Overview
This project simulates a **Least Recently Used (LRU)** page replacement algorithm using stack-based operations. The program reads a binary trace file containing memory accesses and calculates the number of page faults for various frame sizes. It supports four different frame sizes and outputs the total number of accesses, the number of page faults, and the miss rate for each frame size.

## Features
- **Memory Trace Reading**: Reads a binary trace file to simulate memory accesses.
- **Page Replacement Policy**: Uses the **Least Recently Used (LRU)** algorithm to manage page references.
- **Frame Size Selection**: The user can choose from four different frame sizes:
  - 512 bytes
  - 1KB
  - 2KB
  - 4KB
- **Page Fault Tracking**: Tracks the number of page faults for each frame size and outputs the miss rate.

## Code Explanation

### Command Line Arguments
The program accepts two command line arguments:
1. The binary trace file to read from.
2. (Optional) The frame size selection, which can be one of:
   - 1: 512 bytes
   - 2: 1KB
   - 3: 2KB
   - 4: 4KB

If the frame size is not provided, the program prompts the user to select one.

### Frame Size Selection
The frame size is selected based on user input or command line argument. The corresponding values for `OFFSET_BITS` and `MAX_FRAMES` are set based on the selected frame size:
```c
switch(menu_option){
    case 1:
        OFFSET_BITS = 9;  // 512 bytes
        MAX_FRAMES = 8192;
        break;
    case 2:
        OFFSET_BITS = 10; // 1KB
        MAX_FRAMES = 4096;
        break;
    case 3:
        OFFSET_BITS = 11; // 2KB
        MAX_FRAMES = 2048;
        break;
    case 4:
        OFFSET_BITS = 12; // 4KB
        MAX_FRAMES = 1024;
        break;
}
```
### LRU Stack Implementation

The program uses a stack-based approach to simulate the LRU page replacement algorithm. The seek_and_remove() function checks if the page is already in the stack and returns the depth (or index) of the page in the stack. If the page is not found, it returns -1.

For each page access:

If the page is not in the stack, a page fault occurs and all current frames have their page fault count incremented.
If the page is found in the stack, only the frames up to the current depth have their fault count incremented.
The page is then pushed to the top of the stack using the push() function.

### Main Loop

The main loop processes each page access from the trace file:

```c
while(!feof(ifp)) {
    fread(&trace_record, sizeof(p2AddrTr), 1, ifp);
    unsigned long page_num = trace_record.addr >> OFFSET_BITS;
    num_accesses++;

    int depth = seek_and_remove(&lruStack, page_num);

    if (depth == -1) {
        for (int i = 0; i < MAX_FRAMES; i++) {
            pageFaults[i]++;
        }
    } else {
        for (int i = 0; i < depth; i++) {
            pageFaults[i]++;
        }
    }

    push(&lruStack, page_num);
}

```
### Output
After processing all accesses, the program outputs the total number of accesses, and for each frame size, the number of page faults and the miss rate:

```c
printf("Total Accesses:,%ld\n", num_accesses);
printf("Frames,Misses,Miss Rate\n");

for (int i = 0; i < MAX_FRAMES; i++) {
    double missRate = (double)pageFaults[i] / num_accesses;
    printf("%d,%lu,%.6f\n", i + 1, pageFaults[i], missRate);
}

```
### Example Output

Total Accesses:,1000000
Frames,Misses,Miss Rate
1,100000,0.100000
2,80000,0.080000
3,70000,0.070000
...

## How to Compile and Run
### Compilation

To compile the program, run the following command:

```c
gcc -o lru_simulator lru_simulator.c byutr.c LRUstack.c
```

### Running the Program

To run the program, you need to provide a binary trace file and optionally a frame size:

```c
./lru_simulator tracefile.byutr 3
```

If no frame size is provided, the program will prompt for input.

###Input Options for Frame Size
512 bytes
1KB
2KB
4KB

### Page Fault Calculation

The program calculates the number of page faults for each frame size based on the LRU replacement policy. The pageFaults[] array tracks the number of faults for each frame size, and the miss rate is calculated as:

```c
double missRate = (double)pageFaults[i] / num_accesses;
```
