#include <founction.h>
#include <msp430.h>
#include <oled.h>
#include <basic.h>
#include <mpu6050.h>
double v1,v2;
int ax,ay,az;
#define nums_of_results 8
volatile unsigned int A0result[nums_of_results];
volatile unsigned int A1result[nums_of_results];
void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    OLED_Init();
    OLED_Clear();
    MPU6050Init();
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
    {   /*v1 = ADC12MEM0*2.5/4095;
        v2 = ADC12MEM1*2.5/4095;
        OLED_ShowString(30,1,"ADC",10);
        OLED_ShowString(20,2,"ADC1=",10);
        */
        ax = AccelY();
        ay = AccelY();
        az = AccelZ();
        OLED_ShowNum(60,2,ax,5,20);
        OLED_ShowNum(60,3,ay,5,20);
        OLED_ShowNum(60,4,az,5,20);
/*
        OLED_ShowString(20,3,"V1=",10);
        OLED_ShowNum(60,3,v1,5,20);
        OLED_ShowString(20,4,"ADC2=",10);
        OLED_ShowNum(60,4,ADC12MEM1,5,20);
        OLED_ShowString(20,5,"V2=",10);
        OLED_ShowNum(60,5,v2,5,20);
        */
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
