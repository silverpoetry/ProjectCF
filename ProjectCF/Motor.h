#pragma once


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






