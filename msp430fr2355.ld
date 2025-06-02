/*
 * MSP430FR2355 Linker Script
 * 
 * Memory layout for MSP430FR2355:
 * - FRAM: 32KB (0x8000 - 0xFFFF) - Program and data memory
 * - RAM: 4KB (0x2000 - 0x2FFF) - Volatile memory
 * - SFR: Special Function Registers (0x0000 - 0x01FF)
 * - Peripherals: (0x0200 - 0x1FFF)
 */

MEMORY
{
    /* Special Function Registers */
    SFR              : ORIGIN = 0x0000, LENGTH = 0x0200
    
    /* Peripheral Memory */
    PERIPHERALS      : ORIGIN = 0x0200, LENGTH = 0x1E00
    
    /* RAM */
    RAM              : ORIGIN = 0x2000, LENGTH = 0x1000
    
    /* FRAM - Program and Data Memory */
    FRAM             : ORIGIN = 0x8000, LENGTH = 0x8000
    
    /* Interrupt vectors */
    VECTORS          : ORIGIN = 0xFF80, LENGTH = 0x0080
}

SECTIONS
{
    /* Interrupt vectors */
    .vectors : {
        KEEP(*(.vectors*))
    } > VECTORS
    
    /* Program code */
    .text : {
        *(.text*)
        *(.rodata*)
        . = ALIGN(2);
    } > FRAM
    
    /* Initialized data */
    .data : {
        __data_start = .;
        *(.data*)
        . = ALIGN(2);
        __data_end = .;
    } > RAM AT> FRAM
    
    __data_load_start = LOADADDR(.data);
    
    /* Uninitialized data */
    .bss : {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(2);
        __bss_end = .;
    } > RAM
    
    /* Stack */
    .stack : {
        . = ALIGN(2);
        __stack_start = .;
        . += 0x200;  /* 512 bytes for stack */
        __stack_end = .;
    } > RAM
    
    /* Heap (optional) */
    .heap : {
        __heap_start = .;
        . = ORIGIN(RAM) + LENGTH(RAM);
        __heap_end = .;
    } > RAM
}

/* Entry point */
ENTRY(__reset_vector)

/* Stack pointer initial value */
PROVIDE(__stack = __stack_end);