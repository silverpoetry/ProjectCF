#include "Distance.h"


void Distance_Init()
{
	
	//pinMode(ledpin, OUTPUT);
	pinMode(Distance_InputPin, INPUT);
	pinMode(Distance_OutPutPin, OUTPUT);
}

//��ȡ����
//��λ ����
long Distance_Get()

{
	long  sum = 0;
	//ѭ��20��ȡƽ��ֵ
	for(int i = 0;i<20;i++)
	{ 
		digitalWrite(Distance_OutPutPin, LOW); // ʹ���������������źŽӿڵ͵�ƽ2��s
		delayMicroseconds(2);
		digitalWrite(Distance_OutPutPin, HIGH); // ʹ���������������źŽӿڸߵ�ƽ10��s������������10��s
		delayMicroseconds(10);
		digitalWrite(Distance_OutPutPin, LOW); // ���ַ����������źŽӿڵ͵�ƽ
		long distance = pulseIn(Distance_InputPin, HIGH); // ��������ʱ��
		distance = distance*10 / 58; // ������ʱ��ת��Ϊ���루��λ�����ף�
	//	Serial.println(distance); //�������ֵ 
		if (distance>0&&distance<1000)
		{
			sum += distance;
		}
		else
		{
			i--;
		}
		delay(20);
	}
	sum /= 20;
	return sum;
	}