#include "Distance.h"


void Distance_Init()
{
	
	//pinMode(ledpin, OUTPUT);
	pinMode(inputPin, INPUT);
	pinMode(outputPin, OUTPUT);
}

//获取距离
//单位 毫米
long Distance_Get()

{
	long  sum = 0;
	//循环20次取平均值
	for(int i = 0;i<20;i++)
	{ 
		digitalWrite(outputPin, LOW); // 使发出发出超声波信号接口低电平2μs
		delayMicroseconds(2);
		digitalWrite(outputPin, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
		delayMicroseconds(10);
		digitalWrite(outputPin, LOW); // 保持发出超声波信号接口低电平
		long distance = pulseIn(inputPin, HIGH); // 读出脉冲时间
		distance = distance*10 / 58; // 将脉冲时间转化为距离（单位：厘米）
	//	Serial.println(distance); //输出距离值 
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