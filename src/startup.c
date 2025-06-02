/*
 * MSP430FR2355 Startup Code and Interrupt Vector Table
 * 
 * This file contains the reset handler and interrupt vector table
 * for the MSP430FR2355 microcontroller.
 */

#include "../include/msp430fr2355.h"

/* External symbols from linker script */
extern unsigned int __data_start;
extern unsigned int __data_end;
extern unsigned int __data_load_start;
extern unsigned int __bss_start;
extern unsigned int __bss_end;
extern unsigned int __stack;

/* Main function prototype */
extern int main(void);

/* Forward declarations */
void __reset_vector(void);
void __default_handler(void);

/*
 * Reset Handler
 * This function is called when the processor starts up
 */
void __reset_vector(void)
{
    unsigned int *src, *dest;
    
    /* Stop watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;
    
    /* Copy initialized data from FRAM to RAM */
    src = &__data_load_start;
    dest = &__data_start;
    while (dest < &__data_end)
    {
        *dest++ = *src++;
    }
    
    /* Clear uninitialized data (BSS) */
    dest = &__bss_start;
    while (dest < &__bss_end)
    {
        *dest++ = 0;
    }
    
    /* Call main function */
    main();
    
    /* If main returns, loop forever */
    while(1);
}

/*
 * Default handler for unused interrupts
 */
void __default_handler(void)
{
    /* Loop forever */
    while(1);
}

/* Weak aliases for interrupt handlers */
void __attribute__((weak, alias("__default_handler"))) PORT1_ISR(void);
void __attribute__((weak, alias("__default_handler"))) PORT2_ISR(void);
void __attribute__((weak, alias("__default_handler"))) ADC_ISR(void);
void __attribute__((weak, alias("__default_handler"))) EUSCI_A0_ISR(void);
void __attribute__((weak, alias("__default_handler"))) EUSCI_A1_ISR(void);
void __attribute__((weak, alias("__default_handler"))) EUSCI_B0_ISR(void);
void __attribute__((weak, alias("__default_handler"))) TIMER0_A1_ISR(void);
void __attribute__((weak, alias("__default_handler"))) TIMER0_A0_ISR(void);
void __attribute__((weak, alias("__default_handler"))) TIMER1_A1_ISR(void);
void __attribute__((weak, alias("__default_handler"))) TIMER1_A0_ISR(void);
void __attribute__((weak, alias("__default_handler"))) WDT_ISR(void);
void __attribute__((weak, alias("__default_handler"))) COMP_ISR(void);
void __attribute__((weak, alias("__default_handler"))) NMI_ISR(void);

/*
 * Interrupt Vector Table
 * Located at 0xFF80 - 0xFFFF
 */
__attribute__((section(".vectors")))
void (* const interrupt_vectors[])(void) = {
    __default_handler,      /* 0xFF80 */
    __default_handler,      /* 0xFF82 */
    __default_handler,      /* 0xFF84 */
    __default_handler,      /* 0xFF86 */
    __default_handler,      /* 0xFF88 */
    __default_handler,      /* 0xFF8A */
    __default_handler,      /* 0xFF8C */
    __default_handler,      /* 0xFF8E */
    __default_handler,      /* 0xFF90 */
    __default_handler,      /* 0xFF92 */
    __default_handler,      /* 0xFF94 */
    __default_handler,      /* 0xFF96 */
    __default_handler,      /* 0xFF98 */
    __default_handler,      /* 0xFF9A */
    __default_handler,      /* 0xFF9C */
    __default_handler,      /* 0xFF9E */
    __default_handler,      /* 0xFFA0 */
    __default_handler,      /* 0xFFA2 */
    __default_handler,      /* 0xFFA4 */
    __default_handler,      /* 0xFFA6 */
    __default_handler,      /* 0xFFA8 */
    __default_handler,      /* 0xFFAA */
    __default_handler,      /* 0xFFAC */
    __default_handler,      /* 0xFFAE */
    __default_handler,      /* 0xFFB0 */
    __default_handler,      /* 0xFFB2 */
    __default_handler,      /* 0xFFB4 */
    __default_handler,      /* 0xFFB6 */
    __default_handler,      /* 0xFFB8 */
    __default_handler,      /* 0xFFBA */
    __default_handler,      /* 0xFFBC */
    __default_handler,      /* 0xFFBE */
    __default_handler,      /* 0xFFC0 */
    __default_handler,      /* 0xFFC2 */
    __default_handler,      /* 0xFFC4 */
    __default_handler,      /* 0xFFC6 */
    __default_handler,      /* 0xFFC8 */
    __default_handler,      /* 0xFFCA */
    __default_handler,      /* 0xFFCC */
    __default_handler,      /* 0xFFCE */
    __default_handler,      /* 0xFFD0 */
    __default_handler,      /* 0xFFD2 */
    __default_handler,      /* 0xFFD4 */
    __default_handler,      /* 0xFFD6 */
    __default_handler,      /* 0xFFD8 */
    __default_handler,      /* 0xFFDA */
    __default_handler,      /* 0xFFDC */
    __default_handler,      /* 0xFFDE */
    PORT2_ISR,              /* 0xFFE0 - Port 2 */
    PORT1_ISR,              /* 0xFFE2 - Port 1 */
    TIMER1_A1_ISR,          /* 0xFFE4 - Timer1_A3 CC1-2, TA1 */
    TIMER1_A0_ISR,          /* 0xFFE6 - Timer1_A3 CC0 */
    TIMER0_A1_ISR,          /* 0xFFE8 - Timer0_A3 CC1-2, TA0 */
    TIMER0_A0_ISR,          /* 0xFFEA - Timer0_A3 CC0 */
    ADC_ISR,                /* 0xFFEC - ADC */
    EUSCI_B0_ISR,           /* 0xFFEE - USCI B0 Receive/Transmit */
    EUSCI_A1_ISR,           /* 0xFFF0 - USCI A1 Receive/Transmit */
    EUSCI_A0_ISR,           /* 0xFFF2 - USCI A0 Receive/Transmit */
    WDT_ISR,                /* 0xFFF4 - Watchdog Timer */
    COMP_ISR,               /* 0xFFF6 - Comparator_E */
    __default_handler,      /* 0xFFF8 */
    __default_handler,      /* 0xFFFA */
    NMI_ISR,                /* 0xFFFC - NMI */
    __reset_vector          /* 0xFFFE - Reset Vector */
};