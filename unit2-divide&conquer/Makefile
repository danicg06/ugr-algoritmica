CC = g++
BUILD_DIR = ./build
SRC_DIR = ./src

# Get current directory cross-platform safely inside make rules if needed
current_directory = $(shell pwd)

# Target list matching all 7 translated source files
all: binomialCoefficient maxSubarray consecutivePlots
	@echo "Compiled successfully."

.PHONY: binomialCoefficient
binomialCoefficient:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/binomialCoefficient.cpp -o $(BUILD_DIR)/$@

.PHONY: maxSubarray
maxSubarray:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/maxSubarray.cpp -o $(BUILD_DIR)/$@

.PHONY: consecutivePlots
consecutivePlots:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/consecutivePlots.cpp -o $(BUILD_DIR)/$@

.PHONY: cables
cables:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/cables.cpp -o $(BUILD_DIR)/$@

.PHONY: Kruskal
Kruskal:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/Kruskal.cpp -o $(BUILD_DIR)/$@

.PHONY: Prim
Prim:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/Prim.cpp -o $(BUILD_DIR)/$@

.PHONY: Dijkstra
Dijkstra:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/Dijkstra.cpp -o $(BUILD_DIR)/$@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
