# Makefile for Rock-Paper-Scissors C Project

# Compiler
CC = clang

# Compiler Flags
CFLAGS = -std=c99 -Wall

# Project Structure
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source Files
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/game.c $(SRC_DIR)/players.c

# Output executable
TARGET = game

# Default target
all: $(TARGET)

# How to build the executable
$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(SRC_FILES) -o $(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)
