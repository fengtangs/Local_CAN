#ifndef __DATA_OUT_H
#define __DATA_OUT_H

#include "stm32f1xx_hal.h"

#define TYPE_W32    0
#define TYPE_N2000  1

#define SQUARE    0
#define LINER     1


typedef struct
{
	 int  Fid_Type;
   int  Out_Type;
	 int  Switch_Select;
}Fid_typedef;
typedef struct
{
	  int8_t  CH_Id;
		uint8_t Chanal_Buf[4];
}W32_DatatypeDef;

extern W32_DatatypeDef W32;
extern Fid_typedef     Fid;

void Data_Output_Task(void);
void Set_FidMode(void);


#endif /* __DATA_OUT_H */



