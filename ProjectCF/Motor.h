#pragma once
#define Motor_NomorSpeed 120 
#define Motor_EncodePin1 2
#define Motor_EncodePin2 3
const int  Motor_Pin2 = 35;
const int  Motor_Pin1 = 37;
const int  Motor_Pin4 = 39;
const int  Motor_Pin3 = 41;
const int  Motor_EN1 = 7;
const int Motor_EN2 = 6;
extern int Motor_M1Speed;
extern int Motor_M2Speed;

extern volatile unsigned  long long  Motor_M1Cnt;
extern volatile unsigned long long  Motor_M2Cnt;



void Motor_Init();
void Motor_Stop();
//speed :�����ٶ� ��Χ -255-255
void Motor_SetSpeed(int speed, int id);


//speed1 :��೵���ٶ� ��Χ��-255~255
//spped2 :�Ҳ೵���ٶ� 
void Motor_GoSpeed(int speed1, int speed2);






