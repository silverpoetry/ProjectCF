#include "Zigbee.h"
#define serialPort Serial

#define CRC_POLY 0xa001 //CRC-16，多项式0x8005；0xa001为它的倒序






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

unsigned short crc16(uint8_t *data_p, unsigned char length)

{

	unsigned char i, j;

	unsigned short crc = 0xffff; //初始值0xffff



	for (i = 0; i < length; ++i)

	{

		crc ^= (unsigned short)(0xff & data_p[i]);

		for (j = 0; j < 8; j++)

		{

			if (crc & 0x0001)

				crc = (crc >> 1) ^ CRC_POLY;

			else

				crc >>= 1;

		}

	}

	// crc = (crc << 8) | (crc >> 8 & 0xff);

	return crc;

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

void DecodeCarAInfo()
{
	Car[0].No = 0;

	Car[0].Area = (zigbeeMessage[2] & 0x20) >> 5;
	Car[0].pos.X = ((zigbeeMessage[2] & 0x08) << 5) + zigbeeMessage[4];
	Car[0].pos.Y = ((zigbeeMessage[2] & 0x04) << 6) + zigbeeMessage[5];
	Car[0].Task = (zigbeeMessage[3] & 0x01);

	Car[0].Score = (zigbeeMessage[14] << 8) + zigbeeMessage[15];
	Car[0].PickPsgNum = zigbeeMessage[18];
	Car[0].GetBallNum = zigbeeMessage[20];
	Car[0].SendBallNum = zigbeeMessage[22];
}

void DecodeCarBInfo()
{
	Car[1].No = 1;

	Car[1].Area = (zigbeeMessage[2] & 0x10) >> 4;
	Car[1].pos.X = ((zigbeeMessage[2] & 0x02) << 7) + zigbeeMessage[6];
	Car[1].pos.Y = ((zigbeeMessage[2] & 0x01) << 8) + zigbeeMessage[7];
	Car[1].Task = (~zigbeeMessage[3]) & 0x01;


	Car[1].Score = (zigbeeMessage[16] << 8) + zigbeeMessage[17];
	Car[1].PickPsgNum = zigbeeMessage[19];
	Car[1].GetBallNum = zigbeeMessage[21];
	Car[1].SendBallNum = zigbeeMessage[23];
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
	DecodeCarAInfo();
	DecodeCarBInfo();
	DecodePassenger0();
	DecodePassenger1();
}
unsigned long zigbee_lasttime = 0;
uint8_t zReceive[Zigbee_Message_Length];//经过整理顺序后得到的信息
long  sum = 0;
bool  Zigbee_MessageRecord()
{
	if (!serialPort.available())return false;

	serialPort.readBytes(zigbeeMessage, Zigbee_Message_Length);
	while (serialPort.available())serialPort.read();
	
	//校验
	if (crc16(zigbeeMessage,28)== ( ( short(zigbeeMessage[28])<<8)+zigbeeMessage[29]))
	{
		DecodeAll();
		return true;

	}
	return false;
	//for (int i = 0; i <= 32; i++)Serial.print(zigbeeMessage[i]), Serial.print(" ");
	//Serial.println("");
	//if (zigbeeMessage[Zigbee_Message_Length - 1] == 0x0a && zigbeeMessage[Zigbee_Message_Length - 2] == 0x0D)
	//{
	//	//上次是最近读取的
	//	if (millis()-zigbee_lasttime<500)
	//	{
	//		//检验读取的正确性
	//		Zigbee_CarInfo cc;
	//		if (OurCarIndex==0)
	//		{
	//			//0号车
	//			DecodeCarAInfo(cc);
	//		}
	//		else
	//		{
	//			DecodeCarBInfo(cc);
	//		}
	//		if ((abs(cc.pos.X - OurCar.pos.X) + abs(cc.pos.Y - OurCar.pos.Y) )> 80)return false;
	//		
	//	}
	//	
	//	for (int i = 0; i <= 32; i++)Serial.print (zigbeeMessage[i]), Serial.print (" ");
	//	Serial.println ("");
	//	
	//	DecodeAll();
	//	zigbee_lasttime = millis(); 
	//	return true;
	//}
	return false;

}