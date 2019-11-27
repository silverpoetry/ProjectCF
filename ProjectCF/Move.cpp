#include "IncludeList.h"
#include "Move.h"

#include <math.h>

long long Move_LastCnt1;

long long Move_LastCnt2;
double Motor_Rate=1;
void Move_Refresh()
{
	Move_LastCnt1 = Motor_M1Cnt;
	Move_LastCnt2 = Motor_M2Cnt;
}
void Move_GoSpeed(int speed1, int speed2)
{
	Motor_GoSpeed(speed1, speed2);
	Motor_Rate = double(speed1) / double(speed2);
}
void Move_Fucker()
{
	Move_Refresh();
	while (true)
	{
		if (Serial.available() > 0)return;
		delay(20);
		Move_KeepRate();
	}
}
void Move_KeepRate ()
{
	int step1 = Motor_M1Cnt - Move_LastCnt1;
	if (Motor_M1Speed < 0)step1 *= -1;

	int step2 = Motor_M2Cnt - Move_LastCnt2;
	if (Motor_M2Speed < 0)step2 *= -1;
	double KP = 1;
	int err = (step2 * Motor_Rate - step1);

	Debugger_SetWatch ("ActualSpeed1", step1);
	Debugger_SetWatch ("ActualSpeed2", step2);
	
	Debugger_SetWatch ("M1Speed1", (Motor_M1Speed));
	Debugger_SetWatch ("M2Speed2", (Motor_M2Speed));
	Debugger_SetWatch ("err", (err));

//}
	Motor_GoSpeed (Motor_M1Speed, min (255, max (Motor_M2Speed - int (KP * err), -255)));
	Move_Refresh ();
	//Motor_GoSpeed (min(255,max(Motor_M1Speed + int(KP * err),0)), 120);

	//sh (\n err is ); pu (err);

}
int Move_RotateLeft (void) {

	Move_GoSpeed (-120, 120);
}

int Move_RotateRight (void) {

	Move_GoSpeed (120, -120);
}

void Move_Stop (void) {
	Motor_GoSpeed(-Motor_M1Speed, -Motor_M2Speed);
	delay(50);
	Motor_Stop (1);
	Motor_Stop (2);
}
void Move_Gotime(int speed1,int speed2, int time)
{
	Motor_GoSpeed(speed1, speed2);
	delay(time);
	Move_Stop();
}
void Move_GotimeWithoutStop(int speed, int time)
{
	Motor_GoSpeed(speed, speed);
	delay(time);
	
}
void Move_GoStraightTime(int speed, int time)
{
	Mpu_RecordAngle();
	while (!Manager_Time_TakeTime(64,time))
	{
		//Mpu_ReadData();
		Mpu_AdjustStraight(speed);
	
	}
	Move_Stop();
}
void Move_TurnLeft (int speed) {
		
	Motor_GoSpeed (1, speed);
}