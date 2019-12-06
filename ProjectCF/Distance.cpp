#include "Distance.h"
#include "IncludeList.h"

void Distance_Init()
{

	//pinMode(ledpin, OUTPUT);
	pinMode(Distance_InputPin, INPUT);
	pinMode(Distance_OutPutPin, OUTPUT);
	pinMode(Distance_InputPin2, INPUT);
	pinMode(Distance_OutPutPin2, OUTPUT);
	pinMode(Distance_InputPin0, INPUT);
	pinMode(Distance_OutPutPin0, OUTPUT);


}
//long long  starttime;
//long long arrivetime;
//bool arrived;

//获取距离
//单位 毫米
long Distance_Get(int opt)
{
	
	long  sum = 0;
	//循环20次取平均值

	for (int i = 0; i < 4; i++)
	{
		long distance = 0;
		if (opt == 1)
		{
			digitalWrite(Distance_OutPutPin0, LOW); // 使发出发出超声波信号接口低电平2μs
			delayMicroseconds(2);
			digitalWrite(Distance_OutPutPin0, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
			delayMicroseconds(10);
			digitalWrite(Distance_OutPutPin0, LOW); // 保持发出超声波信号接口低电平
				//attachInterrupt(2,,)
			distance = pulseIn(Distance_InputPin0, HIGH, 20000); // 读出脉冲时间

		}
		else if (opt == 2) 
		{
			digitalWrite(Distance_OutPutPin, LOW); // 使发出发出超声波信号接口低电平2μs
			delayMicroseconds(2);
			digitalWrite(Distance_OutPutPin, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
			delayMicroseconds(10);
			digitalWrite(Distance_OutPutPin, LOW); // 保持发出超声波信号接口低电平
				//attachInterrupt(2,,)
			distance = pulseIn(Distance_InputPin, HIGH, 20000); // 读出脉冲时间
		}
		else if (opt == 3)
		{
			digitalWrite(Distance_OutPutPin2, LOW); // 使发出发出超声波信号接口低电平2μs
			delayMicroseconds(2);
			digitalWrite(Distance_OutPutPin2, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
			delayMicroseconds(10);
			digitalWrite(Distance_OutPutPin2, LOW); // 保持发出超声波信号接口低电平
				//attachInterrupt(2,,)
			distance = pulseIn(Distance_InputPin2, HIGH, 10000); // 读出脉冲时间
		}
		if (distance == 0)return 0;
		distance = distance * 10 / 58; // 将脉冲时间转化为距离（单位：厘米）
	//	Serial.println(distance); //输出距离值 

		sum += distance;


		delay(5);

	}
	sum /= 8;
	return sum;
}