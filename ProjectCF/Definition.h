#pragma once
//--------------------------参考量----------------------------------------

//巡线的左右轮子参考速度
#define SPEED 150
#define SPEED2 150
//外围上位机走点偏移量
#define Outer_eps 5

//---------------------------模块-----------------------------------------
//超声波

#define Distance_InputPin  23 // 定义超声波信号接收接口
#define Distance_OutPutPin  22// 定义超声波信号发出接口
#define Distance_InputPin2  17 // 定义超声波信号接收接口
#define Distance_OutPutPin2  16// 定义超声波信号发出接口
#define Distance_InputPin0  19 // 定义超声波信号接收接口
#define Distance_OutPutPin0  18// 定义超声波信号发出接口

//灰度
const int Huidu_Pins[] = { A0,A1,A11,A10,A9,A8 };
const int Huidu_LineValues[] = { 100,100, 100, 100,100,100,100 };


//机械臂
const int Arm_Pins[] = { 4,5,2,46 };

//微动开关
#define MicroMove_Pin 11 //left_front
#define MicroMove_Pin2 10 //right_front
#define MicroMove_Pin3 45 //left_back
#define MicroMove_Pin4 49 //right_back

//电机
extern int Motor_SpeedBalance; //B轮增加的补偿速度
#define Motor_NomorSpeed 150
#define Motor_EncodePin1 7
#define Motor_EncodePin2 9
const int  Motor_Pin2 = 42;
const int  Motor_Pin1 = 43;
const int  Motor_Pin4 = 44;
const int  Motor_Pin3 = 45;
const int  Motor_EN1 = 44;
const int Motor_EN2 = 45;
