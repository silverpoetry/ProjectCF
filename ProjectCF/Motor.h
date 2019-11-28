#pragma once
#define Motor_SpeedBalance -30 //B�����ӵĲ����ٶ�
#define Motor_NomorSpeed 150
#define Motor_EncodePin1 3
#define Motor_EncodePin2 2
const int  Motor_Pin2 = 28;
const int  Motor_Pin1 = 29;
const int  Motor_Pin4 = 27;
const int  Motor_Pin3 = 26;
const int  Motor_EN1 = 9;
const int Motor_EN2 = 10; 
extern int Motor_M1Speed;
extern int Motor_M2Speed;

extern volatile unsigned  long long  Motor_M1Cnt;
extern volatile unsigned long long  Motor_M2Cnt;



void Motor_Init();
void Motor_Stop(int id);
//speed :�����ٶ� ��Χ -255-255
void Motor_SetSpeed(int speed, int id);


//speed1 :��೵���ٶ� ��Χ��-255~255
//spped2 :�Ҳ೵���ٶ� 
void Motor_GoSpeed(int speed1, int speed2);






