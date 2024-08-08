# Compiler
CC := gcc-14
# Compiler flags
CFLAGS := -g -Wall -Wextra -std=c23

# Linker flags
LDFLAGS := -lncurses

# Directories
OBJ_DIR := obj
BIN_DIR := bin

# Main project source directory
SRC_DIR := src

# Main project source files
MAIN_SRC := $(wildcard $(SRC_DIR)/*.c)

# Object files
MAIN_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(MAIN_SRC))

# Executable name
EXECUTABLE := $(BIN_DIR)/snake

# Targets
all: directories $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
