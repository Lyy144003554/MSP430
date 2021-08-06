#include <motor.h>

void motor_IO_int()
{
	    P1DIR |=(BIT2+BIT3+BIT4+BIT5);	//PWM1,PWM2，IN1,FIN2
	    P3DIR |=(BIT3+BIT4);  // B_IN3,B_IN4
		P1SEL |=(BIT2+BIT3);

	    TA0CCR0 = 50;  //定时器装载值，周期50us,即频率1*10^6/50=20kHz
	    TA0CCTL1 = OUTMOD_7;
	    TA0CCTL2 = OUTMOD_7;
	    TA0CTL= TASSEL_2 +MC_1;

	  P4DIR = 0x00; //左右寻迹传感器.
	  P4SEL = 0x00;
	}
void ftont()
{
	 PWM(32,32);   //占空比：32*100/50= 64%，即2倍关系
	 P1OUT |= BIT5;
	 P1OUT &= ~BIT4;
	 P3OUT |= BIT4;
	 P3OUT &= ~BIT3;
}
void stop()
{
	 PWM(0,0);

}
void turn_L()
{
	 PWM(32,20);
	 P1OUT |= BIT4;
	 P1OUT &= ~BIT5;
	 P3OUT |= BIT4;
	 P3OUT &= ~BIT3;
}
void turn_R()
{
	PWM(20,32);
	P1OUT |= BIT5;
	P1OUT &= ~BIT4;
	P3OUT |= BIT3;
	P3OUT &= ~BIT4;
}

void PWM(int pwm1,int pwm2)   //左，右电机pwm
{
	TA0CCR1 = pwm1;   // CCR2 PWM 占空比定义
	TA0CCR2 = pwm2;   // CCR2 PWM 占空比定义
	}


