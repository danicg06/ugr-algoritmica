CC = g++
BUILD_DIR = ./build
SRC_DIR = ./src

# Get current directory cross-platform safely inside make rules if needed
current_directory = $(shell pwd)

# Target list matching all 7 translated source files
all: binomialCoefficient maxSubarray consecutivePlots repeatedNums
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

.PHONY: repeatedNums
repeatedNums:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/repeatedNums.cpp -o $(BUILD_DIR)/$@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
