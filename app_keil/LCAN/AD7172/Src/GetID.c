#include "GetID.h"
void GetSTM32MCUID(char *id,MCUTypedef type)
{

    id[0]=*(char*)(idAddr[type]);
    id[1]=*(char*)(idAddr[type]+1);
    id[2]=*(char*)(idAddr[type]+2);
		id[3]=*(char*)(idAddr[type]+3);
    id[4]=*(char*)(idAddr[type]+4);
    id[5]=*(char*)(idAddr[type]+5);
		id[6]=*(char*)(idAddr[type]+6);

}
