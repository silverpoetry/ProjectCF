#include "SPI.h"
#include "CFSPI.h"
SPI_TYPE spitype;
volatile byte command;


void SPI_Init(SPI_TYPE type)
{
	spitype = type;
	if (type== SPI_TYPE::MASTER)
	{
		//开启spi
		SPI.begin();
		SPI.setClockDivider(SPI_CLOCK_DIV8);//设置频率
		pinMode(SS, OUTPUT);//片选
		digitalWrite(SS, LOW);//不选中

	}
	else
	{
		SPCR = _BV(SPE);//开启spi
		SPI.attachInterrupt();//设置中断
		pinMode(MISO, OUTPUT);//配置引脚
	}
}
byte data[2];
float SPI_ReadAngle()
{
	SPI.transfer(16);
	delayMicroseconds(10);
	data[0] = SPI.transfer(16) ;
	delayMicroseconds(10);
	data[1] = SPI.transfer(0);
	Serial.println(data[0]);
	Serial.println(data[1]);
	Serial.println(short(data[0] << 8 | data[1]) / 32768.0 * 180);
	Serial.println("");
	return short(data[0] << 8 | data[1]) / 32768.0 * 180;
	
}

