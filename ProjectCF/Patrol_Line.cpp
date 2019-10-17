#include "Patrol_Line.h"
#include <math.h>

#define SEP_EPS 10

//判断在车与线的相对位置
int Patrol_Line_Position (int sensor_a, int sensor_b)
{	
	int sensor_a_value = Huidu_Read (sensor_a), sensor_b_value = Huidu_Read (sensor_b);

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

int Patrol_Line_PIDCorrection (void)
{

	return 0;
}

void Patrol (void)
{
	Huidu_Init ();
}
