#pragma once
void Debugger_Init();

//����������ͱ�������
//name : ������
//value: ����ֵ
void Debugger_SetWatch(String name, long value);

void Debugger_SetWatch(String name, String value);
void Debugger_Print(String pa, int p1, int p2, int p3);
//���������
void Debugger_DebugManagement();

void Debugger_ShowMicroMove();
void Debugger_ShowDistance();
void Debugger_ShowMpu();
void Debugger_ShowZigbee();