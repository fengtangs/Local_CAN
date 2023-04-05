#include "main.h"
#include "stdio.h"
#include "N2000.h"

extern UART_HandleTypeDef huart1;

N2000_DatatypeDef N2000 ={0};
//**************************************************************************//
void N2000_OutPut(int32_t N2000_Value,N2000_DatatypeDef *N2000_Data)
{
	
	      uint8_t *Pchar = (uint8_t *) N2000_Data;	
	 
	      N2000_Data->CH0_Id=0xc0;
	      N2000_Data->CH1_Id=0xc1;
	
        N2000_Value = (float)N2000_Value / (float)9.75;
			
			  N2000_Value = N2000_Value >  524287 ?  524287 : N2000_Value;
		    N2000_Value = N2000_Value < -524287 ? -524287 : N2000_Value;		
			
				N2000_Data->Chanal0_Buf[2] = N2000_Value&0x0000007f;
				N2000_Value = N2000_Value >> 7;
				N2000_Data->Chanal0_Buf[1] = N2000_Value&0x0000007f;
				N2000_Value = N2000_Value >> 7;
				N2000_Data->Chanal0_Buf[0] = N2000_Value&0x0000003f;
			
			  HAL_UART_Transmit(&huart1,Pchar,8,HAL_MAX_DELAY);
};
