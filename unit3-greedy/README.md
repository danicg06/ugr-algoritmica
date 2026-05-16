# Unit 3 — Greedy Algorithms

This folder contains a collection of programming exercises solved using **Greedy** approaches for the Algorítmica course. 

The detailed problem statements and implementation notes can be found inside the comments at the top of each `.cpp` file.

## Exercise Breakdown 📂

The problems are divided into two main categories:

### 1. Classical Graph Algorithms
These exercises focus on well-known, foundational greedy algorithms for graph theory:
- **`Dijkstra.cpp`** — Shortest path algorithm on a directed weighted graph.
- **`Kruskal.cpp`** — Minimum Spanning Tree (MST) discovery utilizing Disjoint Sets (Union-Find).
- **`Prim.cpp`** — Minimum Spanning Tree (MST) discovery by growing a central tree vertex by vertex.

### 2. Custom Greedy Designs
These problems were analyzed, modeled, and programmed from scratch based on custom optimization criteria:
- **`fuel.cpp`** — Minimizing the number of refueling stops for a long-distance vehicle.
- **`latency.cpp`** — Task scheduling optimization to minimize the maximum task latency against deadlines.
- **`intervals.cpp`** — Finding the minimum number of fixed-length intervals needed to cover a set of points.
- **`cables.cpp`** — Optimal binary merging strategy to minimize total connection/fusion costs.

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

Then, to execute:
```bash
./build/my_exercise
```
