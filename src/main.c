/* 
 * MSP430FR2355 LED Blink Example
 * 
 * This program blinks the red LED (P1.0) on the MSP430FR2355 LaunchPad
 * 
 * Hardware: MSP430FR2355 LaunchPad
 * LED1 (Red): P1.0
 * LED2 (Green): P6.6
 */

#include "../include/msp430fr2355.h"

void delay(unsigned long cycles);
void init_clock(void);
void init_gpio(void);

int main(void)
{
    /* Stop watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;
    
    /* Disable the GPIO power-on default high-impedance mode */
    PM5CTL0 &= ~LOCKLPM5;
    
    /* Initialize clock system */
    init_clock();
    
    /* Initialize GPIO */
    init_gpio();
    
    /* Main loop - blink LED */
    while(1)
    {
        P1OUT |= LED1;          /* Turn on LED1 */
        delay(100000);          /* Delay */
        P1OUT &= ~LED1;         /* Turn off LED1 */
        delay(100000);          /* Delay */
    }
    
    return 0;
}

/*
 * Initialize clock system
 * Configure DCO to run at ~1MHz
 */
void init_clock(void)
{
    /* Configure DCO to 1MHz */
    CSCTL0 = 0;                 /* Clear CSCTL0 */
    CSCTL1 = 0;                 /* Clear CSCTL1 - Use default DCO frequency */
    CSCTL2 = 0;                 /* Clear CSCTL2 */
    CSCTL3 = 0;                 /* Clear CSCTL3 */
}

/*
 * Initialize GPIO pins
 * Configure P1.0 as output for LED1
 */
void init_gpio(void)
{
    /* Configure P1.0 as output */
    P1DIR |= LED1;              /* Set P1.0 as output */
    P1OUT &= ~LED1;             /* Initialize LED1 as off */
    
    /* Configure P1.0 as GPIO (not special function) */
    P1SEL0 &= ~LED1;
    P1SEL1 &= ~LED1;
    
    /* Optional: Configure P6.6 for LED2 (green LED) */
    P6DIR |= LED2;              /* Set P6.6 as output */
    P6OUT &= ~LED2;             /* Initialize LED2 as off */
    P6SEL0 &= ~LED2;
    P6SEL1 &= ~LED2;
}

/*
 * Simple delay function
 * Uses CPU cycles for delay - not precise timing
 */
void delay(unsigned long cycles)
{
    volatile unsigned long i;
    for(i = 0; i < cycles; i++)
    {
        __asm__("nop");         /* No operation - just consume cycles */
    }
}