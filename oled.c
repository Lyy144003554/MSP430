#include <basic.h>
#include <mpu6050.h>
//----------------------------------------------------I2C_Start----------------------------------------------------
void I2C_Start()
{
  SDAO; SDA1;   //sent a begin data
  delay_us(2);
  SCLO; SCL1;   //sent a begin data
  delay_us(5);
  SDA0;
  delay_us(5);
  SCL0;
}
//-----------------------------------------------------I2C_Stop----------------------------------------------------
void I2C_Stop()
{
    SDAO; SDA0;
    delay_us(2);
    SCLO; SCL1;
    delay_us(5);
    SDA1;
    delay_us(5);
}
//-----------------------------------------------------I2C_Anser----------------------------------------------------
void I2C_Anser(u8 asw)
  {
  SDAO; SCLO;
  if(asw)
  {
  SDA1;
  }
  else
  {
  SDA0;
  }
  SCL1;
  delay_us(5);
  SCL0;
  delay_us(5);
  }
//----------------------------------------------------I2C_Receive----------------------------------------------------
u8 I2C_Receive()
{
  u8 receive;
  SCLO; SCL1;
  SDAI;
  delay_us(5);
  if(SDAD)
  {
      receive=1;
  }
  else
  {
      receive=0;
  }
  SCL0;
  delay_us(5);
  SDAO;
  return receive;
}
//----------------------------------------------------I2C_SendByte---------------------------------------------------
void I2C_SendByte(u8 data)
{
  u8 i;   //as a number
  SDAO;
  for(i=0;i<8;i++)
  {
  if((data<<i)&0x80)
  {
  SDA1;
  }
  else
  {
  SDA0;
  }

  SCLO; SCL1;
  delay_us(5);
  SCL0;
  delay_us(5);
  }
  I2C_Receive();
  }
//----------------------------------------------------I2C_RecvByte--------------------------------------------------
u8 I2C_RecvByte()
{
  u8 i;
  u8 data=0,receive;
  SDAO; SCLO;
  SDA1; SDAI;
  for(i=0;i<8;i++)  //read begin
  {
  data<<=1;
  SCL1;
  delay_us(5);
  if(SDAD)
  {
      receive=1;
  }
  else
  {
      receive=0;
  }
  data |= receive;
  SCL0;
  delay_us(5);
  }   //read over
  SDAO;
  return data;
  }
//----------------------------------------------------Single_WriteI2C------------------------------------------------
void Single_WriteI2C(u8 set_address,u8 set_data)
{
  I2C_Start();
  I2C_SendByte(writeads);
  I2C_SendByte(set_address);
  I2C_SendByte(set_data);
  I2C_Stop();
}
//----------------------------------------------------Single_ReadI2C------------------------------------------------
u8 Single_ReadI2C(u8 set_address)
{
  u8 data;
  I2C_Start();
  I2C_SendByte(writeads);
  I2C_SendByte(set_address);
  I2C_Start();
  I2C_SendByte(writeads+1);   //read the data
  data = I2C_RecvByte();
  I2C_Anser(1);
  I2C_Stop();
  return data;
}
//-----------------------------------------------------MPU6050Init--------------------------------------------------
void MPU6050Init()
{
  Single_WriteI2C(ACCEL_CONFIG,0x01);
  Single_WriteI2C(GYRO_CONFIG,0x18);
  Single_WriteI2C(SMPLRT_CONFIG,0x07);
  Single_WriteI2C(CONFIG,0x06);
  Single_WriteI2C(PWR_MGMT_1,0x00);
}
//-------------------------------------------------------GetData------------------------------------------------------
int GetData(u8 setaddress)
  {
  int H,L;
  H=Single_ReadI2C(setaddress);
  L=Single_ReadI2C(setaddress+1);
  return (H<<8)+L;
  }
//--------------------------------------------------------Accel--------------------------------------------------------
int AccelX()
{
  return GetData(ACCEL_XOUT_H);
}
int AccelY()
{
  return GetData(ACCEL_YOUT_H);
}
int AccelZ()
{
  return GetData(ACCEL_YOUT_H);
}
 //--------------------------------------------------------GYROX--------------------------------------------------------
int GYROX()
{
  return GetData(GYRO_XOUT_H);
}
int GYROY()
{
  return GetData(GYRO_XOUT_H);
}
int GYROZ()
{
  return GetData(GYRO_XOUT_H);
}

