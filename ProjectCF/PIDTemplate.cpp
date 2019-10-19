#include "IncludeList.h"
double PID_SumError;
double PID_LastError;
double PID_KP;
double PID_KI;
double PID_KD;
int PID_LastTime;

void PID_Output(double newError)
{
	double deltatime = micros() - PID_LastTime;
	PID_SumError += newError*deltatime;
	double deltaError = (newError - PID_LastError)/deltatime;

	int output = PID_KP * newError + PID_KI * PID_SumError + PID_KD * deltaError;
	Motor_GoSpeed(Motor_NomorSpeed - output, Motor_NomorSpeed + output);
	
	PID_LastTime = micros();
	PID_LastError - newError;
}
void PID_Refresh()
{
	 PID_SumError=0;
	 PID_LastError=0;
	
	int PID_LastTime=0;

}