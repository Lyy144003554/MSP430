#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__
const int PI=3.1415926;
const uchar CHAR_16[];
/*************ͷ�ļ�����**************/
#include<msp430.h>
#include<intrinsics.h>
#include<stdlib.h>
#include<math.h>
#include<basic.h>
/**************************************/


/**************�����ʱ****************/
/*****25000000Ϊ����Ƶ�ʣ�������*******/
/**************************************/


/*************������ɫ����*************/
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define ORANGE 0xE462
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x14EE
#define YELLOW 0xFFE0
#define PURPLE 0xB114
/**************************************/


/**************���ƶ˶���**************/
/*********ѡ��P4����DH,P3����DL********/
/******P9.0����CS�ˣ�P9.1����RS��******/
/******P9.2����RW�ˣ�P9.3����RD��******/
/*************P9.4����RES��************/
#define TFT_CS_1 P2OUT|=BIT7   //Ƭѡ��
#define TFT_CS_0 P2OUT&=~BIT7
#define TFT_RS_1 P2OUT|=BIT0   //��������ѡ���
#define TFT_RS_0 P2OUT&=~BIT0
#define TFT_WR_1 P3OUT|=BIT0   //д
#define TFT_WR_0 P3OUT&=~BIT0
#define TFT_RD_1 P3OUT|=BIT2   //��
#define TFT_RD_0 P3OUT&=~BIT2
#define TFT_RES_1 P2OUT|=BIT4  //��λ
#define TFT_RES_0 P2OUT&=~BIT4
/**************************************/


long int S=0;


/*************����������***************/


void init_430();                                      //430��ʼ��
void ILI9481_Initial(void);                           //9481��ʼ������
void init_TFT();                                      //TFT��ʼ��
void LCD_WriteReg(uint,uint);                         //��ָ��λ��дָ������
void LCD_WR_DATA(uint);                               //lcdд���ݣ�������ɫ��
void LCD_SetCursor(uint, uint);                       //lcd�趨����
void LCD_SetPos(uint,uint,uint,uint);                 // lcd�趨����������Xmin,Xmax,Ymin,Ymax
void ClearScreen(uint);	                              //��ĳ����ɫ����
void LCD_DrawHLine(uint,uint,uint,uint);              //�����ߣ������ֱ�Ϊ����ʼ����X,Y�����ȣ���ɫ
void LCD_DrawVLine(uint, uint, uint,uint);            //�����ߣ������ֱ�Ϊ����ʼ����X,Y�����ȣ���ɫ
void LCD_DrawRect(uint, uint, uint, uint,uint);       //�����Σ������ֱ�Ϊ���������Ͻ����꣬���ȣ���ȣ���ɫ
void LCD_FillRect(uint, uint,uint, uint,uint);        //�������ľ��Σ������ֱ�Ϊ���������Ͻ����꣬���ȣ���ȣ���ɫ
void LCD_DrawCircle(uint,uint,uint,uint);             //��Բ�������ֱ�Ϊ��Բ�����꣬�뾶����ɫ
void LCD_FillCircle(uint,uint,uint,uint);             //��������Բ�������ֱ�Ϊ��Բ�����꣬�뾶����ɫ
void DrawPixel(uint,uint,uint);	                      //��һ�����ص㣬�����ֱ�Ϊ�����꣬��ɫ
void LCD_DrawUniLine(uint,uint,uint,uint,uint);       //�����ⷽ��ֱ�ߣ������ֱ�Ϊ��������꣬�յ����꣬��ɫ
void ClearAera(uint,uint,uint,uint,uint);             //����������򣬲����ֱ�Ϊ�����Ͻ����꣬���ȣ���ȣ������ɫ
uint DATA_MERGE(uchar,uchar);                         //���ݺϳɣ�������λ�ϳ�ʮ��λ
void Draw_Pic(uint,uint,uint,uint);                   //lcd��ʾͼƬ�������ֱ�Ϊ��ͼƬ���Ͻ����꣬���ȣ����
void LCD_PutChar(uint,uint, char, uint);        //lcd��ʾ�����ַ��������ֱ�Ϊ���ַ����Ͻ����꣬�ַ����ַ���ɫ
void LCD_PutString(uint,uint,uchar *,uint);      //lcd��ʾ�ַ�����������������һ������
void LCD_PutCha32(uint,uint,uchar *,uint);        //lcd��ʾ���֣�����������һ������
void LCD_PutCha16(uint,uint,uchar *,uint);        //lcd��ʾ���֣�����������һ������
void fresh_time(int,int);               //ˢ��ʱ���룬������ʱ����
void first_screen();                               //��һ�����
void fresh_temperature();
void fresh_date(uchar,uchar);


