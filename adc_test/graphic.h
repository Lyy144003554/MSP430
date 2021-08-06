#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__
const int PI=3.1415926;
const uchar CHAR_16[];
/*************头文件包含**************/
#include<msp430.h>
#include<intrinsics.h>
#include<stdlib.h>
#include<math.h>
#include<basic.h>
/**************************************/


/**************软件延时****************/
/*****25000000为晶振频率，可设置*******/
/**************************************/


/*************常见颜色定义*************/
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


/**************控制端定义**************/
/*********选用P4口送DH,P3口送DL********/
/******P9.0控制CS端，P9.1控制RS端******/
/******P9.2控制RW端，P9.3控制RD端******/
/*************P9.4控制RES端************/
#define TFT_CS_1 P2OUT|=BIT7   //片选端
#define TFT_CS_0 P2OUT&=~BIT7
#define TFT_RS_1 P2OUT|=BIT0   //数据命令选择端
#define TFT_RS_0 P2OUT&=~BIT0
#define TFT_WR_1 P3OUT|=BIT0   //写
#define TFT_WR_0 P3OUT&=~BIT0
#define TFT_RD_1 P3OUT|=BIT2   //读
#define TFT_RD_0 P3OUT&=~BIT2
#define TFT_RES_1 P2OUT|=BIT4  //复位
#define TFT_RES_0 P2OUT&=~BIT4
/**************************************/


long int S=0;


/*************函数定义区***************/


void init_430();                                      //430初始化
void ILI9481_Initial(void);                           //9481初始化函数
void init_TFT();                                      //TFT初始化
void LCD_WriteReg(uint,uint);                         //在指定位置写指定数据
void LCD_WR_DATA(uint);                               //lcd写数据，包括颜色码
void LCD_SetCursor(uint, uint);                       //lcd设定座标
void LCD_SetPos(uint,uint,uint,uint);                 // lcd设定区域，区域是Xmin,Xmax,Ymin,Ymax
void ClearScreen(uint);	                              //以某种颜色清屏
void LCD_DrawHLine(uint,uint,uint,uint);              //画横线，参数分别为：开始座标X,Y，长度，颜色
void LCD_DrawVLine(uint, uint, uint,uint);            //画竖线，参数分别为：开始座标X,Y，长度，颜色
void LCD_DrawRect(uint, uint, uint, uint,uint);       //画矩形，参数分别为：矩形左上角座标，长度，宽度，颜色
void LCD_FillRect(uint, uint,uint, uint,uint);        //画填充过的矩形，参数分别为：矩形左上角座标，长度，宽度，颜色
void LCD_DrawCircle(uint,uint,uint,uint);             //画圆，参数分别为：圆心座标，半径，颜色
void LCD_FillCircle(uint,uint,uint,uint);             //画填充过的圆，参数分别为：圆心座标，半径，颜色
void DrawPixel(uint,uint,uint);	                      //画一个像素点，参数分别为：座标，颜色
void LCD_DrawUniLine(uint,uint,uint,uint,uint);       //画任意方向直线，参数分别为：起点座标，终点座标，颜色
void ClearAera(uint,uint,uint,uint,uint);             //清除部分区域，参数分别为：左上角座标，长度，宽度，清除颜色
uint DATA_MERGE(uchar,uchar);                         //数据合成，两个八位合成十六位
void Draw_Pic(uint,uint,uint,uint);                   //lcd显示图片，参数分别为：图片左上角座标，长度，宽度
void LCD_PutChar(uint,uint, char, uint);        //lcd显示单个字符，参数分别为：字符左上角座标，字符，字符颜色
void LCD_PutString(uint,uint,uchar *,uint);      //lcd显示字符串，参数类似上面一个函数
void LCD_PutCha32(uint,uint,uchar *,uint);        //lcd显示汉字，参数类似上一个函数
void LCD_PutCha16(uint,uint,uchar *,uint);        //lcd显示汉字，参数类似上一个函数
void fresh_time(int,int);               //刷新时分秒，依次是时分秒
void first_screen();                               //第一屏设计
void fresh_temperature();
void fresh_date(uchar,uchar);


