#include "main.h"
#include "stdio.h"
#include "DataOut.h"
#include "AD7172-2.h"
#include "Dictionary.h"
#include "KelmanFilter.h"
uint32_t  AD7172_uData =0;
int32_t   AD7172_Data =0;
extern int32_t  AD_Data ;
extern int32_t  AD_Data_Filiter ;

volatile int    OneConvert = 0;
int             LedFlash = 0;
extern type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH];

Fid_typedef  Fid={.Fid_Type = LINER,//1
	                .Out_Type = TYPE_W32,//0
                  .Switch_Select=0};

W32_DatatypeDef W32 ={0};


//**************************************************************************//
void Set_FidMode(void)		//��ʼ��ʱ�ж�
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

  void CallBack_Func_FID_Gear_Or_TCD_Current(void *Control_Data) 
{
	 int16_t B16_Buf = *((int16_t *)Control_Data); //��ȡ��Ҫ���õĵ�λ
			  if(Fid.Fid_Type==LINER)//����
				{	
							 switch(B16_Buf)
							 {
								 case 0x00a0://111
										HAL_GPIO_WritePin(S0_GPIO_Port,S0_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S1_GPIO_Port,S1_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S2_GPIO_Port,S2_Pin, GPIO_PIN_SET);		
									  Fid.Switch_Select = 0;
											HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
											HAL_Delay(300);
											HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
											HAL_Delay(300);
											HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
											HAL_Delay(300);
											break;
								 case 0x00a1://011
										HAL_GPIO_WritePin(S0_GPIO_Port,S0_Pin, GPIO_PIN_RESET);
										HAL_GPIO_WritePin(S1_GPIO_Port,S1_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S2_GPIO_Port,S2_Pin, GPIO_PIN_SET);		
									  Fid.Switch_Select = 1;
									 
									 break;
								 case 0x00a2://101
										HAL_GPIO_WritePin(S0_GPIO_Port,S0_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S1_GPIO_Port,S1_Pin, GPIO_PIN_RESET);
										HAL_GPIO_WritePin(S2_GPIO_Port,S2_Pin, GPIO_PIN_SET);		
									  Fid.Switch_Select = 2;
									 break;
								 case 0x00a3://110
										HAL_GPIO_WritePin(S0_GPIO_Port,S0_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S1_GPIO_Port,S1_Pin, GPIO_PIN_SET);
										HAL_GPIO_WritePin(S2_GPIO_Port,S2_Pin, GPIO_PIN_RESET);		
									  Fid.Switch_Select = 3;
									 break;
								 case 0x00c0://������ã�
									 Fid.Out_Type = TYPE_W32;
									 break;
								 case 0x00c1:
									 Fid.Out_Type = TYPE_N2000;
									 break;
							 };
			  };
}
void Data_Output_Task(void)
{	
		if(OneConvert == 1)
		{
			AD7172_uData= ad7172_read(DATA,3,AD7172_DATA);//��ȡ����,��ȡ����������ƫ�ƶ����ƣ�
		
			HAL_Delay(1);
	  if(Fid.Fid_Type==LINER)
		{	
		   AD7172_Data = 0xE87BEB-AD7172_uData;//��������ԷŴ���������ֵ���Ǹ��ģ�Ҫ�ĳ���ֵ����Ϊ�������˲���
		}	
		else
		{	
		   AD7172_Data = AD7172_uData -0x800000;//����Ƕ����Ŵ�����ADֵ��ȥ�м�ֵ�õ���������	
		};	
			
		//AD_Data_Filiter =KalmanFilter(AD7172_Data);
		AD_Data =  AD7172_Data;
		OneConvert = 0;
		}  
	
}