/*********��Ƭ����ʼ������*************/
void init_430()
{
  WDTCTL= WDTPW + WDTHOLD; // �ؿ��Ź�
  PMMCTL0_H=0xA5;//��PMM��Դ����                             
  SVSMLCTL|=SVSMLRRL_1+SVMLE;//����SVML��ѹ
  PMMCTL0=PMMPW+PMMCOREV_2;//�����ں˵�ѹ
  while((PMMIFG&SVSMLDLYIFG )==0);//�ȴ��������
  PMMIFG&=~(SVMLVLRIFG + SVMLIFG+SVSMLDLYIFG);
  if((PMMIFG&SVMLIFG)==1)//�ж��ں˵�ѹ�Ƿ�������VSVML
  while((PMMIFG&SVMLVLRIFG)==0);//���û�еȴ�
  SVSMLCTL&=~SVMLE;//�ص�SVMLģ��
  PMMCTL0_H =0X00;//��������
  P5SEL |=0x0C; // Port select XT2
  UCSCTL6&=~XT2OFF; // Enable XT2 even if not used
  UCSCTL3|=SELREF_2; // FLLref = REFO
  UCSCTL4|=SELA_2; // ACLK=REFO,SMCLK=DCO,MCLK=DCO
  do
  {
    UCSCTL7&=~(XT2OFFG+XT1LFOFFG+DCOFFG);
    SFRIFG1&=~OFIFG;// Clear fault flags
  }while(SFRIFG1&OFIFG);// Test oscillator fault flag
  UCSCTL4|=SELS_5+SELM_5;// SMCLK=MCLK=XT2
  //UCSCTL5|=DIVM_1+DIVS_2;

//  P8DIR|=0xfe;
//  P8DIR&=~BIT3;
  P3DIR=0xff;
  P3DS=0xff;
  P3OUT=0xff;
  P2SEL=0x00;
  P2DIR=0xff;
  P2DS=0xff;
  P2OUT=0xff;
  P1SEL=0x00;
  P1DIR=0xff;
  P1DS=0xff;
  P4DIR=0xff;
  P4DS=0xff;
}

/***************************************/

/***********lcdд���ݺ���***************/
void LCD_WR_DATA(uint Data)	
{
  uchar DH,DL;
  DH=Data>>8;
  DL=Data;
  TFT_CS_0;
  TFT_RS_1;
  P2OUT=DH;
  P1OUT=DL;
  TFT_WR_0;
  TFT_WR_1;
  TFT_CS_1;
}
/***************************************/



/***********LCDд�Ĵ���*****************/
void LCD_WR_REG(uint Index)	   
{
  uchar DH,DL;
  DH=Index>>8;
  DL=Index;
  TFT_CS_0;
  TFT_RS_0;
  P2OUT=DH;
  P1OUT=DL;
  TFT_WR_0;
  TFT_WR_1;
  TFT_CS_1;
}
/**************************************/



/********��ָ���Ĵ���д����************/
void LCD_WriteReg(uint Index,uint Data)
{
  LCD_WR_REG(Index);
  LCD_WR_DATA(Data);
}
/**************************************/



/**********��ʼ������оƬ**************/
void ILI9481_Initial()
{ 
  LCD_WR_REG(0x11);
  delay_ms(20);
  LCD_WR_REG(0xD0);
  LCD_WR_DATA(0x07);
  LCD_WR_DATA(0x42);
  LCD_WR_DATA(0x18);
  LCD_WR_REG(0xD1);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x07);
  LCD_WR_DATA(0x10);
  LCD_WR_REG(0xD2);
  LCD_WR_DATA(0x01);
  LCD_WR_DATA(0x02);
  LCD_WR_REG(0xC0);
  LCD_WR_DATA(0x10);
  LCD_WR_DATA(0x3B);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x02);
  LCD_WR_DATA(0x11);
  LCD_WR_REG(0xC5);
  LCD_WR_DATA(0x03);
  LCD_WR_REG(0xC8);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x32);
  LCD_WR_DATA(0x36);
  LCD_WR_DATA(0x45);
  LCD_WR_DATA(0x06);
  LCD_WR_DATA(0x16);
  LCD_WR_DATA(0x37);
  LCD_WR_DATA(0x75);
  LCD_WR_DATA(0x77);
  LCD_WR_DATA(0x54);
  LCD_WR_DATA(0x0C);
  LCD_WR_DATA(0x00);
  LCD_WR_REG(0x36);
  LCD_WR_DATA(0x0A);
  LCD_WR_REG(0x3A);
  LCD_WR_DATA(0x55);
  LCD_WR_REG(0x2A);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x01);
  LCD_WR_DATA(0x3F);
  LCD_WR_REG(0x2B);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x01);
  LCD_WR_DATA(0xE0);
  delay_ms(120);
  LCD_WR_REG(0x29);
  LCD_WR_REG(0x002c);	
}
/***************************************/