/*********单片机初始化函数*************/
void init_430()
{
  WDTCTL= WDTPW + WDTHOLD; // 关看门狗
  PMMCTL0_H=0xA5;//开PMM电源管理                             
  SVSMLCTL|=SVSMLRRL_1+SVMLE;//配置SVML电压
  PMMCTL0=PMMPW+PMMCOREV_2;//配置内核电压
  while((PMMIFG&SVSMLDLYIFG )==0);//等待设置完成
  PMMIFG&=~(SVMLVLRIFG + SVMLIFG+SVSMLDLYIFG);
  if((PMMIFG&SVMLIFG)==1)//判断内核电压是否上升到VSVML
  while((PMMIFG&SVMLVLRIFG)==0);//如果没有等待
  SVSMLCTL&=~SVMLE;//关掉SVML模块
  PMMCTL0_H =0X00;//锁存配置
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

/***********lcd写数据函数***************/
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



/***********LCD写寄存器*****************/
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



/********在指定寄存器写数据************/
void LCD_WriteReg(uint Index,uint Data)
{
  LCD_WR_REG(Index);
  LCD_WR_DATA(Data);
}
/**************************************/



/**********初始化驱动芯片**************/
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


/*************初始化函数****************/
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



/***********lcd定义显示窗体*************/
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



/***********lcd设置光标位置*************/
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



/***********lcd清屏函数*****************/
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



/************lcd画水平线****************/
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



/***********lcd画竖直线*****************/
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



/*********lcd画填充的矩形***************/
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



/***********lcd画矩形********************/
void LCD_DrawRect(uint Xpos, uint Ypos, uint Width, uint Height,uint bcolor)
{
  LCD_DrawHLine(Xpos, Ypos, Width,bcolor);
  LCD_DrawHLine(Xpos, Ypos+ Height, Width,bcolor); 
  LCD_DrawVLine(Xpos, Ypos, Height,bcolor);
  LCD_DrawVLine(Xpos+ Width,Ypos, Height,bcolor);
}
/*****************************************/



/**************lcd画圆********************/
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



/*************lcd画填充圆****************/
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



/*********lcd画一个像素点*****************/
void DrawPixel(uint x,uint y,uint bcolor)
{ 
	LCD_SetCursor(x,y);
  	LCD_WR_DATA(bcolor);
}
/******************************************/



/***********lcd清除区域********************/
void ClearAera(uint x,uint y,uint w,uint h,uint bcolor)
{
  	while(h--)
  	{
    	LCD_DrawHLine(x, y++, w,bcolor);    
  	}
}
/******************************************/



/***********lcd画任意方向直线**************/
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



/*******数据合成函数，两个8位到16位*********/
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




/**********lcd显示字符串（英文)*************/
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






/**********刷新lcd显示时间函数*************************/
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


/**************第一屏设计********************************/
void first_screen()
{
  uint i;
  ClearScreen(WHITE);
  LCD_PutString(152,42,"12", BLACK);
  LCD_PutChar(156,225, '6',BLACK);
  LCD_PutChar(62,132, '9',BLACK);
  LCD_PutChar(250,132, '3',BLACK);
 // LCD_PutString(0,0,"中国移动",BLACK);
  LCD_PutString(90,285,"DESIGNED BY:JP",BLACK);
  LCD_PutString(88,250,"01.08.2015   FRI",BLACK);
  LCD_PutCha32(0,447,"菜",BLACK);
  LCD_PutCha32(32,447,"单",BLACK);
  LCD_PutCha32(255,447,"返",BLACK);
  LCD_PutCha32(287,447,"回",BLACK);
  LCD_DrawCircle(160,140,100,GREEN);
  LCD_FillCircle(160,140,1,GREEN);
  LCD_PutString(88,320,"当前温度:",BLACK);
  LCD_PutString(200,320," ℃",BLACK);
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






