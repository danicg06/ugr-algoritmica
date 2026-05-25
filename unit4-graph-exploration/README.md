# Unit 4 - Graph Exploration

This folder contains a collection of programming exercises of grapghs solved using **Backtracking** and **Branch&Bound** approaches for the Algorítmica course. 

> The detailed problem statements and implementation notes can be found inside the comments at the top of each `.cpp` file.

## Exercise Breakdown 📂

The problems are divided into two main categories:

### 1. Backtracking Algorithm
- **`backtracking.cpp`** — Sudoku resolver.

### 2. Branch&Bound Algorithm
- **`branch_and_bound.cpp`** — Minimizing the number of packages used to pack some items of the given size.

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
or to compile a single exercise:
```bash
# Backtracking
make backtracking

# Branch&Bound:
make branch_and_bound
```

### Execution
```bash
./build/backtracking [--examples] | --auto

./build/branch_and_bound [--examples] | --auto
```


| Flag | Description |
|------|-------------|
| `--examples` | Runs hard-coded examples. **Default** if no flag is provided. |
| `--auto` | Interactive mode — lets you introduce your own problem input. |

---

## Project Structure 📁

```
unit4-graph-exploration/
├── src/
│   ├── backtracking.cpp      # Sudoku solver (Backtracking)
│   └── branch_and_bound.cpp  # Package minimization (Branch & Bound)
├── Makefile                  # Build automation
└── README.md
```
---
## AI Assistance Disclosure 🤖
The 'main' function and the Makefile were partially generated with the assistance of GitHub Copilot (VS Code extension).
All AI-generated code was reviewed, tested, and manually adjusted by the author to ensure correctness and alignment with the problem requirements.
