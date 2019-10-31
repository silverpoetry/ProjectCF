#include "Zigbee.h"
#define serialPort Serial2


 uint8_t zigbeeReceive[Zigbee_Message_Length];	//实时记录收到的信息
 uint8_t zigbeeMessage[Zigbee_Message_Length];//经过整理顺序后得到的信息






  Zigbee_BasicInfo Game;
  Zigbee_CarInfo Car[2];
 Zibee_PassengerInfo Passenger[2];

/***********************接口****************************/
void Zigbee_Init()
{
	serialPort.begin(115200);
	serialPort.setTimeout(30);
	
}






/***************************************************/

void DecodeBasicInfo()
{
	Game.Time = (zigbeeReceive[0] << 8) + zigbeeReceive[1];
	Game.GameState = (zigbeeReceive[2] & 0xC0) >> 6;

	Game.BallPos.X = ((zigbeeReceive[3] & 0x08) << 5) + zigbeeReceive[12];
	Game.BallPos.Y = ((zigbeeReceive[3] & 0x04) << 6) + zigbeeReceive[13];
	Game.BallExist = (zigbeeReceive[3] & 0x02) >> 1;

	Game.PassengerNum = 2;

}

void DecodeCarAInfo()
{
	Car[0].No = 0;

	Car[0].Area = (zigbeeReceive[2] & 0x20) >> 5;
	Car[0].pos.X = ((zigbeeReceive[2] & 0x08) << 5) + zigbeeReceive[4];
	Car[0].pos.Y = ((zigbeeReceive[2] & 0x04) << 6) + zigbeeReceive[5];
	Car[0].Task = (zigbeeReceive[3] & 0x01);

	Car[0].Score = (zigbeeReceive[14] << 8) + zigbeeReceive[15];
	Car[0].PickPsgNum = zigbeeReceive[18];
	Car[0].GetBallNum = zigbeeReceive[20];
	Car[0].SendBallNum = zigbeeReceive[22];
}

void DecodeCarBInfo()
{
	Car[1].No = 1;

	Car[1].Area = (zigbeeReceive[2] & 0x10) >> 4;
	Car[1].pos.X = ((zigbeeReceive[2] & 0x02) << 7) + zigbeeReceive[6];
	Car[1].pos.Y = ((zigbeeReceive[2] & 0x01) << 8) + zigbeeReceive[7];
	Car[1].Task = (~zigbeeReceive[3]) & 0x01;


	Car[1].Score = (zigbeeReceive[16] << 8) + zigbeeReceive[17];
	Car[1].PickPsgNum = zigbeeReceive[19];
	Car[1].GetBallNum = zigbeeReceive[21];
	Car[1].SendBallNum = zigbeeReceive[23];
}

void DecodePassenger0()
{
	Passenger[0].No = 0;
	Passenger[0].pos.X = ((zigbeeReceive[3] & 0x80) << 1) + zigbeeReceive[8];
	Passenger[0].pos.Y = ((zigbeeReceive[3] & 0x40) << 2) + zigbeeReceive[9];
}

void DecodePassenger1()
{
	Passenger[1].No = 1;
	Passenger[1].pos.X = ((zigbeeReceive[3] & 0x20) << 3) + zigbeeReceive[10];
	Passenger[1].pos.Y = ((zigbeeReceive[3] & 0x10) << 4) + zigbeeReceive[11];
}


void DecodeAll()
{
	DecodeBasicInfo();
	DecodeCarAInfo();
	DecodeCarBInfo();
	DecodePassenger0();
	DecodePassenger1();
}


bool  Zigbee_MessageRecord()
{
	if (!serialPort.available())return false;

	serialPort.readBytes(zigbeeMessage, Zigbee_Message_Length);
	for (int i = 0; i <= 32; i++)Serial.print(zigbeeMessage[i]), Serial.print(" ");
	Serial.println("");
	while (serialPort.available())serialPort.read();

	if (zigbeeMessage[Zigbee_Message_Length - 1] == 0x0a && zigbeeMessage[Zigbee_Message_Length - 2] == 0x0D)
	{
		DecodeAll(); return true;
	}
	return false;

}