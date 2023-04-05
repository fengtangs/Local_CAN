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

 Function: //��ʼ��CAN�������麯����ʹ��CAN
 Description: // ���ô˺�����ʼ��CAN�������飬ͨ�������û��ֵ�Ŀ¼��������ع�������
 Calls: //HAL_CAN_ConfigFilter();HAL_CAN_Start();HAL_CAN_ActivateNotification();
				Error_Handler();

******************************************************************/
 void Set_Can_Filter(FDCAN_HandleTypeDef *hcan)
{
	
  FDCAN_FilterTypeDef sFilterConfig  ={0};
	int FilterCount=0;
	sFilterConfig.FilterIndex =0;
	
	for(int i=0;i<CONTENTS_LENGTH;i++)	//ɸѡ��Ҫ��ʼ����SID
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
	//����������ID�����һ��
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




