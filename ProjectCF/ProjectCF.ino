/*
 Name:		ProjectCF.ino
 Created:	2019/9/22 21:26:00
 Author:	The CFer
*/

#define pu(a) Serial.print((a))
#define sh(a) Serial.print(#a)
#include <Wire.h>
#include <Arduino.h>
#include <stdlib.h>
#include "IncludeList.h"

void setup()
{
	Motor_Init();
	//pinMode(34, OUTPUT);
	//pinMode(35, OUTPUT);
	//pinMode(11, OUTPUT);
	Serial.begin(9600);


}
void loop()
{
	if (Manager_Time_TakeTime(1000))
	{
		sh(The Motor 1 goes),pu((unsigned long)Motor_M1Cnt), sh(steps\n);
		sh(The Motor 2 goes), pu((unsigned long)Motor_M2Cnt), sh(steps\n);
		pu((double)Motor_M1Cnt / (double)Motor_M2Cnt),sh(\n);
		Motor_M1Cnt = 0;
		Motor_M2Cnt = 0;
	}
	/*while (1)
	{
		for (int i = 0; i < 10; i++)
		{
			digitalWrite(34, HIGH);
			digitalWrite(35, LOW);
			analogWrite(11, 120);
			delay(500);
		}
	}*/
	
		
	
	if (Serial.available() > 0)
	{
		String s ;
		s =Serial.readString();
		sh(Motor),pu(s),sh(-   listening\n);
		
		if (atoi(s.c_str()) == 1)
		{
			while (Serial.available() == 0);
			s = Serial.readString();
			Serial.println(atoi(s.c_str()));
			sh(Motor1  go as), pu(atoi(s.c_str())), sh(- speed\n);
			Motor_SetSpeed( atoi(s.c_str()),1);
		}
		else if (atoi(s.c_str()) == 2)
		{
			while (Serial.available() == 0);
			s = Serial.readString();
			sh(Motor2  go as),pu(atoi(s.c_str())),sh(- speed\n);
			Motor_SetSpeed(atoi(s.c_str()),2);
		}
		else if (atoi(s.c_str()) == 3)
		{
			int a, b; 
			while (Serial.available() == 0);
			s = Serial.readString();
			a = atoi(s.c_str());
			while (Serial.available() == 0);
			s = Serial.readString();
			b = atoi(s.c_str());
			sh(Motor1  go as), pu(a), sh(- speed\n);
			sh(Motor2  go as), pu(b), sh(- speed\n);
			Motor_GoSpeed(a, b);
		}
	}

}
