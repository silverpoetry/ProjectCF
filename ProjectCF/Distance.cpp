#include "Distance.h"


void Distance_Init()
{
	
	//pinMode(ledpin, OUTPUT);
	pinMode(inputPin, INPUT);
	pinMode(outputPin, OUTPUT);
}

//��ȡ����
//��λ ����
long Distance_Get()

{
	long  sum = 0;
	//ѭ��20��ȡƽ��ֵ
	for(int i = 0;i<20;i++)
	{ 
		digitalWrite(outputPin, LOW); // ʹ���������������źŽӿڵ͵�ƽ2��s
		delayMicroseconds(2);
		digitalWrite(outputPin, HIGH); // ʹ���������������źŽӿڸߵ�ƽ10��s������������10��s
		delayMicroseconds(10);
		digitalWrite(outputPin, LOW); // ���ַ����������źŽӿڵ͵�ƽ
		long distance = pulseIn(inputPin, HIGH); // ��������ʱ��
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