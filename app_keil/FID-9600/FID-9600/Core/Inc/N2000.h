#ifndef __N2000_H
#define __N2000_H

#include "stm32f1xx_hal.h"



/* USER CODE BEGIN Private defines */
typedef struct
{
	  int8_t  CH0_Id;
		uint8_t Chanal0_Buf[3];
	  int8_t   CH1_Id;
		uint8_t  Chanal1_Buf[3];
}N2000_DatatypeDef;

extern N2000_DatatypeDef N2000;
void N2000_OutPut(int32_t N2000_Value,N2000_DatatypeDef *N2000_Data);

/* USER CODE END Private defines */


#endif /* __DATA_OUT_H */
