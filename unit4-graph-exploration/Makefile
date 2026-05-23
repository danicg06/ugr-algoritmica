CC = g++
BUILD_DIR = ./build
SRC_DIR = ./src
FLAGS =  -Wall -Wextra -O2

all: backtracking branch_and_bound

backtracking:
	mkdir -p  $(BUILD_DIR)
	$(CC) $(FLAGS) $(SRC_DIR)/backtracking.cpp -o $(BUILD_DIR)/backtracking

branch_and_bound:
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(SRC_DIR)/branch_and_bound.cpp -o $(BUILD_DIR)/branch_and_bound

run-examples: backtracking
	.$(BUILD_DIR)/backtracking --examples

run-auto: backtracking
	@echo "Use example:"
	@echo "printf \"1 4 1 0 3 0 0 4 0 2 2 0 4 0 0 3 0 1\n\" | .$(BUILD_DIR)/backtracking --auto"

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run-examples run-auto clean
