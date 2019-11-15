/*************************************************************************
zigbee.h
接收上位机的数据
接收说明（以USART2为例）
	在程序开始的时候使用zigbee_Init(&huart2)进行初始化;
	在回调函数中使用zigbeeMessageRecord(void)记录数据，并重新开启中断

数据说明
	struct BasicInfo Game; 储存比赛状态、时间、乘客数、小球有效性、小球位置
	struct CarInfo Car[2]; 储存车辆信息
	struct PassengerInfo Passenger[2]: 储存乘客的序号和位置
	通过接口获取数据	
*************************************************************************/

#pragma once
#include "IncludeList.h"
#include "Types.h"
#include <Arduino.h>
#define INVALID_ARG -1
#define Zigbee_Message_Length 32



struct Zigbee_BasicInfo
{
	uint8_t GameState;			//游戏状态：00未开始，01进行中，10暂停，11结束
	uint16_t Time;					//比赛时间，以0.1s为单位
	uint8_t PassengerNum;		//乘客数，当前为2
	struct Pos BallPos;//物资收集点小球信息
	uint16_t BallExist;			//存在有效的小球,0表示不存在
};

struct Zigbee_CarInfo
{
	uint8_t No;							//车辆编号，A为0， B为1
	uint8_t Area;						//车辆区域：0在道路上（不在迷宫里），1在迷宫里
	struct Pos pos;		//小车位置
	uint16_t Score;					//得分
	uint8_t PickPsgNum;			//接到的人员数
	uint8_t GetBallNum;			//成功获取小球数
	uint8_t SendBallNum;		//运至出发点小球数
	uint8_t Task;						//小车任务，0为救援，1为收集
};

struct Zibee_PassengerInfo
{
	uint8_t No; 						//乘客编号，只有0和1
	struct Pos pos;
};

enum Zigbee_GameStateEnum
{
	GameNotStart,	//未开始
	GameGoing,		//进行中
	GamePause,		//暂停中
	GameOver			//已结束
};

enum Zigbee_CarArea
{
	OnRoad,	//在周围的道路上
	InMaze	//在中央的迷宫里
};

enum Zigbee_CarTask
{
	Rescue,	 	//0,救援任务
	Collect 	//1,收集任务
};


void Zigbee_Init();

bool  Zigbee_MessageRecord();








extern Zigbee_BasicInfo Game;
extern Zigbee_CarInfo Car[2];
extern Zibee_PassengerInfo Passenger[2];