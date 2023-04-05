#include"Consumer.h"
#include "string.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANConsumer
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: Consumer function, the received CAN 
		packet analysis, do the corresponding action

-------------------------------------------------------------*/

//数据字典
extern type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH];
	//CAN
	#if !STMF1
extern CAN_HandleTypeDef hcan;
#else
extern FDCAN_HandleTypeDef hfdcan1;
#endif
//错误函调
#define ERROR() ; 
//接收消息队列
CAN_Queue_typedef CAN_Rx_Queue= {0};
//字典目录
extern  Contents_def ContentsDictionary[CONTENTS_LENGTH];
//初始化信号量
extern volatile int    Sem_Sn; 

/****************************************************************
 Function: //uint8类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void uint8_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	uint8_t *ptr;
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (uint8_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((uint8_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((uint8_t*)&CAN_Rx_package->Buf[1]);
		#endif
				//调用回调函数，完成其他操作
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//错误处理
	{
			ERROR();
	}
}

/****************************************************************
 Function: //uint16类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void uint16_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	uint16_t *ptr;
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (uint16_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((uint16_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((uint16_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//调用回调函数，完成其他操作
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//错误处理
	{
			ERROR();
	}

}
/****************************************************************
 Function: //uint32类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void uint32_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	uint32_t *ptr;
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (uint32_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((uint32_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((uint32_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//调用回调函数，完成其他操作
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//错误处理
	{
			ERROR();
	}
}
/****************************************************************
 Function: //int8_t类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void int8_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	int8_t *ptr;
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (int8_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((int8_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((int8_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//调用回调函数，完成其他操作
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//错误处理
	{
			ERROR();
	}
}
/****************************************************************
 Function: //int16类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void int16_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	int16_t *ptr;
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (int16_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((int16_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((int16_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//调用回调函数，完成其他操作
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//错误处理
	{
			ERROR();
	}
}
/****************************************************************
 Function: //int32_t类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void int32_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	int32_t *ptr;
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (int32_t*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((int32_t*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((int32_t*)&CAN_Rx_package->Buf[1]);
		#endif

				//调用回调函数，完成其他操作
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//错误处理
	{
			ERROR();
	}
}
/****************************************************************
 Function: //float类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void real_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	float *ptr;
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (float*)Dictionary_Data[index].consumer_object;
		#if !STANDARD_MODE
				*ptr=*((float*)CAN_Rx_package->CAN_Msg.Data);
		#else
				*ptr=*((float*)&CAN_Rx_package->Buf[1]);
		#endif

				//调用回调函数，完成其他操作
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//错误处理
	{
			ERROR();
	}
}
/****************************************************************
 Function: //char arry3类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void arry3_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
		#if !STANDARD_MODE
			memcpy(Dictionary_Data[index].consumer_object, CAN_Rx_package->CAN_Msg.Data,3);
		#else
			memcpy(Dictionary_Data[index].consumer_object, &CAN_Rx_package->Buf[1],3);
		#endif
			//调用回调函数，完成其他操作
			if(Dictionary_Data[index].Callback_func!= NULL)
			{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
			}
	}
	else
	{
			ERROR();
	}
}
/****************************************************************
 Function: //char arry5类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void arry5_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	//将字典指针指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)//如果数据区不为空，即用户定义了数据区
	{
		#if !STANDARD_MODE
			memcpy(Dictionary_Data[index].consumer_object, CAN_Rx_package->CAN_Msg.Data,5);
		#else
			memcpy(Dictionary_Data[index].consumer_object, &CAN_Rx_package->Buf[1],5);
		#endif

		//调用回调函数，完成其他操作
		if(Dictionary_Data[index].Callback_func!= NULL)
		{
			Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
		}
	}
		else
	{
		ERROR();
	}
	
}
/****************************************************************
 Function: //char arry6类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void arry6_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
		#if !STANDARD_MODE
			memcpy(Dictionary_Data[index].consumer_object, CAN_Rx_package->CAN_Msg.Data,6);
		#else
			memcpy(Dictionary_Data[index].consumer_object, &CAN_Rx_package->Buf[1],6);
		#endif

		//调用回调函数，完成其他操作
		if(Dictionary_Data[index].Callback_func!= NULL)
		{
			Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
		}
	}
		else
	{
		ERROR();
	}
}

/****************************************************************
 Function: //char arry6类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void arry7_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
		#if !STANDARD_MODE
			memcpy(Dictionary_Data[index].consumer_object, CAN_Rx_package->CAN_Msg.Data,7);
		#else
			memcpy(Dictionary_Data[index].consumer_object,&CAN_Rx_package->Buf[1],7);
		#endif
		//调用回调函数，完成其他操作
		if(Dictionary_Data[index].Callback_func!= NULL)
		{
			Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
		}
	}
		else
	{
		ERROR();
	}
}

/****************************************************************
 Function: //float类型的数据
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // 具体消息队列中的队中元素。CAN_Receive_typedef
 Return: // 返回值为空类型
******************************************************************/
static void double_Update_Rx_Data(CAN_RxBuf_typedef *CAN_Rx_package)
{
	uint8_t  Segment = (uint8_t)CAN_Rx_package->CAN_Msg.SegmentId;//获取段号
	uint8_t OffsetIndex = CAN_Rx_package->CAN_Msg.Index;
	uint16_t StartIndex = ContentsDictionary[Segment].StartIndex;
	uint16_t index = StartIndex+ OffsetIndex;//获取段字典索引；
	double *ptr;
	//将字典指向的数据区更新
	if(Dictionary_Data[index].consumer_object != NULL)
	{
				ptr= (double*)Dictionary_Data[index].consumer_object;
				*ptr=*((double*)&CAN_Rx_package->Buf[1]);
				//调用回调函数，完成其他操作
				if(Dictionary_Data[index].Callback_func!= NULL)
				{
				Dictionary_Data[index].Callback_func ((Dictionary_Data[index].consumer_object));
				}
	}
	else			//错误处理
	{
			ERROR();
	}
}
/****************************************************************

 Function: //接受消息队列处理函数数组
 Description: // 根据不同数据类型，调用不同的函数，完成字典指向数据区的数据更新以及调用相应的函数，完成功能
 Calls: // 各数据字典记录的回调函数
 Called By: //消费者函数
 Input: // CAN_RxBuf_typedef 接收消息包
 Return: // 返回值为空类型
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

 Function: //	消费者函数
 Description: //不断监测接收消息队列，如果接收消息队列有新来的数据，就处理，调用相应的回调函数。
 Calls: //
 Called By: //接受消息队列处理函数
 Input: //无
*******************************************************************************************/
void Consumer_Event()
{
	while(CAN_Rx_Queue.Queue_first != CAN_Rx_Queue.Queue_tail)//接收消息队列不为空
		{
				uint16_t  Segment = (uint16_t)CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_first].Data.CAN_Msg.SegmentId;//获取段号
				uint16_t OffsetIndex = CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_first].Data.CAN_Msg.Index;
				uint32_t StartIndex = ContentsDictionary[Segment].StartIndex;
			if(Segment > CONTENTS_LENGTH || OffsetIndex> ContentsDictionary[Segment].SegmentLength )					//索引不合法
				{	
						CAN_Rx_Queue.Queue_first=(CAN_Rx_Queue.Queue_first+1)%CAN_QUEUE_LENGTH;//完成出队
						ERROR();
				}
			else
			{	
						uint16_t id =Dictionary_Data[StartIndex + OffsetIndex].data_type;
						(*Update_Rx_Data[id])(&(CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_first].Data));	//做相应的动作，更新字典，调用回调函数
						CAN_Rx_Queue.Queue_first=(CAN_Rx_Queue.Queue_first+1)%CAN_QUEUE_LENGTH;//完成出队
			}
				
		}//end_while
}
/****************************************************************************************

 Function: //	接收邮箱中断回调函数
 Description: //当接收到数据后，触发本函数，如果是发送给本设备的，就接收，并将接收到的数据放到接收队列。
*******************************************************************************************/
#if !STMF1
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *canHandle)
{
			int	 tail = (CAN_Rx_Queue.Queue_tail+1)%CAN_QUEUE_LENGTH;
	    CAN_Receive_typedef *CAN_Receive_package = &CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail];
			#if !STANDARD_MODE
				if(HAL_CAN_GetRxMessage(canHandle,CAN_RX_FIFO0, &CAN_Receive_package->RxMessage, CAN_Receive_package->Data.Buf)==HAL_OK)
				{	
						uint16_t Segment = CAN_Receive_package->RxMessage.StdId & 0x1f;
						CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail].Data.CAN_Msg.SegmentId=Segment;
						CAN_Rx_Queue.Queue_tail =tail;//接收消息队列后移。	
				};
			#else 
				if(HAL_CAN_GetRxMessage(canHandle,CAN_RX_FIFO0, &CAN_Receive_package->RxMessage, &CAN_Receive_package->Data.Buf[1])==HAL_OK)
				{	
					uint16_t Segment = (CAN_Receive_package->RxMessage.ExtId>>13) & 0x1f;
					CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail].Data.CAN_Msg.SegmentId=Segment;
					CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail].Data.CAN_Msg.Index = CAN_Receive_package->RxMessage.ExtId>>21;
					CAN_Rx_Queue.Queue_tail =tail;//接收消息队列后移。	
				};
			#endif
				
}
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *canHandle)
{
			int	 tail = (CAN_Rx_Queue.Queue_tail+1)%CAN_QUEUE_LENGTH;
	    CAN_Receive_typedef *CAN_Receive_package = &CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail];
			#if !STANDARD_MODE
				if(HAL_CAN_GetRxMessage(canHandle,CAN_RX_FIFO0, &CAN_Receive_package->RxMessage, CAN_Receive_package->Data.Buf)==HAL_OK)
				{	
						uint16_t Segment = CAN_Receive_package->RxMessage.StdId & 0x1f;
						CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail].Data.CAN_Msg.SegmentId=Segment;
						CAN_Rx_Queue.Queue_tail =tail;//接收消息队列后移。	
				};
			#else 
				if(HAL_CAN_GetRxMessage(canHandle,CAN_RX_FIFO0, &CAN_Receive_package->RxMessage, &CAN_Receive_package->Data.Buf[1])==HAL_OK)
				{	
					uint16_t Segment = (CAN_Receive_package->RxMessage.ExtId>>13) & 0x1f;
					CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail].Data.CAN_Msg.SegmentId=Segment;
					CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail].Data.CAN_Msg.Index = CAN_Receive_package->RxMessage.ExtId>>21;
					CAN_Rx_Queue.Queue_tail =tail;//接收消息队列后移。	
				};
			#endif
				
}
#else
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) 
{
			int	 tail = (CAN_Rx_Queue.Queue_tail+1)%CAN_QUEUE_LENGTH;
	    CAN_Receive_typedef *CAN_Receive_package = &CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail];
	
  	  if(HAL_FDCAN_GetRxMessage(hfdcan,FDCAN_RX_FIFO0, &CAN_Receive_package->RxMessage, CAN_Receive_package->Data.Buf)==HAL_OK)
			{	
						uint16_t Segment = CAN_Receive_package->RxMessage.Identifier & 0x1f;
						CAN_Rx_Queue.CAN_Receive[CAN_Rx_Queue.Queue_tail].Data.CAN_Msg.SegmentId=Segment;
						CAN_Rx_Queue.Queue_tail =tail;//接收消息队列后移。
			
			};			
}
#endif
