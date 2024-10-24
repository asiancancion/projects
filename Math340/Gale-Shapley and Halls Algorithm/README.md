# Stable Matching with Gale-Shapley Algorithm

## Project Overview
This project implements a stable matching algorithm using the **Gale-Shapley** algorithm. It processes preferences from CSV files and generates stable pairings, both boy-favored and girl-favored. The project also checks for rogue pairs, verifies stability of pairings, and tests Hall's condition to ensure a perfect matching exists.

## Features
- **Reading Preferences**: Reads the preferences for entities (boys and girls) from CSV files into structured dictionaries.
- **Pairing Algorithms**:
  - **Boy-Favored Pairings**: Uses the Gale-Shapley algorithm to generate stable pairings where boys get their preferred matches.
  - **Girl-Favored Pairings**: Uses a modified version of the Gale-Shapley algorithm to favor the girls during pairing.
- **Rogue Pair Detection**: Identifies rogue pairs that violate stability in the pairings.
- **Hall's Condition**: Tests whether Hall's condition is satisfied, ensuring that a perfect matching exists for the boys' set.
- **CSV Output**: Reads and writes CSV files for preferences and pairings.
  
## Code Breakdown

### `read_priorities(csv_filepath)`
Reads a CSV file containing the preferences of both boys and girls and returns a nested dictionary structure where the first level is indexed by 'B' (boys) and 'R' (girls), and the second level contains their preferences.

### `show_priorities(csv_path)`
Prints the preferences stored in a CSV file to the console for easier viewing.

### `read_pairs(csv_filename)`
Reads a CSV file with pairings and returns a dictionary where the boys' names are the keys, and their paired girl is the value.

### `write_pairs(csv_filename, pairs)`
Writes the boy-girl pairings to a CSV file.

### `find_rogues(pairs_filename, priorities_filename, outputfilename)`
Identifies rogue pairs that would prefer to be matched with someone else, thus violating stability. Outputs the rogue pairs to a text file.

### `pair(csv_path)`
Implements the **Gale-Shapley Algorithm** for boy-favored pairings. It returns a dictionary of stable pairings with girls as keys and their corresponding boys as values.

### `pair2(csv_path)`
Implements the **Gale-Shapley Algorithm** for girl-favored pairings. It returns a dictionary of stable pairings with boys as keys and their corresponding girls as values.

### `test_halls(priorities_filename, boy_set_label, girl_set_label)`
Tests Hall's condition, ensuring that for every subset of boys, there are enough girls to form a perfect match. Returns "pass" if Hall's condition is satisfied and "fail" otherwise.

### `main()`
Executes multiple tests for different sized datasets (size 6, 10, 25, and 100) to:
- Find rogue pairs.
- Generate boy-favored and girl-favored pairings.
- Test Hall's condition.
Results are written to output text files.

## Input/Output Format

### Input Files
- **Priorities CSV**: Contains the preferences of boys and girls in the following format:


*Part of Discrete Math Course (Math 340). Created pair, pair2, find_rogues, and test_halls functions. The other helper functions were provided via instructor.*
