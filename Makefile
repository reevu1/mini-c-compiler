# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -mconsole

# Directories
SRC_DIR = src
BIN = compiler

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/lexer.c

# Default build target
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN)

# Clean build files
clean:
	del /Q $(BIN).exe 2>nul || exit 0
