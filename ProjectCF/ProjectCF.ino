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
	//Serial1.begin(115200);
	
}
void loop()
{
	while (true)
	{
		Debugger_DebugManagement();
		Debugger_SetWatch("A", Huidu_Read(2));
		Debugger_SetWatch("B", Huidu_Read(3));

	}

	
		//Motor_GoSpeed(120, 120);
	long long lastcnt11 = Motor_M1Cnt;
	long long lastcnt12 = Motor_M2Cnt;
	long long lastcnt21 = Motor_M1Cnt;
	long long lastcnt22 = Motor_M2Cnt;
	//Move_GoSpeed (SPEED, SPEED);
	while (1) {
		Debugger_DebugManagement ();
		//PL_GoStop ();
		//PL_GoStop
	}
	

}

