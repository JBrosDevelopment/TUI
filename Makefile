# Compiler settings
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra
CXXFLAGS = -Wall -Wextra -std=c++17

# Project structure
BIN = bin/
TARGET_LIB = src/lib.cpp
TARGET_EXAMPLE = example/main.cpp
HEADER = src/lib.h

# Output names
NAME = tui
VERSION = 0.0.1
LIB_OBJ = $(BIN)lib.o
LIB_OUT = $(BIN)lib$(NAME).a
EXAMPLE_OUT = $(BIN)example

# Build everything
all: | $(BIN) lib example

# Create bin directory
$(BIN):
	mkdir -p $(BIN)

# Build static library
lib: $(LIB_OUT)
	@echo Built $(NAME) library v$(VERSION)

$(LIB_OUT): $(LIB_OBJ)
	ar rcs $(LIB_OUT) $(LIB_OBJ)
	rm -f $(LIB_OBJ)

$(LIB_OBJ): $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) -c $(TARGET_LIB) -o $(LIB_OBJ)

# Build example
example: $(EXAMPLE_OUT)
	@echo Built $(NAME) example

$(EXAMPLE_OUT): $(TARGET_EXAMPLE) $(LIB_OUT)
	$(CXX) $(CFLAGS) $(TARGET_EXAMPLE) $(LIB_OUT) -o $(EXAMPLE_OUT)

run: all
	@echo Running $(EXAMPLE_OUT)
	./$(EXAMPLE_OUT)

run_only:
	@echo Running $(EXAMPLE_OUT)
	./$(EXAMPLE_OUT)

clean:
	rm -rf $(BIN)

.PHONY: all lib example clean run
