#include <msp430.h>
#include <stdint.h>
#include "aux_functions.h"

void display(uint8_t digit)
{
    if (digit == 0) P1OUT = 0xF5;
    if (digit == 1) P1OUT = 0x05;
    if (digit == 2) P1OUT = 0x73;
    if (digit == 3) P1OUT = 0x57;
    if (digit == 4) P1OUT = 0x87;
    if (digit == 5) P1OUT = 0xD6;
    if (digit == 6) P1OUT = 0xF6;
    if (digit == 7) P1OUT = 0x45;
    if (digit == 8) P1OUT = 0xF7;
    if (digit == 9) P1OUT = 0xD7;
    if (digit == 0xA) P1OUT = 0xE7;
    if (digit == 0xB) P1OUT = 0xB0;
    if (digit == 0xC) P1OUT = 0x36;
    if (digit == 0xD) P1OUT = 0x26;
    if (digit == 0xE) P1OUT = 0xE2;
    if (digit == 0xF) P1OUT = 0x00;
}

void indication(uint8_t digit12, uint8_t digit34, uint8_t which_digit)
{
    P2OUT &= ~0x0F;
    if (which_digit == 0) {display(digit12 / 10); P2OUT |= BIT0;}
    if (which_digit == 1) {display(digit12 % 10); P2OUT |= BIT1;}
    if (which_digit == 2) {display(digit34 / 10); P2OUT |= BIT2;}
    if (which_digit == 3) {display(digit34 % 10); P2OUT |= BIT3;}
}

void indication2(uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4, uint8_t which_digit)
{
    P2OUT &= ~0x0F;
    if (which_digit == 0) {display(digit1); P2OUT |= BIT0;}
    if (which_digit == 1) {display(digit2); P2OUT |= BIT1;}
    if (which_digit == 2) {display(digit3); P2OUT |= BIT2;}
    if (which_digit == 3) {display(digit4); P2OUT |= BIT3;}
}

void delay(uint32_t ms)
{
    uint32_t ims;
    for(ims = 0;ims<ms;ims++)
    {
        __delay_cycles(120);//aizture par 120 taktīm
        //šeit ir divi undescori!!!
    }
}

void digit_blinking(uint8_t digit_position, uint8_t blink_digit_position1, uint8_t blink_digit_position2, uint16_t j2)
{
    if ((j2>500)&&(digit_position==blink_digit_position1))
    {
        P2OUT &= ~(0x01<<digit_position);
    }

    if ((j2>500)&&(digit_position==blink_digit_position2))
    {
        P2OUT &= ~(0x01<<digit_position);
    }
}

void play(uint8_t n, uint8_t e)
{
    uint8_t del;
    uint32_t laiks;
    volatile uint32_t i;

    if (n==1) del = 47;
    if (n==2) del = 42;
    if (n==3) del = 37;
    if (n==4) del = 35;
    if (n==5) del = 31;
    if (n==6) del = 28;
    if (n==7) del = 25;
    if(e==1) laiks = 100000;
    if(e==2) laiks = 50000;
    if(e==4) laiks = 25000;
    for (i = 0;i<laiks;i=i+del+del)
    {
        delay(del);
        P2OUT |= 0x0C;
        delay(del);
        P2OUT &= ~0x0C;
    }
}
