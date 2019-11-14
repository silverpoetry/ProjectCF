#include "Zigbee.h"
#define serialPort Serial2



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
	Game.Time = (zigbeeMessage[0] << 8) + zigbeeMessage[1];
	Game.GameState = (zigbeeMessage[2] & 0xC0) >> 6;

	Game.BallPos.X = ((zigbeeMessage[3] & 0x08) << 5) + zigbeeMessage[12];
	Game.BallPos.Y = ((zigbeeMessage[3] & 0x04) << 6) + zigbeeMessage[13];
	Game.BallExist = (zigbeeMessage[3] & 0x02) >> 1;

	Game.PassengerNum = 2;

}

void DecodeCarAInfo(Zigbee_CarInfo& Car)
{
	Car.No = 0;

	Car.Area = (zigbeeMessage[2] & 0x20) >> 5;
	Car.pos.X = ((zigbeeMessage[2] & 0x08) << 5) + zigbeeMessage[4];
	Car.pos.Y = ((zigbeeMessage[2] & 0x04) << 6) + zigbeeMessage[5];
	Car.Task = (zigbeeMessage[3] & 0x01);

	Car.Score = (zigbeeMessage[14] << 8) + zigbeeMessage[15];
	Car.PickPsgNum = zigbeeMessage[18];
	Car.GetBallNum = zigbeeMessage[20];
	Car.SendBallNum = zigbeeMessage[22];
}

void DecodeCarBInfo(Zigbee_CarInfo& Car)
{
	Car.No = 1;

	Car.Area = (zigbeeMessage[2] & 0x10) >> 4;
	Car.pos.X = ((zigbeeMessage[2] & 0x02) << 7) + zigbeeMessage[6];
	Car.pos.Y = ((zigbeeMessage[2] & 0x01) << 8) + zigbeeMessage[7];
	Car.Task = (~zigbeeMessage[3]) & 0x01;


	Car.Score = (zigbeeMessage[16] << 8) + zigbeeMessage[17];
	Car.PickPsgNum = zigbeeMessage[19];
	Car.GetBallNum = zigbeeMessage[21];
	Car.SendBallNum = zigbeeMessage[23];
}

void DecodePassenger0()
{
	Passenger[0].No = 0;
	Passenger[0].pos.X = ((zigbeeMessage[3] & 0x80) << 1) + zigbeeMessage[8];
	Passenger[0].pos.Y = ((zigbeeMessage[3] & 0x40) << 2) + zigbeeMessage[9];
}

void DecodePassenger1()
{
	Passenger[1].No = 1;
	Passenger[1].pos.X = ((zigbeeMessage[3] & 0x20) << 3) + zigbeeMessage[10];
	Passenger[1].pos.Y = ((zigbeeMessage[3] & 0x10) << 4) + zigbeeMessage[11];
}


void DecodeAll()
{
	DecodeBasicInfo();
	DecodeCarAInfo(Car[0]);
	DecodeCarBInfo(Car[1]);
	DecodePassenger0();
	DecodePassenger1();
}
unsigned long zigbee_lasttime = 0;
uint8_t zReceive[Zigbee_Message_Length];//经过整理顺序后得到的信息
long  sum = 0;
bool  Zigbee_MessageRecord()
{
	if (!serialPort.available())return false;

	serialPort.readBytes(zReceive, Zigbee_Message_Length);
	while (serialPort.available())serialPort.read();
	//if (!Manager_Time_TakeTime(33,500))
	//{

	//
	//	sum = 0;
	//	for (int i = 0; i < Zigbee_Message_Length; i++)
	//	{
	//	sum += abs(zigbeeMessage[i] - zReceive[i]);
	//	}
	//	if (sum > 300)return false;
	//}
	
	memcpy(zigbeeMessage, zReceive, sizeof(uint16_t)*Zigbee_Message_Length);
	if (zigbeeMessage[Zigbee_Message_Length - 1] == 0x0a && zigbeeMessage[Zigbee_Message_Length - 2] == 0x0D)
	{
		//上次是最近读取的
		if (millis()-zigbee_lasttime<500)
		{
			//检验读取的正确性
			Zigbee_CarInfo cc;
			if (OurCarIndex==0)
			{
				//0号车
				DecodeCarAInfo(cc);
			}
			else
			{
				DecodeCarBInfo(cc);
			}
			if ((abs(cc.pos.X - OurCar.pos.X) + abs(cc.pos.Y - OurCar.pos.Y) )> 80)return false;
			
		}
		
		//for (int i = 0; i <= 32; i++)Serial.print (zigbeeMessage[i]), Serial.print (" ");
		//Serial.println ("");
		
		DecodeAll();
		zigbee_lasttime = millis(); 
		return true;
	}
	return false;

}