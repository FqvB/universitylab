#include <msp430.h>
#include <stdint.h>

// atbilde uz beigu jautajumu, lai to ciparu poziiciju nomainiitu ir janomaina P2OUT bits

uint8_t i;

void display(uint8_t);
void delay(uint32_t);
void indication(uint8_t, uint8_t, uint8_t);

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_12MHZ;
    DCOCTL = CALDCO_12MHZ;

    P1DIR = 0xFF;
    P2DIR = 0x0F;
    P2OUT = 0x00;
    P2OUT |= BIT0;
//    P2OUT |= BIT1;

    uint8_t digit_position = 0;
    uint8_t j = 0;
    uint16_t j2 = 0;

    // 4. uint 8 ir 8 bitu integer, un tas ir unsigned kas nozime ka visi 8 biti tiek lietoti
    // skaitla uzglabasanai, ja butu signed tad viens bits butu prieks zimes + vai -. max vertiba 2^8-1=255

    for(;;)
    {
        j2++;
        if (j2 == 1000)
        {
            j2 = 0;
            j = (j + 1) % 100;
        }

        digit_position = (digit_position + 1) % 4;
//        display(j);
        indication(j, j, digit_position);
        delay(100);
    }
}

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
}

void indication(uint8_t digit12, uint8_t digit34, uint8_t which_digit)
{
    P2OUT &= ~0x0F;
    if (which_digit == 0) {display(digit12 / 10); P2OUT |= BIT0;}
    if (which_digit == 1) {display(digit12 % 10); P2OUT |= BIT1;}
    if (which_digit == 2) {display(digit34 / 10); P2OUT |= BIT2;}
    if (which_digit == 3) {display(digit34 % 10); P2OUT |= BIT3;}
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
