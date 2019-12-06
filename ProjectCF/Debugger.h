#pragma once
void Debugger_Init();

//向调试器发送变量监视
//name : 变量名
//value: 变量值
void Debugger_SetWatch(String name, long value);

void Debugger_SetWatch(String name, String value);
void Debugger_Print(String pa, int p1, int p2, int p3);
//管理读数据
void Debugger_DebugManagement();

void Debugger_ShowMicroMove();
void Debugger_ShowDistance();
void Debugger_ShowMpu();
void Debugger_ShowZigbee();