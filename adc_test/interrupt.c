#include <msp430.h>
#include <basic.h>

#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
    if(P2IFG&BIT4)
    {
        P3OUT ^= BIT1;
    }
    P2IFG=0;
}
/*
#pragma vector = TIMER1_A1_VECTOR //for this use---TA1CTL = TASSEL_2 + MC_2 + TAIE;
__interrupt void TIMER1_A_ISR(void)
{
    switch(TA1IV)
    {
    case 2:// CCR1_ISR();
        break;
    case 4://CCR2_ISR();
        break;
    case 14:P1OUT ^= BIT2;
    LPM0_EXIT;
    break;
    }
}
*/

