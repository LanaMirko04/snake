# Compiler
CC := gcc-14
# Compiler flags
CFLAGS := -g -Wall -Wextra -std=c23

# Linker flags
LDFLAGS := -lncurses

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INSTALL_DIR := /usr/local/bin

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

install:
	@if [ -w $(INSTALL_DIR) ]; then \
		cp $(EXECUTABLE) $(INSTALL_DIR)/snake; \
		chmod 755 $(INSTALL_DIR)/snake; \
		echo "Installation complete!"; \
		echo "Executable installed to $(INSTALL_DIR)."; \
	else \
		echo "Installation failed!"; \
		echo "Please run with elevated privileges (e.g., using sudo)."; \
	fi

uninstall:
	@if [ -f $(INSTALL_DIR)/snake ]; then \
		if [ -w $(INSTALL_DIR) ]; then \
			rm -f $(INSTALL_DIR)/snake; \
			echo "Uninstallation complete!"; \
			echo "The executable 'snake' has been removed from $(INSTALL_DIR)."; \
		else \
			echo "Uninstallation failed!"; \
			echo "Please run with elevated privileges (e.g., using sudo)."; \
		fi; \
	else \
		echo "'snake' is not installed; nothing to uninstall."; \
	fi
		
# Phony targets
.PHONY: all clean install uninstall

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
