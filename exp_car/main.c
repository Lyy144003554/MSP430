/************����******************/
//OLED:
//     SCL--P3.5��SDA--P3.6
//
//L298N:
//      ������IN1--P1.4,IN2--P1.5,PWMA--P1.2
//      �ҵ����IN3--P3.3,IN4--P3.4,PWMB--P1.3
//
//˫·Ѱ���������� ��---P4.1
//           �ң�---P4.0

#include <msp430.h>
#include <motor.h>
#include <oled.h>
#include <type.h>
#include <bmp.h>

void OLED_Display();
void Delay()
{
	volatile unsigned int i;
	for(i=50000;i>0;i--);   // Delay
}

int main(void)
{
  WDTCTL = WDTPW+WDTHOLD;               // �رտ��Ź�
  motor_IO_int();
  OLED_Init();    //��ʼ��
  OLED_Clear();   //����

  while(1)
  {
	       OLED_Display();
	       switch(P4IN&0x03)
	         {
	        case 0x00: ftont();break;  //0000 ��ȫ�ף�ǰ��

	        case 0x01:turn_R();break;  //0001���ұߴ������������ߣ���ת

	        case 0x02:turn_L();break;   //0010 ����ߴ������������ߣ���ת

	        case 0x03: stop();break;  // 0011  ȫ�ڣ�ֹͣ

	         }

  }
}

void OLED_Display()
{
	OLED_ShowString(50,0,"Car",5);
    __delay_cycles(1000000);
	OLED_DrawBMP(0,0,127,7,BMP);
	}
