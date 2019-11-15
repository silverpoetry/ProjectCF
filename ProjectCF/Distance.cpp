#include "Distance.h"

#include <Adafruit_VL53L0X.h>
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
void Distance_Init()
{

	//pinMode(ledpin, OUTPUT);
	pinMode(Distance_InputPin, INPUT);
	pinMode(Distance_OutPutPin, OUTPUT);
	pinMode(Distance_InputPin2, INPUT);
	pinMode(Distance_OutPutPin2, OUTPUT);
	lox.begin();


}
//long long  starttime;
//long long arrivetime;
//bool arrived;

//��ȡ����
//��λ ����
long Distance_Get(int opt)

{

	long  sum = 0;
	//ѭ��20��ȡƽ��ֵ

	for (int i = 0; i < 10; i++)
	{
		long distance = 0;
		if (opt == 1)
		{
			VL53L0X_RangingMeasurementData_t measure;
			lox.rangingTest(&measure, false); 
			if (measure.RangeStatus != 4)
			{  
			 return measure.RangeMilliMeter;
			}
			else {
				return 0;
			}
		}
		else if (opt == 2) {
			digitalWrite(Distance_OutPutPin, LOW); // ʹ���������������źŽӿڵ͵�ƽ2��s
			delayMicroseconds(2);
			digitalWrite(Distance_OutPutPin, HIGH); // ʹ���������������źŽӿڸߵ�ƽ10��s������������10��s
			delayMicroseconds(10);
			digitalWrite(Distance_OutPutPin, LOW); // ���ַ����������źŽӿڵ͵�ƽ
				//attachInterrupt(2,,)
			distance = pulseIn(Distance_InputPin, HIGH, 20000); // ��������ʱ��
		}
		else if (opt == 3) {
			digitalWrite(Distance_OutPutPin2, LOW); // ʹ���������������źŽӿڵ͵�ƽ2��s
			delayMicroseconds(2);
			digitalWrite(Distance_OutPutPin2, HIGH); // ʹ���������������źŽӿڸߵ�ƽ10��s������������10��s
			delayMicroseconds(10);
			digitalWrite(Distance_OutPutPin2, LOW); // ���ַ����������źŽӿڵ͵�ƽ
				//attachInterrupt(2,,)
			distance = pulseIn(Distance_InputPin2, HIGH, 20000); // ��������ʱ��
		}
		if (distance == 0)return 0;
		distance = distance * 10 / 58; // ������ʱ��ת��Ϊ���루��λ�����ף�
	//	Serial.println(distance); //�������ֵ 
		
			sum += distance;
		
		
		delay(5);

	}
	sum /= 20;
	return sum;
}