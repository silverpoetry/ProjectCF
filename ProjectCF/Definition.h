#pragma once
//--------------------------�ο���----------------------------------------

//Ѳ�ߵ��������Ӳο��ٶ�
#define SPEED 150
#define SPEED2 150
//��Χ��λ���ߵ�ƫ����
#define Outer_eps 5

//---------------------------ģ��-----------------------------------------
//������

#define Distance_InputPin0  41 // ���峬�����źŽ��սӿ�
#define Distance_OutPutPin0  40// ���峬�����źŷ����ӿ�
#define Distance_InputPin2  39 // ���峬�����źŽ��սӿ�
#define Distance_OutPutPin2  38// ���峬�����źŷ����ӿ�
#define Distance_InputPin  44// ���峬�����źŽ��սӿ�
#define Distance_OutPutPin  45// ���峬�����źŷ����ӿ�

//�Ҷ�
const int Huidu_Pins[] = { A0,A1,A3,A7,A10,A14 };
const int Huidu_LineValues[] = { 100,100, 100, 100,100,100,100 };


//��е��
const int Arm_Pins[] = { 4,5,2,46 };

//΢������
#define MicroMove_Pin 49//left_front
#define MicroMove_Pin2 A15 //right_front
#define MicroMove_Pin3 49 //left_back
#define MicroMove_Pin4 49 //right_back

//���
extern int Motor_SpeedBalance; //B�����ӵĲ����ٶ�
#define Motor_NomorSpeed 150
#define Motor_EncodePin1 7
#define Motor_EncodePin2 9//ourcar

const int  Motor_Pin4 = 31;
const int  Motor_Pin3 = 30;
const int  Motor_Pin1 = 32;
const int  Motor_Pin2 = 33;


const int  Motor_EN2 =7;
const int Motor_EN1 =9;
