#pragma once
#define SS 23
enum SPI_TYPE
{
	
	MASTER,
	SLAVE
};
float SPI_ReadAngle();
void SPI_Init(SPI_TYPE type);