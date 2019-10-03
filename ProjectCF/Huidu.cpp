#include "Huidu.h"
#include "IncludeList.h"
int Huidu_LineValues[] = { 500,500,500,500,500 };


void Huidu_Init() {
	for  (int i =0; i<5; i++)
	{
		pinMode(Huidu_Pins[i], INPUT);
	}
}


//��ȡ�Ҷȴ�����ֵ��0-1024��
//index �Ҷȴ��������(1-5)
int Huidu_Read(char index)
{
	
	int value;
	int min = 9999, max = 0, ans = 0;
	for (int i = 0; i < 12; i++)
	{
	
		int temp = analogRead(Huidu_Pins[index - 1]);;
		ans += temp;
		if (temp < min)min = temp;
		if (temp > max)max = temp;
		

	}
	int finalvalue =  (ans - min - max) / 10;
	//��ֵ����
	if (index == 2)finalvalue -= 50;
	return finalvalue;

}

//�жϴ������Ƿ��⵽��
//index �Ҷȴ��������(1-5)
boolean Huidu_IsLine(char index) {
	int value = Huidu_Read(index);
	return value < Huidu_LineValues[index - 1];

}


//����ʱʹ�ã���ӡ����Ҷȵ�ֵ
void Huidu_ShowValue()
{
	

	char str[100];
	sprintf(str, "123%%%%%d%%%%%d%%%%%d%%%%%d%%%%%d%%%%4", Huidu_Read(1), Huidu_Read(2), Huidu_Read(3), Huidu_Read(4), Huidu_Read(5));
	//	sprintf(str,)
	Serial.println(str);

}