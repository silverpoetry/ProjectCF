#include "Huidu.h"
#include "IncludeList.h"





void Huidu_Init() {
	for  (int i =0; i<6; i++)
	{
		pinMode(Huidu_Pins[i], INPUT);
	}
}


//读取灰度传感器值（0-1024）
//index 灰度传感器编号(1-5)
int Huidu_Read(int index)
{
	
	int value;
	int min = 9999, max = 0, ans = 0;
	for (int i = 0; i < 4; i++)
	{
	
		int temp = analogRead(Huidu_Pins[index - 1]);;
		ans += temp;
		if (temp < min)min = temp;
		if (temp > max)max = temp;
		

	}
	int finalvalue =  (ans - min - max) / 3.06;
	//对值修正
	
	return finalvalue;

}

//判断传感器是否检测到线
//index 灰度传感器编号(1-4)
bool Huidu_IsLine(int index, int value) {
	//int value = Huidu_Read(index);
	return (value-30) < Huidu_LineValues[index - 1];

}
bool Huidu_IsLine(int index) {
	int value = Huidu_Read(index);
	return value > Huidu_LineValues[index - 1];

}

bool Huidu_IsCrossRoad (void) {
	int cnt = 0;
	for (int i = 1; i <= 6; i++) {
		if (Huidu_IsLine (i)) {
			cnt++;
		}
	}
	if (cnt > 3) {
		return 1;
	}
	return 0;
}
void Huidu_ShowValues()
{
	for (int i = 1; i <= 6; i++)
	{
		String s = "Huidu";
		Debugger_SetWatch(s + i, Huidu_Read(i));
	}
}