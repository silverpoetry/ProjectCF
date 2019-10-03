/*
 Name:		ProjectCF.ino
 Created:	2019/9/22 21:26:00
 Author:	The CFer
*/
#include <Arduino.h>

#include "string.h"
#include "IncludeList.h"

#define pu(a) Serial.print(a)
#define sh(a) Serial.print(#a)
void setup()
{
	Distance_Init();
	Serial.begin(9600);


}
void loop()
{
	static int i = 1;
	i++;
	sh(Test), pu(i), sh(\n);
	Serial.println(Distance_Get());

}
