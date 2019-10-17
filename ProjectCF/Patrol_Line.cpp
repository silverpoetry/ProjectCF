#include "Patrol_Line.h"
#include <math.h>

#define SEP_EPS 10

//�ж��ڳ����ߵ����λ��
int Patrol_Line_Position (int sensor_a, int sensor_b)
{	
	int sensor_a_value = Huidu_Read (sensor_a), sensor_b_value = Huidu_Read (sensor_b);

	if (abs(sensor_a_value - sensor_b_value < SEP_EPS)) {

		//��������
		if (sensor_a_value < Huidu_LineValues[sensor_a] && sensor_b_value < Huidu_LineValues[sensor_b]){
			//�˴����Բ���ʵ���ж�С����ȫ���ߵ���һ��
			return 0;
		}

		//������
		return 1;
		
	}

	//ƫ��
	else if (sensor_a_value > Huidu_LineValues[sensor_a] && sensor_b_value < Huidu_LineValues[sensor_b]) {
		return 2;
	}

	//ƫ��
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
