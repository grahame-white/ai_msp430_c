# MSP430FR2355 LED Blink Project

A baremetal embedded C project targeting the MSP430FR2355 microcontroller that blinks an LED.

## Hardware

- **Target MCU**: MSP430FR2355
- **Development Board**: MSP430FR2355 LaunchPad (MSP-EXP430FR2355)
- **LED Used**: LED1 (Red LED on P1.0)

## Features

- Baremetal C implementation (no RTOS or libraries)
- Custom linker script for MSP430FR2355 memory layout
- Interrupt vector table and startup code
- Simple GPIO-based LED blinking
- Makefile-based build system

## Project Structure

```
.
├── src/
│   ├── main.c          # Main application code
│   └── startup.c       # Startup code and interrupt vectors
├── include/
│   └── msp430fr2355.h  # MCU register definitions
├── msp430fr2355.ld     # Linker script
├── Makefile            # Build configuration
└── README.md           # This file
```

## Prerequisites

To build this project, you need the MSP430 GCC toolchain:

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install gcc-msp430
```

### Alternative Installation
Download the official MSP430-GCC toolchain from TI:
https://www.ti.com/tool/MSP430-GCC-OPENSOURCE

## Building

Check if the toolchain is available:
```bash
make check-toolchain
```

Build the project:
```bash
make
```

This will create:
- `build/msp430_led_blink.elf` - ELF executable
- `build/msp430_led_blink.hex` - Intel HEX file for programming
- `build/msp430_led_blink.map` - Memory map file

## Programming

To flash the firmware to your MSP430FR2355 LaunchPad:

### Using mspdebug (Linux/macOS)
```bash
make flash
```

### Using Code Composer Studio
1. Import the project into CCS
2. Build the project
3. Use the CCS debugger to program and run

### Using MSP430 Flasher
```bash
MSP430Flasher -n MSP430FR2355 -w build/msp430_led_blink.hex -v -z [VCC]
```

## Operation

Once programmed, the red LED (LED1) on the LaunchPad will blink continuously:
- LED ON for ~100ms
- LED OFF for ~100ms
- Repeats indefinitely

## Memory Usage

The MSP430FR2355 has:
- **FRAM**: 32KB (0x8000-0xFFFF) - Used for program and data storage
- **RAM**: 4KB (0x2000-0x2FFF) - Used for variables and stack

## Customization

To modify the blink rate, edit the delay values in `src/main.c`:
```c
delay(100000);  // Increase for slower blink, decrease for faster
```

To use the green LED (LED2) instead, change the GPIO operations in `main.c` from `P1OUT` to `P6OUT` and use `LED2` instead of `LED1`.

## Troubleshooting

1. **Build errors**: Ensure MSP430 GCC toolchain is properly installed
2. **Programming errors**: Check that the LaunchPad is connected and drivers are installed
3. **LED not blinking**: Verify the correct firmware was programmed and the board is powered

## License

MIT License - see LICENSE file for details.
