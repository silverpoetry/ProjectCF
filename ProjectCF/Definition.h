#pragma once
//--------------------------�ο���----------------------------------------

//Ѳ�ߵ��������Ӳο��ٶ�
#define SPEED 150
#define SPEED2 150
//��Χ��λ���ߵ�ƫ����
#define Outer_eps 5

//---------------------------ģ��-----------------------------------------
//������

#define Distance_InputPin  49 // ���峬�����źŽ��սӿ�
#define Distance_OutPutPin  48// ���峬�����źŷ����ӿ�
#define Distance_InputPin2  44 // ���峬�����źŽ��սӿ�
#define Distance_OutPutPin2  45// ���峬�����źŷ����ӿ�
#define Distance_InputPin0  36 // ���峬�����źŽ��սӿ�
#define Distance_OutPutPin0  35// ���峬�����źŷ����ӿ�

//�Ҷ�
const int Huidu_Pins[] = { A0,A1,A2,A9,A8,A3 };
const int Huidu_LineValues[] = { 150, 150, 150, 150,150,150,100 };


//��е��
const int Arm_Pins[] = { 4,5,2,46 };

//΢������
#define MicroMove_Pin A12 //left_front
#define MicroMove_Pin2 48 //right_front
#define MicroMove_Pin3 45 //left_back
#define MicroMove_Pin4 49 //right_back

//���
extern int Motor_SpeedBalance; //B�����ӵĲ����ٶ�
#define Motor_NomorSpeed 150
#define Motor_EncodePin1 7
#define Motor_EncodePin2 9
const int  Motor_Pin2 = 38;
const int  Motor_Pin1 = 39;
const int  Motor_Pin4 = 40;
const int  Motor_Pin3 = 41;
const int  Motor_EN1 = 9;
const int Motor_EN2 = 7;
