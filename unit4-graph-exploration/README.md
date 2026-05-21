# Unit 4 - Graph Exploration

This folder contains a collection of programming exercises of grapghs solved using **Backtracking** and **Branch&Bound** approaches for the Algorítmica course. 

The detailed problem statements and implementation notes can be found inside the comments at the top of each `.cpp` file.

## Exercise Breakdown 📂

The problems are divided into two main categories:

### 1. Backtracking Algorithm
- **`backtracking.cpp`** — Sudoku resolver.

### 2. Branch&Bound Algorithm
- **`fuel.cpp`** — Minimizing the number of packages used to pack some items of the given size.

---

## Compilation and Execution 🛠️

A fully automated `Makefile` is provided to compile all exercises efficiently.

### Requirements
* A C++ compiler supporting `C++11` or higher (e.g., `g++`).
* GNU `make` utility.

### Commands

To compile all exercises at once, run:
```bash
make
```
or, if want to compile a single exercise:
- Backtracking:
```bash
make backtracking
```
- Branch&Bound:
```bash
make branch&bound
```
