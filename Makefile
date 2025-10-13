# Compiler settings
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra
CXXFLAGS = -Wall -Wextra -std=c++17

# Project structure
SRC_DIR = src
BIN_DIR = bin
EXAMPLE_SRC = example/main.cpp

# Output names
NAME = tui
VERSION = 0.0.1
LIB_OUT = $(BIN_DIR)/lib$(NAME).a
EXAMPLE_OUT = $(BIN_DIR)/example

# Find all .cpp files in src/ and convert to .o in bin/
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_FILES))

# Build everything
all: | $(BIN_DIR) lib example

# Create bin directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build static library
lib: $(LIB_OUT)
	@echo Built $(NAME) library v$(VERSION)

$(LIB_OUT): $(OBJ_FILES)
	ar rcs $@ $^
	rm -f $(OBJ_FILES)

# Compile each .cpp to .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build example
example: $(EXAMPLE_OUT)
	@echo Built $(NAME) example

$(EXAMPLE_OUT): $(EXAMPLE_SRC) $(LIB_OUT)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run targets
run: all
	@echo Running $(EXAMPLE_OUT)
	./$(EXAMPLE_OUT)

run_only:
	@echo Running $(EXAMPLE_OUT)
	./$(EXAMPLE_OUT)

# Clean
clean:
	rm -rf $(BIN_DIR)

.PHONY: all lib example clean run run_only
