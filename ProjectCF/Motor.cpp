#include "IncludeList.h"
#include "Motor.h"
//
volatile unsigned long long  Motor_M1Cnt=0;
volatile unsigned long long  Motor_M2Cnt=0;
int Motor_SpeedBalance = -30;
int Motor_M1Speed;
int Motor_M2Speed;


void Motor_Encode1_Arrived()
{
	Motor_M1Cnt++;

}
void Motor_Encode2_Arrived()
{
	Motor_M2Cnt++;

}
void Motor_Init()
{

		pinMode(Motor_Pin1, OUTPUT);
		pinMode(Motor_Pin2, OUTPUT);
		pinMode(Motor_Pin3, OUTPUT);
		pinMode(Motor_Pin4, OUTPUT);
		pinMode(Motor_EN1, OUTPUT);
		pinMode(Motor_EN2, OUTPUT);
		attachInterrupt(digitalPinToInterrupt(Motor_EncodePin2),Motor_Encode1_Arrived , RISING);
		attachInterrupt(digitalPinToInterrupt(Motor_EncodePin1),Motor_Encode2_Arrived , RISING);

}


void Motor_Stop(int id)
{
	
	if (id==1)
	{
		analogWrite(Motor_EN1, 0);
	digitalWrite(Motor_Pin1, HIGH);
	digitalWrite(Motor_Pin2, HIGH);

	}
	else if(id==2)
	{

		analogWrite(Motor_EN2, 0);
	digitalWrite(Motor_Pin3, HIGH);
	digitalWrite(Motor_Pin4, HIGH);
	}

}
void forward(int id)
{
	//forward ǰ��
	if (id==1)
	{
		digitalWrite(Motor_Pin1, HIGH);
		digitalWrite(Motor_Pin2, LOW);
		return;

	}
	
	digitalWrite(Motor_Pin3, HIGH);
	digitalWrite(Motor_Pin4, LOW);
}
void back(int id)
{
	if (id==1)
	{
		digitalWrite(Motor_Pin1, LOW);
		digitalWrite(Motor_Pin2, HIGH);
		return;
	}
	
	digitalWrite(Motor_Pin3, LOW);
	digitalWrite(Motor_Pin4, HIGH);
}

void Motor_SetSpeed(int speed, int id)
{
	if(id==1)
	{
		//Serial.println(speed);
	if (speed > 0)forward(id), analogWrite(Motor_EN1, abs(speed));
	if (speed < 0)back(id), analogWrite(Motor_EN1, abs(speed));
	if (speed == 0)Motor_Stop(id);
	Motor_M1Speed = speed;
	}
	else
	{
		Motor_M2Speed = speed;
		if(abs(speed)<245&&abs(speed)>10)
		{ 
			int fuhao = speed / abs(speed);
			speed = fuhao * (abs(speed) + Motor_SpeedBalance);
		}
		if (speed >= 0)forward(id), analogWrite(Motor_EN2, abs(speed));
		if (speed < 0)back(id), analogWrite(Motor_EN2, abs(speed));
		if (speed == 0)Motor_Stop(id);
		

	}
}
//���Ƶ���н�
//speed1 :��೵���ٶ� ��Χ��-255~255
//spped2 :�Ҳ೵���ٶ� 
void Motor_GoSpeed(int speed1, int speed2)
{
	if (speed1 > 255)
		speed1 = 255;
	if (speed2 > 255)
		speed2 = 255;
	/*if (speed1 < 1)
		speed1 = 1;
	if (speed2 < 1)
		speed2 = 1;*/
	Motor_SetSpeed(speed1, 1);
	Motor_SetSpeed(speed2, 2);
	
}




