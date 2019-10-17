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
	pinMode(23, OUTPUT);
	pinMode(24, OUTPUT);
	Serial1.begin(9600);
	digitalWrite(23, HIGH);
	digitalWrite(24, LOW);
	Motor_Init();
 	Huidu_Init();
	Serial.begin(9600);

	Mpu_Init();
}
void loop()
{
	/*Motor_GoSpeed(70, 200);
	delay(3000);*/
	
		//Motor_GoSpeed(120, 120);
	
	
	
	
	long long lastcnt11 = Motor_M1Cnt;
	long long lastcnt12 = Motor_M2Cnt;
	long long lastcnt21 = Motor_M1Cnt;
	long long lastcnt22 = Motor_M2Cnt;
	while (1)
	{
		if (Manager_Time_TakeTime(3, 40))
		{

			while (Serial1.available() > 0)
				Serial1.print((char)Serial1.read());
		}

		if (Manager_Time_TakeTime(1, 1000))
		{
			sh(The Motor 1 goes), pu((unsigned long)(Motor_M1Cnt - lastcnt11)), sh(steps\n);
			sh(The Motor 2 goes), pu((unsigned long)(Motor_M2Cnt - lastcnt12)), sh(steps\n);
			lastcnt11 = Motor_M1Cnt;
			lastcnt12 = Motor_M2Cnt;
		}

		if (Manager_Time_TakeTime(2, 30))
		{
			int step1 = Motor_M1Cnt - lastcnt21;
			int step2 = Motor_M2Cnt - lastcnt22;
			if (step1 > step2)
				Motor_GoSpeed(Motor_M1Speed-1 , Motor_M2Speed);
			else if (step1 < step2)
				Motor_GoSpeed(Motor_M1Speed+1 , Motor_M2Speed);
			lastcnt21 = Motor_M1Cnt;
			lastcnt22 = Motor_M2Cnt;
		}
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
