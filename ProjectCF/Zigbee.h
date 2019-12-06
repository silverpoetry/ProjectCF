/*************************************************************************
zigbee.h
������λ��������
����˵������USART2Ϊ����
	�ڳ���ʼ��ʱ��ʹ��zigbee_Init(&huart2)���г�ʼ��;
	�ڻص�������ʹ��zigbeeMessageRecord(void)��¼���ݣ������¿����ж�

����˵��
	struct BasicInfo Game; �������״̬��ʱ�䡢�˿�����С����Ч�ԡ�С��λ��
	struct CarInfo Car[2]; ���泵����Ϣ
	struct PassengerInfo Passenger[2]: ����˿͵���ź�λ��
	ͨ���ӿڻ�ȡ����	
*************************************************************************/

#pragma once
#include "IncludeList.h"
#include "Types.h"
#include <Arduino.h>
#define INVALID_ARG -1
#define Zigbee_Message_Length 32



struct Zigbee_BasicInfo
{
	uint8_t GameState;			//��Ϸ״̬��00δ��ʼ��01�����У�10��ͣ��11����
	uint16_t Time;					//����ʱ�䣬��0.1sΪ��λ
	uint8_t PassengerNum;		//�˿�������ǰΪ2
	struct Pos BallPos;//�����ռ���С����Ϣ
	uint16_t BallExist;			//������Ч��С��,0��ʾ������
};

struct Zigbee_CarInfo
{
	uint8_t No;							//������ţ�AΪ0�� BΪ1
	uint8_t Area;						//��������0�ڵ�·�ϣ������Թ����1���Թ���
	struct Pos pos;		//С��λ��
	uint16_t Score;					//�÷�
	uint8_t PickPsgNum;			//�ӵ�����Ա��
	uint8_t GetBallNum;			//�ɹ���ȡС����
	uint8_t SendBallNum;		//����������С����
	uint8_t Task;						//С������0Ϊ��Ԯ��1Ϊ�ռ�
};

struct Zibee_PassengerInfo
{
	uint8_t No; 						//�˿ͱ�ţ�ֻ��0��1
	struct Pos pos;
};

enum Zigbee_GameStateEnum
{
	GameNotStart,	//δ��ʼ
	GameGoing,		//������
	GamePause,		//��ͣ��
	GameOver			//�ѽ���
};

enum Zigbee_CarArea
{
	OnRoad,	//����Χ�ĵ�·��
	InMaze	//��������Թ���
};

enum Zigbee_CarTask
{
	Rescue,	 	//0,��Ԯ����
	Collect 	//1,�ռ�����
};


void Zigbee_Init();

bool  Zigbee_MessageRecord();








extern Zigbee_BasicInfo Game;
extern Zigbee_CarInfo Car[2];
extern Zibee_PassengerInfo Passenger[2];