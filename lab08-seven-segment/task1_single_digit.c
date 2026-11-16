#include <msp430.h>
#include <stdint.h>

// atbilde uz beigu jautajumu, lai to ciparu poziiciju nomainiitu ir janomaina P2OUT bits

uint8_t i;

void display(uint8_t);
void delay(uint32_t);

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

    uint8_t j = 0;

    // 4. uint 8 ir 8 bitu integer, un tas ir unsigned kas nozime ka visi 8 biti tiek lietoti
    // skaitla uzglabasanai, ja butu signed tad viens bits butu prieks zimes + vai -. max vertiba 2^8-1=255

    for(;;)
    {
        j = (j + 1) % 10;
        display(j);
        delay(10000);
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

void delay(uint32_t ms)
{
    uint32_t ims;
    for(ims = 0;ims<ms;ims++)
    {
        __delay_cycles(120);//aizture par 120 taktīm
        //šeit ir divi undescori!!!
    }
}