/*************��ʼ������****************/
void init_TFT()
{
  TFT_CS_1;
  delay_ms(50);
  TFT_RES_0;
  delay_ms(150);
  TFT_RES_1;
  delay_ms(50);
  ILI9481_Initial();
}
/***************************************/



/***********lcd������ʾ����*************/
void LCD_SetPos(uint x0,uint x1,uint y0,uint y1)
{
  LCD_WR_REG(0x2A); 
  LCD_WR_DATA( x0>>8);
  LCD_WR_DATA( x0&0xFF);
  LCD_WR_DATA(x1>>8); 
  LCD_WR_DATA(x1&0XFF);	 
  LCD_WR_REG(0x2B); 
  LCD_WR_DATA( y0>>8);
  LCD_WR_DATA( y0&0xFF);
  LCD_WR_DATA(y1>>8); 
  LCD_WR_DATA(y1&0XFF);
  LCD_WR_REG(0x2C); 	
}



/***********lcd���ù��λ��*************/
void LCD_SetCursor(uint x0, uint y0)
{
  LCD_WR_REG(0x2A); 
  LCD_WR_DATA( x0>>8);
  LCD_WR_DATA( x0&0xFF);
  LCD_WR_REG(0x2B); 
  LCD_WR_DATA( y0>>8);
  LCD_WR_DATA( y0&0xFF);
  LCD_WR_REG(0x2C); 
	
}
/***************************************/



/***********lcd��������*****************/
void ClearScreen(uint bcolor)
{
  int i,j;
  LCD_SetPos(0,320-1,0,480-1);
  for (i=0;i<480;i++)
  {
    for (j=0;j<320;j++)
      LCD_WR_DATA(bcolor);
  }
}
/***************************************/



/************lcd��ˮƽ��****************/
void LCD_DrawHLine(uint Xpos,uint Ypos,uint Length,uint bcolor)
{
  uint i = 0;
  LCD_SetCursor(Xpos, Ypos);
  for(i = 0; i < Length; i++)
  {
    LCD_WR_DATA(bcolor);
  }
}
/***************************************/



/***********lcd����ֱ��*****************/
void LCD_DrawVLine(uint Xpos, uint Ypos, uint Length,uint bcolor)
{
  uint i = 0;
  LCD_SetCursor(Xpos, Ypos);
  for(i = 0; i < Length; i++)
  {
    LCD_WR_DATA(bcolor);
    Ypos++;
    LCD_SetCursor(Xpos, Ypos);
  }
}
/***************************************/



/*********lcd�����ľ���***************/
void LCD_FillRect(uint Xpos, uint Ypos, uint Width, uint Height,uint bcolor)
{ 
  LCD_DrawHLine(Xpos, Ypos, Width,bcolor);
  LCD_DrawHLine(Xpos, Ypos+ Height, Width,bcolor);
  LCD_DrawVLine(Xpos, Ypos, Height,bcolor);
  LCD_DrawVLine(Xpos+Width, Ypos, Height,bcolor);
  Width --;
  Height-=1;
  Xpos++;
  while(Height--)
  {
    LCD_DrawHLine(Xpos, ++Ypos, Width,bcolor);    
  }
}
/****************************************/



/***********lcd������********************/
void LCD_DrawRect(uint Xpos, uint Ypos, uint Width, uint Height,uint bcolor)
{
  LCD_DrawHLine(Xpos, Ypos, Width,bcolor);
  LCD_DrawHLine(Xpos, Ypos+ Height, Width,bcolor); 
  LCD_DrawVLine(Xpos, Ypos, Height,bcolor);
  LCD_DrawVLine(Xpos+ Width,Ypos, Height,bcolor);
}
/*****************************************/



