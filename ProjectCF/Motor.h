#pragma once
#define Motor_NomorSpeed 120 
#define Motor_EncodePin1 2
#define Motor_EncodePin2 3
const int  Motor_Pin1 = 49;
const int  Motor_Pin2 = 47;
const int  Motor_Pin3 = 45;
const int  Motor_Pin4 = 43;
const int  Motor_EN1 = 11;
const int Motor_EN2 = 10;


extern volatile unsigned  long long  Motor_M1Cnt;
extern volatile unsigned long long  Motor_M2Cnt;



void Motor_Init();
void Motor_Stop();
//speed :车轮速度 范围 -255-255
void Motor_SetSpeed(int speed, int id);


//speed1 :左侧车轮速度 范围：-255~255
//spped2 :右侧车轮速度 
void Motor_GoSpeed(int speed1, int speed2);






