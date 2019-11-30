#include "MicroMove.h"
#include "IncludeList.h"

void MicroMove_Init ()
{
	pinMode (MicroMove_Pin, INPUT);
	pinMode (MicroMove_Pin2, INPUT);
	pinMode (MicroMove_Pin3, INPUT);
	pinMode (MicroMove_Pin4, INPUT);

}
bool MicroMove_IsPushed (int id)
{
	if(id == 1)return !digitalRead (MicroMove_Pin);
	if (id == 2)return !digitalRead (MicroMove_Pin2);
	if (id == 3)return !digitalRead (MicroMove_Pin3);
	if (id == 4)return !digitalRead (MicroMove_Pin4);


}