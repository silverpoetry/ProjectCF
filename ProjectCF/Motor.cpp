#include "IncludeList.h"
#include "Motor.h"

void Motor_Init()
{
	pinMode(Motor_Pin1, OUTPUT);
	pinMode(Motor_Pin2, OUTPUT);
	pinMode(Motor_Pin3, OUTPUT);
	pinMode(Motor_Pin4, OUTPUT);

}
void Motor_Stop()
{

	digitalWrite(Motor_Pin1, LOW);
	digitalWrite(Motor_Pin2, LOW);
	digitalWrite(Motor_Pin3, LOW);
	digitalWrite(Motor_Pin4, LOW);
}
void forward()
{
	//forward Ç°½ø
	digitalWrite(Motor_Pin1, HIGH);
	digitalWrite(Motor_Pin2, LOW);
	digitalWrite(Motor_Pin3, HIGH);
	digitalWrite(Motor_Pin4, LOW);
}
void back()
{
	digitalWrite(Motor_Pin1, LOW);
	digitalWrite(Motor_Pin2, HIGH);
	digitalWrite(Motor_Pin3, LOW);
	digitalWrite(Motor_Pin4, HIGH);
}
void Motor_GoSpeed(int speed)
{
	if (speed > 0)forward(), analogWrite(Motor_EN1, speed), analogWrite(Motor_EN2, speed);
	if (speed < 0)back(), analogWrite(Motor_EN1, abs(speed)), analogWrite(Motor_EN2, speed);
	if (speed == 0)Motor_Stop();
}





