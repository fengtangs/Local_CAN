#include "Can_Filter_Init.h"
#include "String.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCAN_Ini
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description:CAN filter group initialization configuration

-------------------------------------------------------------*/
extern 	void 	Error_Handler(void);


/****************************************************************

 Function: //标准模式下初始化CAN过滤器组函数，使能CAN
 Description: // 调用此函数初始化CAN过滤器组
 Calls: //
				Error_Handler();

******************************************************************/
#if !STMF1
void Set_Can_ID_Mode(int OutId,uint16_t *Temp,CAN_HandleTypeDef *hcan)
{
					CAN_FilterTypeDef CAN_FilterInitStructure;	
					CAN_FilterInitStructure.FilterActivation       	= ENABLE; 
					CAN_FilterInitStructure.FilterBank							= OutId;
					CAN_FilterInitStructure.FilterFIFOAssignment   	= CAN_FILTER_FIFO0;
					CAN_FilterInitStructure.FilterIdHigh           	= (Temp[0]+ (BID<<6))<<5;
					CAN_FilterInitStructure.FilterIdLow           	= (Temp[1]+ (BID<<6))<<5;
					CAN_FilterInitStructure.FilterMaskIdHigh        = (Temp[2]+ (BID<<6))<<5;
					CAN_FilterInitStructure.FilterMaskIdLow         = (Temp[3]+ (BID<<6))<<5;
					CAN_FilterInitStructure.FilterMode							=	CAN_FILTERMODE_IDLIST;
					CAN_FilterInitStructure.FilterScale            	= CAN_FILTERSCALE_16BIT;
					CAN_FilterInitStructure.SlaveStartFilterBank	= 0;
					if(HAL_CAN_ConfigFilter(hcan, &CAN_FilterInitStructure) != HAL_OK)
					{
						Error_Handler();
					}	
}
/****************************************************************

 Function: //初始化CAN过滤器组函数，使能CAN
 Description: // 调用此函数初始化CAN过滤器组，通过检索用户字典目录表，设置相关过滤器组
 Calls: //HAL_CAN_ConfigFilter();HAL_CAN_Start();HAL_CAN_ActivateNotification();
				Error_Handler();

******************************************************************/
 void Set_Can_Filter(CAN_HandleTypeDef *hcan)
{
	uint16_t i=0;
#if !STANDARD_MODE
	uint16_t Temp[4] ={0}; 
	int OutId=0,InId=0;
	for(i=0;i<CONTENTS_LENGTH;i++)	//筛选出要初始化的SID
	{
		if(ContentsDictionary[i].SegmentLength!=0)
		{
				Temp[InId++] = i;
				if(InId>3)
				{
					InId=0;
					Set_Can_ID_Mode(OutId,Temp,hcan);
					OutId++;
					memset(Temp, 0, sizeof(Temp)); 
				}
		}
	}
	while(InId<4&&InId!=0)
	{
		Temp[InId++]=Temp[0];
	}
	if(InId!=0)
		Set_Can_ID_Mode(OutId,Temp,hcan);

#else			//拓展ID
	for(i=0;i<CONTENTS_LENGTH;i++)	//筛选出要初始化的SID
	{
		if(ContentsDictionary[i].SegmentLength!=0)
		{
		CAN_FilterTypeDef CAN_FilterInitStructure;	
		CAN_FilterInitStructure.FilterActivation       	= ENABLE; 
		CAN_FilterInitStructure.FilterBank							= i;
		CAN_FilterInitStructure.FilterFIFOAssignment   	= CAN_FILTER_FIFO0;
		CAN_FilterInitStructure.FilterIdHigh           	= i;	
		CAN_FilterInitStructure.FilterIdLow           	= BID<<3;
		CAN_FilterInitStructure.FilterMaskIdHigh        = 0x00ff;
		CAN_FilterInitStructure.FilterMaskIdLow         = 0xfff8;
		CAN_FilterInitStructure.FilterMode							=	CAN_FILTERMODE_IDMASK;
		CAN_FilterInitStructure.FilterScale            	= CAN_FILTERSCALE_32BIT;
		CAN_FilterInitStructure.SlaveStartFilterBank	= 0;

		if(HAL_CAN_ConfigFilter(hcan, &CAN_FilterInitStructure) != HAL_OK)
		{
			Error_Handler();
		}
				
		}
	}
#endif	
		if(HAL_CAN_Start(hcan) != HAL_OK)
	{
		Error_Handler();
	}
	if(HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING|CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
	{
		Error_Handler();
	}
		if(HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO1_MSG_PENDING|CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
	{
		Error_Handler();
	}
}	


 void Set_Can_Filter1(CAN_HandleTypeDef *hcan)
{
	uint16_t i=0;
#if !STANDARD_MODE
	uint16_t Temp[4] ={0}; 
	int OutId=0,InId=0;
	for(i=0;i<CONTENTS_LENGTH;i++)	//筛选出要初始化的SID
	{
		if(ContentsDictionary[i].SegmentLength!=0)
		{
				Temp[InId++] = i;
				if(InId>3)
				{
					InId=0;
					Set_Can_ID_Mode(OutId,Temp,hcan);
					OutId++;
					memset(Temp, 0, sizeof(Temp));
				}
		}
	}
	while(InId<4&&InId!=0)
	{
		Temp[InId++]=Temp[0];
	}
	if(InId!=0)
		Set_Can_ID_Mode(OutId,Temp,hcan);
#else			//拓展ID
	for(i=0;i<CONTENTS_LENGTH;i++)	//筛选出要初始化的SID
	{
		if(ContentsDictionary[i].SegmentLength!=0)
		{
		CAN_FilterTypeDef CAN_FilterInitStructure;	
		CAN_FilterInitStructure.FilterActivation       	= ENABLE; 
		CAN_FilterInitStructure.FilterBank							= i;
		CAN_FilterInitStructure.FilterFIFOAssignment   	= CAN_FILTER_FIFO0;
		CAN_FilterInitStructure.FilterIdHigh           	= i;	
		CAN_FilterInitStructure.FilterIdLow           	= BID<<3;
		CAN_FilterInitStructure.FilterMaskIdHigh        = 0x00ff;
		CAN_FilterInitStructure.FilterMaskIdLow         = 0xfff8;
		CAN_FilterInitStructure.FilterMode							=	CAN_FILTERMODE_IDMASK;
		CAN_FilterInitStructure.FilterScale            	= CAN_FILTERSCALE_32BIT;
		CAN_FilterInitStructure.SlaveStartFilterBank	= 0;

		if(HAL_CAN_ConfigFilter(hcan, &CAN_FilterInitStructure) != HAL_OK)
		{
			Error_Handler();
		}
				
		}
	}
#endif	
}
#else
 void Set_Can_Filter(FDCAN_HandleTypeDef *hcan)
{
	
  FDCAN_FilterTypeDef sFilterConfig  ={0};
	int FilterCount=0;
	sFilterConfig.FilterIndex =0;
	
	for(int i=0;i<CONTENTS_LENGTH;i++)	//筛选出要初始化的SID
	{
		if(ContentsDictionary[i].SegmentLength!=0)
		{
			  if(FilterCount)
				{
							/* Configure Rx filter */
						sFilterConfig.IdType = FDCAN_STANDARD_ID;

						sFilterConfig.FilterType =   FDCAN_FILTER_DUAL;
						sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
						sFilterConfig.FilterID2 =  i+(BID<<6);
						HAL_FDCAN_ConfigFilter(hcan, &sFilterConfig);	
					
            sFilterConfig.FilterIndex ++;
					  FilterCount = 0;
				}
        else
				{
						sFilterConfig.FilterID1 = i+(BID<<6);					
				};
				FilterCount = (FilterCount+1)%2;
		};
	};
	//处理奇数个ID的最后一个
	if(FilterCount)
	{
			sFilterConfig.IdType       = FDCAN_STANDARD_ID;
			sFilterConfig.FilterType   = FDCAN_FILTER_DUAL;
			sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
			sFilterConfig.FilterID2    = sFilterConfig.FilterID1;
			HAL_FDCAN_ConfigFilter(hcan, &sFilterConfig);			
	};

  HAL_FDCAN_ConfigGlobalFilter(hcan, FDCAN_REJECT, FDCAN_REJECT, DISABLE, DISABLE);
	/* Configure Rx FIFO 0 watermark to 2 */
  HAL_FDCAN_ConfigFifoWatermark(hcan, FDCAN_CFG_RX_FIFO0, 2);
	/* Activate Rx FIFO 0 watermark notification */
	HAL_FDCAN_ActivateNotification(hcan, FDCAN_IT_RX_FIFO0_WATERMARK, 0);
	HAL_FDCAN_Start(hcan);	
	HAL_FDCAN_ActivateNotification(hcan,FDCAN_IT_RX_FIFO0_NEW_MESSAGE|FDCAN_IT_BUS_OFF,0); 

}
 void Set_Can_Filter1(FDCAN_HandleTypeDef *hcan)
{
	
  FDCAN_FilterTypeDef sFilterConfig  ={0};
	int FilterCount=0;
	sFilterConfig.FilterIndex =0;
	
	for(int i=0;i<CONTENTS_LENGTH;i++)	//筛选出要初始化的SID
	{
		if(ContentsDictionary[i].SegmentLength!=0)
		{
			  if(FilterCount)
				{
							/* Configure Rx filter */
						sFilterConfig.IdType = FDCAN_STANDARD_ID;

						sFilterConfig.FilterType =   FDCAN_FILTER_DUAL;
						sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
						sFilterConfig.FilterID2 =  i+(BID<<6);
						HAL_FDCAN_ConfigFilter(hcan, &sFilterConfig);	
					
            sFilterConfig.FilterIndex ++;
					  FilterCount = 0;
				}
        else
				{
						sFilterConfig.FilterID1 = i+(BID<<6);					
				};
				FilterCount = (FilterCount+1)%2;
		};
	};
	//处理奇数个ID的最后一个
	if(FilterCount)
	{
			sFilterConfig.IdType       = FDCAN_STANDARD_ID;
			sFilterConfig.FilterType   = FDCAN_FILTER_DUAL;
			sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
			sFilterConfig.FilterID2    = sFilterConfig.FilterID1;
			HAL_FDCAN_ConfigFilter(hcan, &sFilterConfig);			
	};


}
#endif
