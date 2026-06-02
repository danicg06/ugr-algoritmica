# Unit 2 — Divide and Conquer Algorithms 🔍

This folder contains a collection of programming exercises solved using **Divide and Conquer** approaches for the *Algorítmica* course.

> The detailed problem statements and implementation notes can be found inside the comments at the top of each `.cpp` file.

---

## Build & Run 🛠️

A fully automated `Makefile` is provided to compile all exercises efficiently.

### Requirements

- A C++ compiler supporting **C++11** or higher (e.g., `g++`)
- GNU **`make`** utility

### Build

Compile all exercises at once:

```bash
make
```

Or compile a single exercise:

```bash
make binomialCoefficient
make consecutivePlots
make maxSubarray
make repeatedNums
```

### Run

```bash
./build/<exercise_name>
```
---

## Project Structure 📁

```
unit3-greedy-algorithms/
├── src/
│   ├── binomialCoefficient.cpp    # Binomial coefficient of the form n = C(k,2)
│   ├── consecutivePlots.cpp       # Maximum number of consecutive plots
│   ├── maxSubarray.cpp            # Maximum sumatory of subarray elements
│   └── repeatedNums.cpp           # Repeated numbers counter
├── Makefile            # Build automation
└── README.md
```