/**************lcd��Բ********************/
void LCD_DrawCircle(uint Xpos, uint Ypos, uint Radius,uint bcolor)
{
  int D;/* Decision Variable */ 
  unsigned long int CurX;/* Current X Value */
  unsigned long int CurY;/* Current Y Value */ 
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  while (CurX <= CurY)
  {
    LCD_SetCursor(Xpos + CurX, Ypos + CurY);
    LCD_WR_DATA(bcolor);
    LCD_SetCursor(Xpos + CurX, Ypos - CurY);
    LCD_WR_DATA(bcolor);
    LCD_SetCursor(Xpos - CurX, Ypos + CurY);
    LCD_WR_DATA(bcolor);
    LCD_SetCursor(Xpos - CurX, Ypos - CurY);
    LCD_WR_DATA(bcolor);
    LCD_SetCursor(Xpos + CurY, Ypos + CurX);
    LCD_WR_DATA(bcolor);
    LCD_SetCursor(Xpos + CurY, Ypos - CurX);
    LCD_WR_DATA(bcolor);
    LCD_SetCursor(Xpos - CurY, Ypos + CurX);
    LCD_WR_DATA(bcolor);
    LCD_SetCursor(Xpos - CurY, Ypos - CurX);
    LCD_WR_DATA(bcolor);
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}
/****************************************/



/*************lcd�����Բ****************/
void LCD_FillCircle(uint Xpos,uint Ypos,uint Radius,uint bcolor)
{
  int D;
  unsigned long int CurX;
  unsigned long int CurY;
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      LCD_DrawHLine(Xpos - CurY, Ypos - CurX, 2*CurY,bcolor);
      LCD_DrawHLine(Xpos - CurY, Ypos + CurX, 2*CurY,bcolor);
    }

    if(CurX > 0) 
    {
      LCD_DrawHLine(Xpos - CurX, Ypos -CurY, 2*CurX,bcolor);
      LCD_DrawHLine(Xpos - CurX, Ypos + CurY, 2*CurX,bcolor);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
  LCD_DrawCircle(Xpos, Ypos, Radius,bcolor);
}
/*****************************************/



/*********lcd��һ�����ص�*****************/
void DrawPixel(uint x,uint y,uint bcolor)
{ 
	LCD_SetCursor(x,y);
  	LCD_WR_DATA(bcolor);
}
/******************************************/



/***********lcd�������********************/
void ClearAera(uint x,uint y,uint w,uint h,uint bcolor)
{
  	while(h--)
  	{
    	LCD_DrawHLine(x, y++, w,bcolor);    
  	}
}
/******************************************/



/***********lcd�����ⷽ��ֱ��**************/
void LCD_DrawUniLine(uint x1,uint y1,uint x2,uint y2,uint bcolor)  
{  
  uint t;  
  int xerr=0,yerr=0,delta_x,delta_y,distance;  
  int incx,incy;  
  uint row,col;  
  delta_x = x2-x1; 
  delta_y = y2-y1;  
  col=x1;  
  row=y1;  
  if(delta_x>0) incx=1;  
  else   
  {  
      if(delta_x==0) incx=0;  
      else {incx=-1;delta_x=-delta_x;}  
  }  
  if(delta_y>0)incy=1;  
  else  
  {  
      if(delta_y==0) 
        incy=0; 
      else 
      {
        incy=-1;
        delta_y=-delta_y;
      }  
  }  
  if(delta_x>delta_y) 
    distance=delta_x;  
  else 
    distance=delta_y;  
  for(t=0;t<=distance+1;t++)  
  {                                    
    DrawPixel(col, row, bcolor);
    xerr+=delta_x;  
    yerr+=delta_y;  
    if(xerr>distance)  
    {  
      xerr-=distance;  
      col+=incx;  
    }  
    if(yerr>distance)  
    {  
      yerr-=distance;  
      row+=incy;  
    }  
  }  
}
/*******************************************/



/*******���ݺϳɺ���������8λ��16λ*********/
uint DATA_MERGE(uchar a,uchar b)
{
  uint dat;
  dat=b;
  dat<<=8;
  dat+=a;
  return dat;	
}
/*******************************************/
/*******************************************/




/**********lcd��ʾ�ַ�����Ӣ��)*************/
void LCD_PutString(uint x,uint y,uchar *s,uint fColor) 
{
   uchar l=0;
   while(*s) 
   {
      if( *s < 0x80) 
      {
        LCD_PutChar(x+l*8,y,*s,fColor);
        s++;
        l++;
       }
      else
      {
        LCD_PutCha16(x+l*8,y,(uchar*)s,fColor);
        s+=2;
        l+=2;
      }
    }
}
/*******************************************/






/**********ˢ��lcd��ʾʱ�亯��*************************/
void fresh_time(int fen,int miao)
{
  int shi=11;
  LCD_FillRect(280,0,40,16,WHITE);
  LCD_FillCircle(160+(int)(65*sin((miao-1)*PI/30.0)),140-(int)(65*cos((miao-1)*PI/30.0)),2,WHITE);
  if(miao==59)
    LCD_FillCircle(160+(int)(45*sin(fen*PI/30.0)),140-(int)(45*cos(fen*PI/30.0)),2,WHITE);
  else
    LCD_FillCircle(160+(int)(45*sin((fen-1)*PI/30.0)),140-(int)(45*cos((fen-1)*PI/30.0)),2,WHITE);
  if(fen==59)
  {
    LCD_FillCircle(160+(int)(25*sin(shi*PI/6.0)),140-(int)(25*cos(shi*PI/6.0)),2,WHITE);
    shi++;
  }
  else
    LCD_FillCircle(160+(int)(25*sin((shi-1)*PI/6.0)),140-(int)(25*cos((shi-1)*PI/6.0)),2,WHITE);
  if(shi==24)
  {
    shi=0;
  }
  LCD_PutChar(280,0,'0'+shi/10,BLACK);
  LCD_PutChar(288,0,'0'+shi%10,BLACK);
  LCD_PutChar(296,0,':',BLACK);
  LCD_PutChar(304,0,'0'+fen/10,BLACK);
  LCD_PutChar(312,0,'0'+fen%10,BLACK);
  LCD_FillCircle(160+(int)(65*sin(miao*PI/30.0)),140-(int)(65*cos(miao*PI/30.0)),2,BLACK);
  LCD_FillCircle(160+(int)(45*sin(fen*PI/30.0)),140-(int)(45*cos(fen*PI/30.0)),2,CYAN);
  LCD_FillCircle(160+(int)(25*sin(shi*PI/6.0)),140-(int)(25*cos(shi*PI/6.0)),2,RED);
  delay_ms(975);
  
}
/*******************************************************/


/**************��һ�����********************************/
void first_screen()
{
  uint i;
  ClearScreen(WHITE);
  LCD_PutString(152,42,"12", BLACK);
  LCD_PutChar(156,225, '6',BLACK);
  LCD_PutChar(62,132, '9',BLACK);
  LCD_PutChar(250,132, '3',BLACK);
 // LCD_PutString(0,0,"�й��ƶ�",BLACK);
  LCD_PutString(90,285,"DESIGNED BY:JP",BLACK);
  LCD_PutString(88,250,"01.08.2015   FRI",BLACK);
  LCD_PutCha32(0,447,"��",BLACK);
  LCD_PutCha32(32,447,"��",BLACK);
  LCD_PutCha32(255,447,"��",BLACK);
  LCD_PutCha32(287,447,"��",BLACK);
  LCD_DrawCircle(160,140,100,GREEN);
  LCD_FillCircle(160,140,1,GREEN);
  LCD_PutString(88,320,"��ǰ�¶�:",BLACK);
  LCD_PutString(200,320," ��",BLACK);
  for(i=0;i<60;i++)
  {
    DrawPixel(160+(int)(80*sin(i*PI/30.0)),140-(int)(80*cos(i*PI/30.0)),BLACK);
  }
}
/********************************************************/


void fresh_date(uchar day,uchar mon)
{
  LCD_FillRect(88,250,16,16,WHITE);
  LCD_FillRect(112,250,16,16,WHITE);
  LCD_PutChar(112,250,'0'+day/10%10,BLACK);
  LCD_PutChar(120,250,'0'+day%10,BLACK);
  LCD_PutChar(88,250,'0'+mon/10%10,BLACK);
  LCD_PutChar(96,250,'0'+mon%10,BLACK);
}

#endif






