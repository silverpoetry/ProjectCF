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

//获取距离
//单位 毫米
long Distance_Get()

{
	long  sum = 0;
	//循环20次取平均值
	for(int i = 0;i<10;i++)
	{ 
		digitalWrite(Distance_OutPutPin, LOW); // 使发出发出超声波信号接口低电平2μs
		delayMicroseconds(2);
		digitalWrite(Distance_OutPutPin, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
		delayMicroseconds(10);
		digitalWrite(Distance_OutPutPin, LOW); // 保持发出超声波信号接口低电平
		//attachInterrupt(2,,)
		long distance = pulseIn(Distance_InputPin, HIGH,20000); // 读出脉冲时间
		if (distance == 0)return 0;
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
		delay(5);
	}
	sum /= 20;
	return sum;
}