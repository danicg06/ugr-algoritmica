CC = g++
BUILD_DIR = ./build
SRC_DIR = ./src

# Get current directory cross-platform safely inside make rules if needed
current_directory = $(shell pwd)

# Target list matching all 7 translated source files
all: fuel latency intervals cables kruskal prim dijkstra
	@echo "Compiled successfully."

.PHONY: fuel
fuel:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/fuel.cpp -o $(BUILD_DIR)/$@

.PHONY: latency
latency:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/latency.cpp -o $(BUILD_DIR)/$@

.PHONY: intervals
intervals:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/intervals.cpp -o $(BUILD_DIR)/$@

.PHONY: cables
cables:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/cables.cpp -o $(BUILD_DIR)/$@

.PHONY: kruskal
kruskal:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/Kruskal.cpp -o $(BUILD_DIR)/$@

.PHONY: prim
prim:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/Prim.cpp -o $(BUILD_DIR)/$@

.PHONY: dijkstra
dijkstra:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_DIR)/Dijkstra.cpp -o $(BUILD_DIR)/$@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
