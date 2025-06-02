# Makefile for MSP430FR2355 LED Blink Project
#
# This Makefile builds a baremetal C application for the MSP430FR2355 microcontroller
# 
# Usage:
#   make          - Build the project
#   make clean    - Clean build artifacts
#   make flash    - Flash the binary to the microcontroller (requires mspdebug)
#   make debug    - Start GDB debug session

# Project name
PROJECT = msp430_led_blink

# Toolchain
CC = msp430-gcc
LD = msp430-gcc
OBJCOPY = msp430-objcopy
OBJDUMP = msp430-objdump
SIZE = msp430-size

# Target MCU
MCU = msp430fr2355

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Compiler flags
CFLAGS = -mmcu=$(MCU) \
         -Os \
         -Wall \
         -Wextra \
         -g \
         -I$(INC_DIR) \
         -std=c99 \
         -ffunction-sections \
         -fdata-sections

# Linker flags
LDFLAGS = -mmcu=$(MCU) \
          -Wl,--gc-sections \
          -Wl,-T,msp430fr2355.ld \
          -Wl,-Map,$(BUILD_DIR)/$(PROJECT).map

# Default target
all: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).hex

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@
	$(SIZE) $@

# Generate hex file
$(BUILD_DIR)/$(PROJECT).hex: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex $< $@

# Generate disassembly
$(BUILD_DIR)/$(PROJECT).lst: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJDUMP) -h -S $< > $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Flash to microcontroller (requires mspdebug)
flash: $(BUILD_DIR)/$(PROJECT).hex
	@echo "Flashing $(PROJECT).hex to MSP430FR2355..."
	@if command -v mspdebug >/dev/null 2>&1; then \
		mspdebug tilib "prog $(BUILD_DIR)/$(PROJECT).hex"; \
	else \
		echo "Error: mspdebug not found. Please install mspdebug to flash the device."; \
		echo "Alternative: Use Code Composer Studio or other MSP430 programming tools"; \
	fi

# Start GDB debug session
debug: $(BUILD_DIR)/$(PROJECT).elf
	@echo "Starting GDB debug session..."
	@if command -v msp430-gdb >/dev/null 2>&1; then \
		msp430-gdb $(BUILD_DIR)/$(PROJECT).elf; \
	else \
		echo "Error: msp430-gdb not found."; \
	fi

# Help
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Clean build artifacts"
	@echo "  flash   - Flash the binary to the microcontroller"
	@echo "  debug   - Start GDB debug session"
	@echo "  help    - Show this help message"

# Check if toolchain is available
check-toolchain:
	@echo "Checking MSP430 toolchain..."
	@if command -v $(CC) >/dev/null 2>&1; then \
		echo "✓ $(CC) found: $$($(CC) --version | head -n1)"; \
	else \
		echo "✗ $(CC) not found"; \
		echo "  Please install the MSP430 GCC toolchain"; \
		echo "  Ubuntu/Debian: sudo apt-get install gcc-msp430"; \
		echo "  Or download from TI: https://www.ti.com/tool/MSP430-GCC-OPENSOURCE"; \
	fi

.PHONY: all clean flash debug help check-toolchain

# Dependencies
-include $(OBJECTS:.o=.d)