#include "Distance.h"


void Distance_Init()
{
	
	//pinMode(ledpin, OUTPUT);
	pinMode(Distance_InputPin, INPUT);
	pinMode(Distance_OutPutPin, OUTPUT);
}
long long  starttime;
long long arrivetime;
bool arrived;

//��ȡ����
//��λ ����
long Distance_Get()

{
	long  sum = 0;
	//ѭ��20��ȡƽ��ֵ
	for(int i = 0;i<10;i++)
	{ 
		digitalWrite(Distance_OutPutPin, LOW); // ʹ���������������źŽӿڵ͵�ƽ2��s
		delayMicroseconds(2);
		digitalWrite(Distance_OutPutPin, HIGH); // ʹ���������������źŽӿڸߵ�ƽ10��s������������10��s
		delayMicroseconds(10);
		digitalWrite(Distance_OutPutPin, LOW); // ���ַ����������źŽӿڵ͵�ƽ
		//attachInterrupt(2,,)
		long distance = pulseIn(Distance_InputPin, HIGH,20000); // ��������ʱ��
		if (distance == 0)return 0;
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
		delay(5);
	}
	sum /= 20;
	return sum;
}