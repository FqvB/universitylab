#include <msp430.h>
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD; 
  P2DIR |= 0x0C;
  P2OUT |= 0x0C;
  volatile unsigned int i;
  for(;;)
  {
    P2OUT ^= 0x0C;
    for(i = 100; i>1;i--);
  }
}
