#include "Patrol_Line.h"
#include <math.h>

#define SEP_EPS 10

int sensor_a_value, sensor_b_value;
double PID_SumError = 0;
double PID_LastError = 0;
double PID_LastTime = 0;

//判断在车与线的相对位置
int Patrol_Line_Position (int sensor_a, int sensor_b)
{	
	sensor_a_value = Huidu_Read (sensor_a), sensor_b_value = Huidu_Read (sensor_b);

	if (abs(sensor_a_value - sensor_b_value < SEP_EPS)) {

		//不在线上
		if (sensor_a_value < Huidu_LineValues[sensor_a] && sensor_b_value < Huidu_LineValues[sensor_b]){
			//此处可以补充实现判断小车完全在线的哪一侧
			return 0;
		}

		//在线上
		return 1;
	}

	//偏右
	else if (sensor_a_value > Huidu_LineValues[sensor_a] && sensor_b_value < Huidu_LineValues[sensor_b]) {
		return 2;
	}

	//偏左
	else if (sensor_a_value < Huidu_LineValues[sensor_a] && sensor_b_value > Huidu_LineValues[sensor_b]) {
		return 3;
	}
}


int PID_Output (double newError, double PID_KP, double PID_KI, double PID_KD)
{
	double deltatime = micros () - PID_LastTime;
	PID_SumError += newError * deltatime;
	double deltaError = (newError - PID_LastError) / deltatime;

	int output = PID_KP * newError + PID_KI * PID_SumError + PID_KD * deltaError;
	//Debugger_SetWatch ("Output", output);

	Move_GoSpeed (Motor_M1Speed - output, Motor_M2Speed + output);

	PID_LastTime = micros ();
	PID_LastError - newError;
}
void PID_Refresh ()
{
	PID_SumError = 0;
	PID_LastError = 0;
	PID_LastTime = 0;

}


int Patrol_Line_PIDCorrection (void)
{

	while (true) {

		int position_state = Patrol_Line_Position (2, 3);
		if (position_state == 1) {
			PID_Refresh ();
			continue;
		}

		//Err为正，说明左地灰更黑，车向右偏，应向左调，左轮减速，右轮加速
		int Err = sensor_a_value - sensor_b_value;
		int output =  PID_Output (Err, 0.3, 0, 0);
		if (Manager_Time_TakeTime (2, 50))
		{
			Move_KeepRate ();
			Move_Refresh ();
		}
		if(Manager_Time_TakeTime (5, 100)) {
			Debugger_SetWatch ("Error", Err);
			Debugger_SetWatch ("Output", output);
			Debugger_SetWatch ("M1Speed1", (Motor_M1Speed));
			Debugger_SetWatch ("M2Speed2", (Motor_M2Speed));
		}
	}

	return 0;
}

void Patrol (void)
{
	Huidu_Init ();
}
