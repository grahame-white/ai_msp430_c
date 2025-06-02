#ifndef MSP430FR2355_H
#define MSP430FR2355_H

/* MSP430FR2355 Register Definitions */
/* Based on TI MSP430FR2xx_4xx Family User's Guide */

/* Special Function Registers */
#define WDTCTL              (*(volatile unsigned int*)0x015C)
#define WDTPW               0x5A00
#define WDTHOLD             0x0080

/* Port 1 Registers */
#define P1IN                (*(volatile unsigned char*)0x0200)
#define P1OUT               (*(volatile unsigned char*)0x0202)
#define P1DIR               (*(volatile unsigned char*)0x0204)
#define P1REN               (*(volatile unsigned char*)0x0206)
#define P1SEL0              (*(volatile unsigned char*)0x020A)
#define P1SEL1              (*(volatile unsigned char*)0x020C)

/* Port 6 Registers */  
#define P6IN                (*(volatile unsigned char*)0x0240)
#define P6OUT               (*(volatile unsigned char*)0x0242)
#define P6DIR               (*(volatile unsigned char*)0x0244)
#define P6REN               (*(volatile unsigned char*)0x0246)
#define P6SEL0              (*(volatile unsigned char*)0x024A)
#define P6SEL1              (*(volatile unsigned char*)0x024C)

/* GPIO Pin Definitions for LaunchPad */
#define LED1                0x01    /* P1.0 - Red LED */
#define LED2                0x40    /* P6.6 - Green LED */

/* Power Management Module */
#define PM5CTL0             (*(volatile unsigned int*)0x0130)
#define LOCKLPM5            0x0001

/* Clock System */
#define CSCTL0              (*(volatile unsigned int*)0x0160)
#define CSCTL1              (*(volatile unsigned int*)0x0162)
#define CSCTL2              (*(volatile unsigned int*)0x0164)
#define CSCTL3              (*(volatile unsigned int*)0x0166)

/* Timer_A3 */
#define TA0CTL              (*(volatile unsigned int*)0x0340)
#define TA0CCR0             (*(volatile unsigned int*)0x0350)
#define TA0IV               (*(volatile unsigned int*)0x036E)

/* Timer Control bits */
#define TASSEL_2            0x0200  /* Timer_A clock source select: SMCLK */
#define MC_1                0x0010  /* Timer_A mode control: Up mode */
#define TACLR               0x0004  /* Timer_A counter clear */

/* Interrupt Enable/Disable */
#define __enable_interrupt()    __asm__("eint")
#define __disable_interrupt()   __asm__("dint")
#define __delay_cycles(x)       __asm__("mov %0, r15\n1: dec r15\n jnz 1b" : : "i"(x) : "r15")

#endif /* MSP430FR2355_H */