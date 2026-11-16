#include <msp430.h>
#include <stdint.h>
#include "aux_functions.h"

// atbilde uz beigu jautajumu, lai to ciparu poziiciju nomainiitu ir janomaina P2OUT bits

uint8_t i;

void time_engine(uint8_t time_instant_in_seconds);
void short_press(void);
void long_press (void);

uint8_t sekundes = 0;
uint8_t minutes = 0;
uint8_t stundas = 0;
uint8_t mode = 0;
uint8_t submode = 0;
uint8_t poga4 = 0;
uint8_t alarm_minutes = 0;
uint8_t alarm_hours = 0;
uint8_t alarm_on = 0;


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
        if(mode == 0) {
            indication(minutes,sekundes,digit_position);
            if ((j2<500)&&(digit_position==1)) P1OUT |= 0x08;
        }
        else if(mode == 1) {
            indication(stundas,minutes,digit_position);
            if ((j2<500)&&(digit_position==1)) P1OUT |= 0x08;
        }
        else if(mode == 2)
        {
            indication(stundas,minutes,digit_position);
            if (submode==0) digit_blinking(digit_position,0,1,j2);
            if (submode==1) digit_blinking(digit_position,2,3,j2);
            if (submode==2)
            {
                digit_blinking(digit_position,0,1,j2);
                digit_blinking(digit_position,2,3,j2);
            }
            if ((j2<500)&&(digit_position==1)) P1OUT |= 0x8;
        }
        else if((mode == 3)&(submode == 0)&(alarm_on == 1))
            indication2(0xA,0xB,0xC,0xD,digit_position);
        else if((mode == 3)&(submode == 0)&(alarm_on == 0))
            indication2(0xA,0xB,0xC,0xE,digit_position);
        else if(mode == 3)
        {
            indication(alarm_hours,alarm_minutes,digit_position);
            if (submode==1) digit_blinking(digit_position,0,1,j2);
            if (submode==2) digit_blinking(digit_position,2,3,j2);
        }
        
        delay(100);

        
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

void short_press(void) {
    if (mode == 2)
    {
        if (submode == 0)
        {
            stundas++;
            if (stundas == 24) stundas = 0;
        }
        if (submode == 1)
        {
            minutes++;
            if (minutes == 60) minutes = 0;
        }
    }
    if (mode == 3)
    {
        if (submode == 0)
        {
            alarm_on = (alarm_on+1)%2;
        }
        if (submode == 1)
        {
            alarm_hours++;
            if (alarm_hours == 24) alarm_hours = 0;
        }
        if (submode == 2)
        {
            alarm_minutes++;
            if (alarm_minutes == 60) alarm_minutes = 0;
        }
    }
}
void long_press (void) {
    submode++;
    if(submode==3) submode=0;
}


#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR(void)
{
  if((P2IFG & BIT5) == BIT5)
  {
      P2IFG &= ~BIT5; //sw1
      mode = (mode + 1) % 4;
  }
  if ((P2IFG & BIT4) == BIT4)
  {
      P2IFG &= ~BIT4; //sw2
      if ((P2IES&BIT4) == BIT4)
      {
          P2IES &= ~BIT4;
          poga4 = sekundes;
      }

      else
      {
          P2IES |= BIT4;
          if (sekundes-poga4>1)
             long_press();
          else
          short_press();
              
      }
  }
}
