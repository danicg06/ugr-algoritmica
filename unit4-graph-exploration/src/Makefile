CC = g++
FLAGS =  -Wall -Wextra -O2
SRC = backtracking.cpp $(wildcard branch&bound.cpp)
TARGETS = $(SRC:.cpp=)

all: $(TARGETS)

%: %.cpp
	$(CC) $(FLAGS) -o "$@" "$^"

run-examples: backtracking
	./backtracking --examples

run-auto: backtracking
	@echo "Use example:"
	@echo "printf \"1 4 1 0 3 0 0 4 0 2 2 0 4 0 0 3 0 1\n\" | ./backtracking --auto"

clean:
	rm -f $(TARGETS)

.PHONY: all run-examples run-auto clean
