#include "IncludeList.h"
#include "Motor.h"

void Motor_Init()
{
	Rep(i, 1, 2)
	{

		pinMode(Motor_Pin1[i], OUTPUT);
		pinMode(Motor_Pin2[i], OUTPUT);
		pinMode(Motor_Pin3[i], OUTPUT);
		pinMode(Motor_Pin4[i], OUTPUT);
	}
}
void Motor_Stop(int id)
{
	
		digitalWrite(Motor_Pin1[id], LOW);
		digitalWrite(Motor_Pin2[id], LOW);
		digitalWrite(Motor_Pin3[id], LOW);
		digitalWrite(Motor_Pin4[id], LOW);

	
}
void forward(int id)
{
	//forward Ç°½ø
	digitalWrite(Motor_Pin1[id], HIGH);
	digitalWrite(Motor_Pin2[id], LOW);
	digitalWrite(Motor_Pin3[id], HIGH);
	digitalWrite(Motor_Pin4[id], LOW);
}
void back(int id)
{
	digitalWrite(Motor_Pin1[id], LOW);
	digitalWrite(Motor_Pin2[id], HIGH);
	digitalWrite(Motor_Pin3[id], LOW);
	digitalWrite(Motor_Pin4[id], HIGH);
}

void Motor_SetSpeed(int speed,int id)
{
	if (speed > 0)forward(id), analogWrite(Motor_EN1[id], speed), analogWrite(Motor_EN2[id], speed);
	if (speed < 0)back(id), analogWrite(Motor_EN1[id], abs(speed)), analogWrite(Motor_EN2[id], speed);
	if (speed == 0)Motor_Stop(id);
}

void Motor_GoSpeed(int speed1, int speed2)
{
	Motor_SetSpeed(speed1, 1);
	Motor_SetSpeed(speed2, 2);
}




