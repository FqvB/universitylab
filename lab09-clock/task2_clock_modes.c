#include <msp430.h>
#include <stdint.h>

// atbilde uz beigu jautajumu, lai to ciparu poziiciju nomainiitu ir janomaina P2OUT bits

uint8_t i;

void display(uint8_t);
void delay(uint32_t);
void indication(uint8_t, uint8_t, uint8_t);
void time_engine(uint8_t time_instant_in_seconds);


uint8_t sekundes = 0;
uint8_t minutes = 0;
uint8_t stundas = 0;
uint8_t mode = 0;
uint8_t submode = 0;


int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_12MHZ;
    DCOCTL = CALDCO_12MHZ;

    // pogam
    P2DIR &= ~0x30;
    P2IES |= 0x30;
    P2IFG &= ~0x30;
    P2IE |= 0x30;
    __enable_interrupt();

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
//            j = (j + 1) % 100;
            time_engine(1);
        }

        digit_position = (digit_position + 1) % 4;
//        display(j);
//        indication(j, j, digit_position);
        if(mode == 0)
            indication(minutes,sekundes,digit_position);
        else if(mode == 1)
            indication(stundas,minutes,digit_position);
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

void time_engine(uint8_t time_instant_in_seconds) {
    sekundes = sekundes + time_instant_in_seconds;

    if (sekundes==60) {
        sekundes=0;
        minutes++;
    }

    if (minutes==60) {
        minutes=0;
        stundas++;
    }
    
}

#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR(void)
{
  if((P2IFG & BIT5) == BIT5)
  {
      P2IFG &= ~BIT5; //sw1
      mode = (mode + 1) % 2;
  }
  if ((P2IFG & BIT4) == BIT4)
  {
      P2IFG &= ~BIT4; //sw2
  }
}
