#include "Consumer.h"
#include "string.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANConsumer
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: Consumer function, the received CAN
		packet analysis, do the corresponding action

-------------------------------------------------------------*/

//�����ֵ�
extern type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH];
//CAN
extern FDCAN_HandleTypeDef hcan;
//���󺯵�
extern 	void 	Error_Handler(void);
//������Ϣ����
CAN_Queue_typedef CAN_Rx_Queue= {0};
//�ֵ�Ŀ¼
extern  Contents_def ContentsDictionary[CONTENTS_LENGTH];


/****************************************************************
 Function: //uint8���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void uint8_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	uint8_t *ptr;
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (uint8_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((uint8_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((uint8_t*)&CAN_Rx_package->Buf[1]);
		#endif
				//���ûص������������������
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//������
	{
			Error_Handler();
	}
}

/****************************************************************
 Function: //uint16���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void uint16_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	uint16_t *ptr;
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (uint16_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((uint16_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((uint16_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//���ûص������������������
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//������
	{
			Error_Handler();
	}

}
/****************************************************************
 Function: //uint32���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void uint32_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	uint32_t *ptr;
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (uint32_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((uint32_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((uint32_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//���ûص������������������
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//������
	{
			Error_Handler();
	}
}
/****************************************************************
 Function: //int8_t���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void int8_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	int8_t *ptr;
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (int8_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((int8_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((int8_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//���ûص������������������
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//������
	{
			Error_Handler();
	}
}
/****************************************************************
 Function: //int16���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void int16_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	int16_t *ptr;
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (int16_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((int16_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((int16_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//���ûص������������������
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//������
	{
			Error_Handler();
	}
}
/****************************************************************
 Function: //int32_t���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void int32_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	int32_t *ptr;
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (int32_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((int32_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((int32_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//���ûص������������������
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//������
	{
			Error_Handler();
	}
}
/****************************************************************
 Function: //float���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void real_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	float *ptr;
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (float*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((float*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((float*)&CAN_Rx_package->Buf[1]);
		#endif

				//���ûص������������������
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//������
	{
			Error_Handler();
	}
}
/****************************************************************
 Function: //char arry3���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void arry3_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
		#if !STANDARD_MODE
			memcpy(Dictionary_Data[index].consumer_object, CAN_Rx_package->CAN_Msg.Data,3);
		#else
			memcpy(Dictionary_Data[index].consumer_object, &CAN_Rx_package->Buf[1],3);
		#endif
			//���ûص������������������
			if(Dictionary_Data[index].Callback_func!= NULL)
			{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
			}
	}
	else
	{
			Error_Handler();
	}
}
/****************************************************************
 Function: //char arry5���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void arry5_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	//���ֵ�ָ��ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)//�����������Ϊ�գ����û�������������
	{
		#if !STANDARD_MODE
			memcpy(Dictionary_Data[index].consumer_object, CAN_Rx_package->CAN_Msg.Data,5);
		#else
			memcpy(Dictionary_Data[index].consumer_object, &CAN_Rx_package->Buf[1],5);
		#endif

		//���ûص������������������
		if(Dictionary_Data[index].Callback_func!= NULL)
		{
			Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
		}
	}
		else
	{
		Error_Handler();
	}

}
/****************************************************************
 Function: //char arry6���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void arry6_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
		#if !STANDARD_MODE
			memcpy(Dictionary_Data[index].consumer_object, CAN_Rx_package->CAN_Msg.Data,6);
		#else
			memcpy(Dictionary_Data[index].consumer_object, &CAN_Rx_package->Buf[1],6);
		#endif

		//���ûص������������������
		if(Dictionary_Data[index].Callback_func!= NULL)
		{
			Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
		}
	}
		else
	{
		Error_Handler();
	}
}

/****************************************************************
 Function: //char arry6���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void arry7_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
		#if !STANDARD_MODE
			memcpy(Dictionary_Data[index].consumer_object, CAN_Rx_package->CAN_Msg.Data,7);
		#else
			memcpy(Dictionary_Data[index].consumer_object,&CAN_Rx_package->Buf[1],7);
		#endif
		//���ûص������������������
		if(Dictionary_Data[index].Callback_func!= NULL)
		{
			Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
		}
	}
		else
	{
		Error_Handler();
	}
}

/****************************************************************
 Function: //float���͵�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // ������Ϣ�����еĶ���Ԫ�ء�CAN_Receive_typedef
 Return: // ����ֵΪ������
******************************************************************/
static void double_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//��ȡ�κ�
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//��ȡ���ֵ�������
	double *ptr;
	//���ֵ�ָ�������������
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (double*)Dictionary_Data[index].consumer_object;
				*ptr=*((double*)&CAN_Rx_package->Buf[1]);
				//���ûص������������������
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//������
	{
			Error_Handler();
	}
}
/****************************************************************

 Function: //������Ϣ���д���������
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ���������ֵ�ָ�������������ݸ����Լ�������Ӧ�ĺ�������ɹ���
 Calls: // �������ֵ��¼�Ļص�����
 Called By: //�����ߺ���
 Input: // CAN_RxBuf_typedef ������Ϣ��
 Return: // ����ֵΪ������
******************************************************************/
static void (*Update_Rx_Data[12])(CAN_RxBuf_typedef *CAN_Rx_package) = {
			uint8_Update_Rx_Data,
			uint16_Update_Rx_Data,
			uint32_Update_Rx_Data,
			int8_Update_Rx_Data,
			int16_Update_Rx_Data,
			int32_Update_Rx_Data,
			real_Update_Rx_Data,
			arry3_Update_Rx_Data,
			arry5_Update_Rx_Data,
			arry6_Update_Rx_Data,
			arry7_Update_Rx_Data,
			double_Update_Rx_Data
};
/****************************************************************************************

 Function: //	�����ߺ���
 Description: //���ϼ�������Ϣ���У����������Ϣ���������������ݣ��ʹ���������Ӧ�Ļص�������
 Calls: //
 Called By: //������Ϣ���д�����
 Input: //��
*******************************************************************************************/
void Consumer_Event(void)
{
	while(CAN_Rx_Queue.Queue_first != CAN_Rx_Queue.Queue_tail)//������Ϣ���в�Ϊ��
	{
				uint16_t  Segment = (uint16_t)CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_first].Data.CAN_Msg.SegmentId;//��ȡ�κ�
				uint16_t OffsetIndex = CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_first].Data.CAN_Msg.Index;
				uint32_t StartIndex = ContentsDictionary[Segment].StartIndex;
			if(Segment > CONTENTS_LENGTH || OffsetIndex> ContentsDictionary[Segment].SegmentLength )					//�������Ϸ�
				{
				Error_Handler();
				}
				uint16_t id =Dictionary_Data[StartIndex + OffsetIndex].data_type;
				(*Update_Rx_Data[id])(&(CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_first].Data));	//����Ӧ�Ķ����������ֵ䣬���ûص�����
				CAN_Rx_Queue.Queue_first=(CAN_Rx_Queue.Queue_first+1)%CAN_QUEUE_LENGTH;//��ɳ���
	}//end_while
}

/*********************************************************************************************************


*********************************************************************************************************/
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) 
{
			int	 tail = (CAN_Rx_Queue.Queue_tail+1)%CAN_QUEUE_LENGTH;
	    CAN_Receive_typedef *CAN_Receive_package = &CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail];
	
  	  if(HAL_FDCAN_GetRxMessage(hfdcan,FDCAN_RX_FIFO0, &CAN_Receive_package->RxMessage, CAN_Receive_package->Data.Buf)==HAL_OK)
			{	
						uint16_t Segment = CAN_Receive_package->RxMessage.Identifier & 0x1f;
						CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail].Data.CAN_Msg.SegmentId=Segment;
						CAN_Rx_Queue.Queue_tail =tail;//������Ϣ���к��ơ�
			
			};			
}
