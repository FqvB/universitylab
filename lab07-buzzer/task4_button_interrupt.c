#include <msp430.h>
#include <stdint.h>

void play(uint8_t, uint8_t);
void delay(uint32_t);
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_12MHZ;
  DCOCTL = CALDCO_12MHZ;

  P2DIR &= ~0x30;
  P2OUT |= 0x30;
  P2IES |= 0x30;
  P2IFG &= ~0x30;
  P2IE |= 0x30;
  __enable_interrupt();

  P2DIR |= 0x0C;

//  P2DIR &= ~0x0C;
//  P2REN |= 0x0C;

//  for(;;)
//  {
//    play(1,4);
//    play(2,2);
//    play(1,4);
//    play(4,2);
//    play(3,1);
//  }
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
  for (i=0;i<laiks;i=i+del+del)
  {
    delay(del);
    P2OUT |= 0x0C;
    delay(del);
    P2OUT &= ~0x0C;
  }
}

void delay(uint32_t ms)
{
  uint32_t ims;
  for(ims=0;ims<ms;ims++)
  {
    __delay_cycles(120);
  }
}

#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR(void)
{
  switch(P2IFG & (BIT4+BIT5))
  {
    case BIT4:
      P2IFG &= ~BIT4;
      play(1,4);
      break;
    case BIT5:
      P2IFG &= ~BIT5;
      play(3,2);
      break;
    default:
      P2IFG = 0;
      break;
  }
}
