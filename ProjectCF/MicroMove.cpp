#include "MicroMove.h"
#include "IncludeList.h"

void MicroMove_Init ()
{
	pinMode (MicroMove_Pin, INPUT);
}
bool MicroMove_IsPushed ()
{
	return !digitalRead (MicroMove_Pin);

}