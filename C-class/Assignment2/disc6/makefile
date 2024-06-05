# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source files and target executable
SRC = main.c
TARGET = executable

# Default target
all: $(TARGET)

# Compile the C program
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Clean up object files and the executable
clean:
	rm -f $(TARGET)
