#include "main.h"
#include "stdio.h"
#include "DataOut.h"
#include "AD7172-2.h"
#include "N2000.h"

extern UART_HandleTypeDef huart1;

uint32_t  AD7172_uData =0;
int32_t   AD7172_Data =0;


volatile int    OneConvert = 0;
int             LedFlash = 0;


Fid_typedef  Fid={.Fid_Type = LINER,//1
	                .Out_Type = TYPE_W32,//0
                  .Switch_Select=0};

W32_DatatypeDef W32 ={0};


//**************************************************************************//
void Set_FidMode(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	if(HAL_GPIO_ReadPin(S0_GPIO_Port,S0_Pin)==GPIO_PIN_RESET)
	{
     Fid.Fid_Type = SQUARE;//0���s0����Ϊ�͵�ƽ����fidΪƽ�����Ŵ���
  }
	else
	{
		  Fid.Fid_Type = LINER;//1������Ϊ���ԷŴ����������ʼ��
		
	    HAL_GPIO_WritePin(S0_GPIO_Port,S0_Pin, GPIO_PIN_SET);//1
	    HAL_GPIO_WritePin(S1_GPIO_Port,S1_Pin, GPIO_PIN_SET);//1
	    HAL_GPIO_WritePin(S2_GPIO_Port,S2_Pin, GPIO_PIN_SET);		//1
			GPIO_InitStruct.Pin = S2_Pin|S1_Pin|S0_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;			
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);		
		
	};
	
}	

//**************************************************************************//
void W32_OutPut(int32_t W32_Value,W32_DatatypeDef *W32_Data)
{
	
	      uint8_t *Pchar = (uint8_t *) W32_Data->Chanal_Buf;	

	      W32_Data->CH_Id=0xA0+(Fid.Switch_Select<<4);

	      W32_Data->Chanal_Buf[3] = W32_Value&0x0000007f;
				W32_Value = W32_Value >> 7;
				W32_Data->Chanal_Buf[2] = W32_Value&0x0000007f;
				W32_Value = W32_Value >> 7;
				W32_Data->Chanal_Buf[1] = W32_Value&0x0000007f;
				W32_Value = W32_Value >> 7;
				W32_Data->Chanal_Buf[0] = W32_Value&0x0000000f;
	      W32_Data->Chanal_Buf[0] |= W32_Data->CH_Id;
				
			  HAL_UART_Transmit(&huart1,Pchar,4,HAL_MAX_DELAY);
};


void Data_Output_Task(void)
{	
	  uint8_t B8_Buf;
	  while(OneConvert==0)
		{   
			  if(Fid.Fid_Type==LINER)//����
				{	
						if(HAL_UART_Receive(&huart1,&B8_Buf,1,0)==HAL_OK)//����Ǹ����û����ã��ԷŴ�������ѡ����
						{
							 switch(B8_Buf)
							 {
								 case 0xa0://111
										HAL_GPIO_WritePin(S0_GPIO_Port,S0_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S1_GPIO_Port,S1_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S2_GPIO_Port,S2_Pin, GPIO_PIN_SET);		
									  Fid.Switch_Select = 0;
									 break;
								 case 0xa1://011
										HAL_GPIO_WritePin(S0_GPIO_Port,S0_Pin, GPIO_PIN_RESET);
										HAL_GPIO_WritePin(S1_GPIO_Port,S1_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S2_GPIO_Port,S2_Pin, GPIO_PIN_SET);		
									  Fid.Switch_Select = 1;
									 
									 break;
								 case 0xa2://101
										HAL_GPIO_WritePin(S0_GPIO_Port,S0_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S1_GPIO_Port,S1_Pin, GPIO_PIN_RESET);
										HAL_GPIO_WritePin(S2_GPIO_Port,S2_Pin, GPIO_PIN_SET);		
									  Fid.Switch_Select = 2;
									 break;
								 case 0xa3://110
										HAL_GPIO_WritePin(S0_GPIO_Port,S0_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S1_GPIO_Port,S1_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S2_GPIO_Port,S2_Pin, GPIO_PIN_RESET);		
									  Fid.Switch_Select = 3;
									 break;
								 case 0xc0://������ã�
									 Fid.Out_Type = TYPE_W32;
									 break;
								 case 0xc1:
									 Fid.Out_Type = TYPE_N2000;
									 break;
							 };
						};	
			  };
		};
		OneConvert=0;	
		AD7172_uData= ad7172_read(DATA,3,AD7172_DATA);//��ȡ����,��ȡ����������ƫ�ƶ����ƣ�
		
	  if(Fid.Fid_Type==LINER)
		{	
		   AD7172_Data = 0xE87BEB-AD7172_uData;//��������ԷŴ���������ֵ���Ǹ��ģ�Ҫ�ĳ���ֵ����Ϊ�������˲���
		}	
		else
		{	
		   AD7172_Data = AD7172_uData -0x800000;//����Ƕ����Ŵ�����ADֵ��ȥ�м�ֵ�õ���������	
		};	
//����ʱ�������N2000�ĸ�ʽ����N2000��������Խ��жԱ�		
		switch(Fid.Out_Type)
		{
			case TYPE_W32:			
	      W32_OutPut(AD7172_Data,&W32);
			  break;
			case TYPE_N2000:
        N2000_OutPut(AD7172_Data,&N2000);			
			  break;
		};	
		
   //	printf("%8X\r",AD7172_Data);
			
		LedFlash = (LedFlash+1)%20;
    if(LedFlash<2)
	     HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);  
		else
		   HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);  
	
}

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)

{
  static int   Callback_Times = 0;
  if(htim->Instance == TIM1)
	{
     Callback_Times++;
		 if(Callback_Times>=50)
		 {
        OneConvert=1;
			  Callback_Times =0;
//			  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
     };			 
		 
	};
}

