/*
 Name:		ProjectCF.ino
 Created:	2019/9/22 21:26:00
 Author:	The CFer
*/

#include <Servo.h>
#include <Esplora.h>
#include "IncludeList.h"
#include <Wire.h>
#include <Arduino.h>
#include <stdlib.h>


void setup()
{


	Motor_Init();
 	Huidu_Init();
	Debugger_Init();
	Serial.begin(9600);
	Distance_Init();
	//Zigbee_Init();
	//Arm_Init();
	//Serial1.begin(9600);
	
}
void goline(int basic1, int basic2)
{
	if (Huidu_IsLine(1) && Huidu_IsLine(2))Motor_GoSpeed(basic1,basic2);
	
	if (Huidu_IsLine(1))Motor_GoSpeed(basic1, basic2*1.2);
	if (Huidu_IsLine(2))Motor_GoSpeed(basic1*1.4, basic2);
	if (Huidu_IsLine(3))Motor_GoSpeed(-100, -100), delay(50), Motor_GoSpeed(0, 0), delay(2000);

	
}
void loop()
{

	//while (true)
	//{

	//	Debugger_DebugManagement();
	//	//Debugger_SetWatch("23", 333);
	//	//delay(30);
	//	//Debugger_SetWatch("dis", Distance_Get());
	//	/*if (Manager_Time_TakeTime(1,30))
	//	{
	//		goline(100, 105);
	//	}	*/
	//	Debugger_SetWatch("h1", Huidu_Read(1));
	//	Debugger_SetWatch("h2", Huidu_Read(2));
	//	Debugger_SetWatch("h3", Huidu_Read(3));
	//	//Debugger_SetWatch("h4", Huidu_Read(4));
	//	//Motor_Stop(1);
	//	/*delay(2000);
	//	Motor_Stop(1);
	//	Motor_GoSpeed(2, 150);
	//	delay(2000);
	//	Motor_Stop(2);*/
	//}
	/*Motor_GoSpeed(70, 200);
	delay(3000);*/
	
		//Motor_GoSpeed(120, 120);
	long long lastcnt11 = Motor_M1Cnt;
	long long lastcnt12 = Motor_M2Cnt;
	
	//Move_GoSpeed(60, 60);
	//Move_Refresh();
	//while (true)
	//{
	//	Debugger_DebugManagement();
	//	/*if (Manager_Time_TakeTime(1,300))
	//	{
	//		//Debugger_SetWatch("Huidu1" ,Huidu_Read(1));
	//		//Debugger_SetWatch("Time", millis());
	//	}*/
	//	if (Manager_Time_TakeTime(2, 50))
	//	{
	//		Move_KeepRate();
	//		Move_Refresh ();
	//	}
	//	
	//}
	
	Move_GoSpeed(120, 120);
	Move_Refresh();
	while (1)
	{
		Debugger_DebugManagement();

		//Debugger_SetWatch("ss", 123);
		if (Manager_Time_TakeTime(1, 1000))
		{
			Debugger_SetWatch("Speed1", Motor_M1Cnt - lastcnt11);
			Debugger_SetWatch("Speed2", Motor_M2Cnt - lastcnt12);
			lastcnt11 = Motor_M1Cnt;
			lastcnt12 = Motor_M2Cnt;
			Debugger_SetWatch("Huidu1", Huidu_Read(1));
			Debugger_SetWatch("Huidu2", Huidu_Read(1));
			Debugger_SetWatch("Power1", Motor_M1Speed);
			Debugger_SetWatch("Power2", Motor_M2Speed);
			//Debugger_SetWatch("Distance", Distance_Get());
		}
	/*	if (Manager_Time_TakeTime(2,30))
		{
			Move_KeepRate();
		}*/
	
		
	}

	/*while (1)
	{
		if (Serial1.available() > 0)
			Serial.print(Serial1.read());
	}*/




	//if (Serial.available() > 0)
	//{
	//	String s ;
	//	s =Serial.readString();
	//	sh(Motor),pu(s),sh(-   listening\n);

	//	if (atoi(s.c_str()) == 1)
	//	{
	//		while (Serial.available() == 0);
	//		s = Serial.readString();
	//		Serial.println(atoi(s.c_str()));
	//		sh(Motor1  go as), pu(atoi(s.c_str())), sh(- speed\n);
	//		Motor_SetSpeed(1, atoi(s.c_str()));
	//	}
	//	else if (atoi(s.c_str()) == 2)
	//	{
	//		while (Serial.available() == 0);
	//		s = Serial.readString();
	//		sh(Motor2  go as),pu(atoi(s.c_str())),sh(- speed\n);
	//		Motor_SetSpeed(2, atoi(s.c_str()));
	//	}
	//	else if (atoi(s.c_str()) == 3)
	//	{
	//		int a, b;
	//		while (Serial.available() == 0);
	//		s = Serial.readString();
	//		a = atoi(s.c_str());
	//		while (Serial.available() == 0);
	//		s = Serial.readString();
	//		b = atoi(s.c_str());
	//		sh(Motor1  go as), pu(a), sh(- speed\n);
	//		sh(Motor2  go as), pu(b), sh(- speed\n);
	//		Motor_GoSpeed(a, b);
	//	}
	//}
	//
	//long long ind = 0;
	//while (1)
	//{
	//	Mpu_GetValues();
	//	pu(Mpu_Roll), sh(\n);
	//		//sh(_ Roll),pu(Mpu_Roll),sh(_ Pitch: ),pu(Mpu_Pitch), sh(\n);
	//	delay(100);
	//}
}
//#include "Wire.h"
//void setup() {
//	Serial.begin(9600); // Leonardo: wait for serial port to connect
//	while (!Serial) {}
//	Serial.println();
//	Serial.println("I2C scanner. Scanning ...");
//	byte count = 0;
//	Wire.begin();
//	for (byte i = 8; i < 120; i++) {
//		Wire.beginTransmission(i);
//		if (Wire.endTransmission() == 0) {
//			Serial.print("Found address: ");
//			Serial.print(i, DEC);
//			Serial.print(" (0x");
//			Serial.print(i, HEX);
//			Serial.println(")");
//			count++;
//			delay(1); // maybe unneeded?
//		} // end of good response
//	} // end of for loop
//	Serial.println("Done.");
//	Serial.print("Found ");
//	Serial.print(count, DEC);
//	Serial.println(" device(s).");
//} // end of setup
//void loop() {}
