#include "IncludeList.h"
#include "BlueTooth.h"
 HardwareSerial blSerial = Serial3;
void BlueTooth_Init()
{
	blSerial.begin(115200);//’º”√Serial 1 
}
String  BlueTooth_ReceiveData()
{
	while (blSerial.available() == 0);
	return blSerial.readString();

}
bool BlueTooth_Available()
{
	return blSerial.available();
}

