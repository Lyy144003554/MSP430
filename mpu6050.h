#ifndef MPU6050_H_
#define MPU6050_H_
#include <msp430.h>
//the initial cpu fre is 10000000
//----------------------------------------------------SDA P4.2----------------------------------------------------
#define SDA1 P4OUT |= BIT2
#define SDA0 P4OUT ^= BIT2
#define SDAI P4DIR ^= BIT2
#define SDAO P4DIR |= BIT2
#define SDAD (P4IN&BIT1)
//----------------------------------------------------SCL P4.1----------------------------------------------------
#define SCL0 P4OUT ^= BIT1
#define SCL1 P4OUT |= BIT1
#define SCLO P4DIR |= BIT1
#define address1 0x68   //A0 GND
#define address2 0x69   //A0 VCC
#define writeads 0xD0   //12bit's address
//-----------------------------------------------A0 which can be chosen-------------------------------------------
#define SMPLRT_CONFIG 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
//-------------------------------------------------------ACCEL----------------------------------------------------
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
//--------------------------------------------------------TEMP----------------------------------------------------
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
//--------------------------------------------------------GYRO----------------------------------------------------
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define PWR_MGMT_1 0x6B
//--------------------------------------------------------VOID----------------------------------------------------
void I2C_Start();
void I2C_Stop();
void I2C_Anser(u8 asw);
void I2C_SendByte(u8 data);
void Single_WriteI2C(u8 set_address,u8 set_data);
void MPU6050Init();
int GetData(u8 setaddress);
int AccelX();
int AccelY();
int AccelZ();
int GYROX();
int GYROY();
int GYROZ();
u8 I2C_Receive();
u8 I2C_RecvByte();
u8 Single_ReadI2C(u8 set_address);
#endif
