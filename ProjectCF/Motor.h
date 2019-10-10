#pragma once
#define Motor_NomorSpeed 120 

const int  Motor_Pin1[3] = { 0,1,2 };
const int  Motor_Pin2[3] = { 0,1,2 };
const int  Motor_Pin3[3] = { 0,1,2 };
const int  Motor_Pin4[3] = { 0,1,2 };
const int  Motor_EN1[3] = { 0 ,9,10 };
const int Motor_EN2[3] = { 0,9,10 };


void Motor_Init();
void Motor_Stop();
//speed :车轮速度 范围 0-255
void Motor_SetSpeed(int speed);
//speed1 :左侧车轮速度 范围：-255~255
//spped2 :右侧车轮速度 
void Motor_GoSpeed(int speed1, int speed2);






