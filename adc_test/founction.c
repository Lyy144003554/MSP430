#include <msp430.h>
#include <basic.h>
void Pio_set_init(void)
{
    //oled P4.1---SCL P4.2---SDA
    //circumstance led
    P6DIR |= BIT5;
    P3DIR |= BIT4;
    P6OUT ^= BIT5;
    P3OUT ^= BIT4;
}
//----------------------------------------- frequency_test-----------------------------------------

unsigned int Overflow_cnt;
unsigned long Frq;
void frequency_test(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P2SEL |= BIT1;                  // choose the founction 2
    TA0CTL =TASSEL_3 + MC_1;        // outside clock and upper count
    TA0CCR0 = 60000-1;
    TA0CCTL0 = CCIE;
    WDTCTL = WDT_ADLY_1000;
    SFRIE1 = WDTIE_L;
    _EINT();
}

#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    Frq = TA0CTL + 60000 * Overflow_cnt;
    TA0CTL |= TACLR;
    Overflow_cnt = 0;
}
#pragma vector = TIMER0_A0_VECTOR //for this use---TA0CCTL0 = CCIE;TA0CCR0 = 16384-1;TA0CTL =TASSEL_1 + MC_1;
__interrupt void TIMER0_A_ISR(void)
{
    Overflow_cnt++;
}

//------------------------------------------ pwm_action1----------------------------------------
void pwm_action1(double t1,double x1,double y1) //the P1.2/1.3 actions pwm and the clock is tim1a0
{
    P1DIR |= BIT2 + BIT3;
    P1SEL |= BIT2 + BIT3;
    TA1CCR0 = (16384*t1)-1; //the pwm period
    TA1CCTL1 = OUTMOD_6;
    TA1CCTL2 = OUTMOD_6;
    TA1CCR1 = 16384*t1*x1;
    TA1CCR2 = 16384*t1*y1;
    TA1CTL = TASSEL_1 + MC_1 + TACLR;
}
//------------------------------------------ pwm_action2----------------------------------------
void pwm_action2(double t2,double x2,double y2) //the P1.2/1.3 actions pwm and the clock is tim1a0
{
    P1DIR |= BIT2 + BIT3;
    P1SEL |= BIT2 + BIT3;
    TA1CCR0 = (16384*t2/2)-1; //the pwm period
    TA1CCTL1 = OUTMOD_6;
    TA1CCTL2 = OUTMOD_2;
    TA1CCR1 = 16384*t2*x2/2;
    TA1CCR2 = 16384*t2*y2/2;
    TA1CTL = TASSEL_1 + MC_3 + TACLR;
}
/*------------------------------------------single_ADC_test----------------------------------------
#include <founction.h>
#include <msp430.h>
#include <oled.h>
#include <basic.h>
double v1,v2;
#define nums_of_results 8
volatile unsigned int A0result[nums_of_results];
volatile unsigned int A1result[nums_of_results];
void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    OLED_Init();
    OLED_Clear();
    P6SEL |= BIT0;
    P6SEL |= BIT1;
    ADC12CTL0 = ADC12ON + ADC12SHT0_8 + ADC12MSC + REFON + ADC12REF2_5V;   //open adc12 and time
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_3;   //use timer
    ADC12MCTL0 = ADC12INCH_0;   //channel A0
    ADC12MCTL1 = ADC12INCH_1;   //channel A1
    ADC12IE = 0X08;
    ADC12CTL0 |= ADC12ENC;
    ADC12CTL0 |= ADC12SC;

    while(1)
    {   v1 = ADC12MEM0*2.5/4095;
        v2 = ADC12MEM1*2.5/4095;
        OLED_ShowString(30,1,"ADC",10);
        OLED_ShowString(20,2,"ADC1=",10);
        OLED_ShowNum(60,2,ADC12MEM0,5,20);
        OLED_ShowString(20,3,"V1=",10);
        OLED_ShowNum(60,3,v1,5,20);
        OLED_ShowString(20,4,"ADC2=",10);
        OLED_ShowNum(60,4,ADC12MEM1,5,20);
        OLED_ShowString(20,5,"V2=",10);
        OLED_ShowNum(60,5,v2,5,20);
        OLED_Clear();
    }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    static unsigned int index = 0;
    switch(__even_in_range(ADC12IV,34))
    {
        case 0: break;
        case 2: break;
        case 4: break;
        case 6: break;
        case 8: break;
        case 10:break;
        case 12:
            A0result[index] = ADC12MEM0;
            A1result[index] = ADC12MEM1;
            index++;
            if(index == 8)
            {
                index=0;
            }
        default: break;
    }
}
-------------------------------------------------------------------------------------------------*/
