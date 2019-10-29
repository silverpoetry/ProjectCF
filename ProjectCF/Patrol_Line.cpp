#include "Patrol_Line.h"
#include <math.h>

#define SEP_EPS 15
#define MID_LINE 590

int sensor_a_value, sensor_b_value;
double PID_SumError = 0;
double PID_LastError = 0;
double PID_LastTime = 0;

//判断在车与线的相对位置
int PL_Position (int sensor_a, int sensor_b, int sensor_c, int sensor_d)
{
	sensor_a_value = Huidu_Read (sensor_a), sensor_b_value = Huidu_Read (sensor_b);


	if (Huidu_IsLine (sensor_a) && Huidu_IsLine (sensor_b) && Huidu_IsLine (sensor_c) && Huidu_IsLine (sensor_d)) {
		return 4; //到路口了
	}

	if (abs (sensor_a_value - sensor_b_value < SEP_EPS)) {

		//不在线上
		if (sensor_a_value < Huidu_LineValues[sensor_a] && sensor_b_value < Huidu_LineValues[sensor_b]) {
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

	//Move_GoSpeed (Motor_M1Speed + output, Motor_M2Speed - output);

	PID_LastTime = micros ();
	PID_LastError - newError;
	return output;
}
void PID_Refresh ()
{
	PID_SumError = 0;
	PID_LastError = 0;
	PID_LastTime = 0;

}

int PL_FindCenter (void) {
	Move_GoSpeed (150, 150);
	delay (500);
	Move_Stop ();
	return 1;
}

int PL_CrossRoad (int opt) {
	if (opt == 1) {
		Move_RotateLeft ();
		int cnt = 0;
		while (1) {
			delay (500);
			if (abs (sensor_b_value - MID_LINE) < SEP_EPS) {
				Move_RotateLeft ();//这一步复位
				return 1;
			}

			cnt++;
			if (cnt > 100) {
				break;
			}
		}
	}
	return 0;
}

int PL_PIDCorrection (int opt)
{
	int cnt = 0;
	while (1) {
		//sensor_b_value = analogRead(A5);
		//int position_state = PL_Position (2, 3, 1, 4);
//单光感-左
		if (opt == 2) {
			PL_Position (2, 3, 1, 4);
			int Err = MID_LINE - sensor_b_value;
			if (abs (Err) < SEP_EPS) {
				continue;
			}

			//output = PID_KP * newError + PID_KI * PID_SumError + PID_KD * deltaError;
			int output = PID_Output (Err, 0.05, 0, 0);
			sh (output is), pu (output); sh ("   ");
			sh (Err is), pu (Err); sh ("   ");
			sh (sensor is), pu (sensor_b_value); sh (\n);


			Move_GoSpeed (Motor_M1Speed - output, Motor_M2Speed + output);
			delay (100);
			Move_KeepRate ();
			Move_Refresh ();

			if (Manager_Time_TakeTime (5, 50)) {
				Debugger_SetWatch ("Error", Err);
				Debugger_SetWatch ("Output", output);
				Debugger_SetWatch ("M1Speed1", (Motor_M1Speed));
				Debugger_SetWatch ("M2Speed2", (Motor_M2Speed));
			}
			cnt++;
		}
		/*if (cnt > 50) {
			return 0;
		}*/
		/*if (position_state == 4) {
			return 1;//遇到路口
		}
		if (opt == 1) {

			if (position_state == 1) {
				PID_Refresh ();
				continue;
			}

			//Err为正，说明左地灰更黑，车向右偏，应向左调，左轮减速，右轮加速
			//黑的值小
			int Err = (sensor_a_value - sensor_b_value);
			int output = PID_Output (Err, 0.05, 0, 0);
			if (Manager_Time_TakeTime (2, 50))
			{
				Move_KeepRate (SPEED);
				Move_Refresh ();
			}
			if (Manager_Time_TakeTime (5, 100)) {
				Debugger_SetWatch ("Error", Err);
				Debugger_SetWatch ("Output", output);
				Debugger_SetWatch ("M1Speed1", (Motor_M1Speed));
				Debugger_SetWatch ("M2Speed2", (Motor_M2Speed));
			}

		}
		*/


	}
	return 0;
}

void Patrol (void)
{
	while (1) {
		int state = PL_PIDCorrection (2);
		if (state == 1) {
			if (PL_FindCenter ()) {
				if (PL_CrossRoad (1)) {
					continue;
				}
				else {//转弯没有找到线
					Move_Stop ();
					break;
				}
			}
		}
		else {
			Move_Stop ();
			return;
		}
	}
}

void PL_goline (int basic1, int basic2)
{
	if (Huidu_IsLine (1) && Huidu_IsLine (2))Motor_GoSpeed (basic1, basic2);

	if (Huidu_IsLine (1))Motor_GoSpeed (basic1, basic2 * 1.2);
	if (Huidu_IsLine (2))Motor_GoSpeed (basic1 * 1.4, basic2);
	if (Huidu_IsLine (3))Motor_GoSpeed (-100, -100), delay (50), Motor_GoSpeed (0, 0), delay (2000);


}