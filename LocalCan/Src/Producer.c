#include "Producer.h"
#include "Dictionary.h"
#include "string.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANProducer
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: CAN Producer Function，
		Can packets are generated and put into different
		message queues, and can packets are sent

-------------------------------------------------------------*/

	/*优先级队列定义，extern定义，应在主函数定义*/
CAN_Msg_FIFO Send_High_Priority_Queue={0};		//高优先级队列
CAN_Msg_FIFO Send_Low_Priority_Queue={0};			//低优先级队列
		//数据字典
extern type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH];
		//字典目录
extern  Contents_def ContentsDictionary[CONTENTS_LENGTH]; 
	//CAN


//error函调
extern void Error_Handler(void);

	//数据长度数组
const uint8_t Data_Length[12]={2,3,5,2,3,5,5,4,6,7,8,8};

CAN_TxBuf_typedef CAN_Send;

 /****************************************************************************************

 Function: //uint8类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t uint8_Compare(void *object, char * last_data)
{
	uint8_t  status = HAL_OK;
	if(object != NULL)
	{	
			uint8_t *sp=(uint8_t*)object;
			uint8_t *dp= (uint8_t *)last_data;
			if(*sp != *dp)
			{	
				status = 1;
			}
	}	
	return status;
}
 /****************************************************************************************

 Function: //uint16类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t uint16_Compare(void *object, char * last_data)
{
	uint8_t  status = HAL_OK;
	if(object != NULL)
	{	
			uint16_t *sp=(uint16_t*)object;
			uint16_t *dp= (uint16_t *)last_data;
			if(*sp != *dp)
			{	
				status = 1;
			}
	}	
	return status;
}
 /****************************************************************************************

 Function: //uint32类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t uint32_Compare(void *object, char * last_data)
{
	uint8_t  status = HAL_OK;
	if(object != NULL)
	{	
			uint32_t *sp=(uint32_t*)object;
			uint32_t *dp= (uint32_t *)last_data;
			if(*sp != *dp)
			{	
				status = 1;
			}
	}	
	return status;	
}
 /****************************************************************************************

 Function: //int8类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t int8_Compare(void *object, char * last_data)
{
	uint8_t  status = HAL_OK;
	if(object != NULL)
	{	
			int8_t *sp=(int8_t*)object;
			int8_t *dp= (int8_t *)last_data;
			if(*sp != *dp)
			{	
				status = 1;
			}
	}	
	return status;
}
 /****************************************************************************************

 Function: //int16类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t int16_Compare(void *object, char * last_data)
{
	uint8_t  status = HAL_OK;
	if(object != NULL)
	{	
			int16_t *sp=(int16_t*)object;
			int16_t *dp= (int16_t *)last_data;
			if(*sp != *dp)
			{	
				status = 1;
			}
	}	
	return status;
}
 /****************************************************************************************

 Function: //int32类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t int32_Compare(void *object, char * last_data)
{
	uint8_t  status = HAL_OK;
	if(object != NULL)
	{	
			int32_t *sp=(int32_t*)object;
			int32_t *dp= (int32_t *)last_data;
			if(*sp != *dp)
			{	
				status = 1;
			}
	}	
	return status;
}

 /****************************************************************************************

 Function: //real类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t real_Compare(void *object, char * last_data)
{
	uint8_t  status = HAL_OK;
	if(object != NULL)
	{	
			float *sp=(float*)object;
			float *dp= (float *)last_data;
			if(*sp != *dp)
			{	
				status = 1;
			}
	}	
	return status;
}
 /****************************************************************************************

 Function: //char arry3类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t arry3_Compare(void *object, char * last_data)
{
			uint8_t  status = HAL_OK;
			if(object != NULL)
			{	
					if(*((char* )object)!= last_data[0]||*((char* )object+1)!=last_data[1]||
					*((char* )object+2)!=last_data[2])
					{	
							status = 1;
					}
			}	
			return status;
}

 /****************************************************************************************

 Function: //char arry5类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t arry5_Compare(void *object, char * last_data)
{
			uint8_t  status = HAL_OK;
			if(object != NULL)
			{	
					if(*((char* )object)!= last_data[0]||*((char* )object+1)!=last_data[1]||
					*((char* )object+2)!=last_data[2]||*((char* )object+3)!=last_data[3]||*((char* )object+4)!=last_data[4])
					{	
							status = 1;
					}
			}	
			return status;
}
 /****************************************************************************************

 Function: //char arry6类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t arry6_Compare(void *object, char * last_data)
{
			uint8_t  status = HAL_OK;
			if(object != NULL)
			{	
					if(*((char* )object)!= last_data[0]||*((char* )object+1)!=last_data[1]||
					*((char* )object+2)!=last_data[2]||*((char* )object+3)!=last_data[3]||*((char* )object+4)!=last_data[4]
						||*((char* )object+5)!=last_data[5])
					{	
							status = 1;
					}
			}	
			return status;
}

 /****************************************************************************************

 Function: //char arry7类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t arry7_Compare(void *object, char * last_data)
{
			uint8_t  status = HAL_OK;
			if(object != NULL)
			{	
					if(*((char* )object)!= last_data[0]||*((char* )object+1)!=last_data[1]||
					*((char* )object+2)!=last_data[2]||*((char* )object+3)!=last_data[3]||*((char* )object+4)!=last_data[4]
						||*((char* )object+5)!=last_data[5]||*((char* )object+6)!=last_data[6])
					{	
							status = 1;
					}
			}	
			return status;
} 

 /****************************************************************************************

 Function: //char arry8类型比较函数，内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用：uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
*******************************************************************************************/
static uint8_t double_Compare(void *object, char * last_data)
{
	uint8_t  status = HAL_OK;
	if(object != NULL)
	{	
			double *sp=(double *)object;
			double *dp= (double *)last_data;
			if(*sp != *dp)
			{	
				status = 1;
			}
	}	
	return status;
} 
/****************************************************************************************

 Function: //数据类型比较函数（函数指针）内部函数
 Description: // 根据不同数据类型调用不同的比较函数，根据数据缓冲区last_data存储的上次数据
									，与现有产生的数据进行比较，如果不同，则返回1，否则返回0
 Calls: //无
 Called By: //生产者函数调用uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointer某一具体的字典记录
 Output: // 
 Return: // 返回uint8_t类型，如果是1，则说明比较数据不同，否则返回0
 Others: //

*******************************************************************************************/
static uint8_t (*Compare[12])(void *object, char * last_data) = {
		uint8_Compare,
		uint16_Compare,
		uint32_Compare,
		int8_Compare,
		int16_Compare,
		int32_Compare,
		real_Compare,
		arry3_Compare,
		arry5_Compare,
		arry6_Compare,
		arry7_Compare,
		double_Compare
};
/****************************************************************************************


*******************************************************************************************/
void CAN_TxMessage_init(void)
{
	CAN_Send.TxMessage.IdType = FDCAN_STANDARD_ID;
	CAN_Send.TxMessage.TxFrameType = FDCAN_DATA_FRAME;

	CAN_Send.TxMessage.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	CAN_Send.TxMessage.BitRateSwitch = FDCAN_BRS_ON;
	CAN_Send.TxMessage.FDFormat = FDCAN_FD_CAN;
	CAN_Send.TxMessage.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	CAN_Send.TxMessage.MessageMarker = 0;
	
}

/****************************************************************************************

 Function: //处理消息队列发送函数
 Description: // 将消息队列里需要发送的数据封装发送
 Calls: //HAL_CAN_AddTxMessage(),HAL_CAN_GetTxMailboxesFreeLevel();HAL_Delay()
 Called By: //发布者函数调用：Deliver();
 Input: //Send_Packagef发送数据包结构体
 Output: // 将数据包通过CAN总线发送出去
 Return: //发送成功，返回1，失败返回0
*******************************************************************************************/
static uint32_t Send_MessagesQueue(CAN_Send_package_typedef *Send_Package)
{
	uint32_t status= 0;
	uint32_t i=Send_Package->SegmentId;//段号
	uint8_t SegmentIndex = Send_Package->Dict_SegmentIndex;

	CAN_Send.TxMessage.Identifier  = (BID<<6)+i;		//标准id 将段号与BID设置为标准ID
	
	uint32_t index = Send_Package->Dict_SegmentIndex+ ContentsDictionary[i].StartIndex ;
	uint32_t DLength = Data_Length[Dictionary_Data[index].data_type];
	CAN_Send.TxMessage.DataLength =DLength<<16; 	//数据段长度	
	memcpy(&CAN_Send.Data[1],Send_Package->Data,DLength-1);

	uint8_t *sp = (uint8_t *)CAN_Send.Data;
		*sp = SegmentIndex;
	
 while( HAL_FDCAN_GetTxFifoFreeLevel(&hcan) == 0 )
  {
		 			HAL_Delay(1);
	};	
  if(HAL_FDCAN_AddMessageToTxFifoQ(&hcan,&CAN_Send.TxMessage,CAN_Send.Data)!=HAL_OK)
	{
		status = 1;

	}
	return status;	
}
/****************************************************************

 Function: // uint8数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // 无
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，void *object, char * last_data具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void uint8_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{

	uint8_t *ptr;
	//将数据包放入队列的数据区
	ptr=(uint8_t*)Send_Msg_Package;
	*ptr=*((uint8_t*)object);
	//将producer仓库缓冲更新
	ptr=(uint8_t*)last_data;
	*ptr=*((uint8_t*)object);
	
}
	/****************************************************************

 Function: // uint16数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // 无
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void uint16_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	uint16_t *ptr;
	//将数据包放入队列的数据区
	ptr=(uint16_t*)Send_Msg_Package;
	*ptr=*((uint16_t*)object);
	//将producer仓库缓冲更新
	ptr=(uint16_t*)last_data;
	*ptr=*((uint16_t*)object);
}
	/****************************************************************

 Function: // uint32数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // 无
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void uint32_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	uint32_t *ptr;
	//将数据包放入队列的数据区
	ptr=(uint32_t*)Send_Msg_Package;
	*ptr=*((uint32_t*)object);
	//将producer仓库缓冲更新
	ptr=(uint32_t*)last_data;
	*ptr=*((uint32_t*)object);
}
	/****************************************************************

 Function: // int8数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // 无
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void int8_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	int8_t *ptr;
	//将数据包放入队列的数据区
	ptr=(int8_t*)Send_Msg_Package;
	*ptr=*((int8_t*)object);
	//将producer仓库缓冲更新
	ptr=(int8_t*)last_data;
	*ptr=*((int8_t*)object);
}
	/****************************************************************

 Function: // int16数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // 无
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void int16_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	int16_t *ptr;
	//将数据包放入队列的数据区
	ptr=(int16_t*)Send_Msg_Package;
	*ptr=*((int16_t*)object);
	//将producer仓库缓冲更新
	ptr=(int16_t*)last_data;
	*ptr=*((int16_t*)object);
}
	/****************************************************************

 Function: // int32数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // 无
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void int32_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	int32_t *ptr;
	//将数据包放入队列的数据区
	ptr=(int32_t*)Send_Msg_Package;
	*ptr=*((int32_t*)object);
	//将producer仓库缓冲更新
	ptr=(int32_t*)last_data;
	*ptr=*((int32_t*)object);
}
	/****************************************************************

 Function: // float数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // 无
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void real_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	float *ptr;
	//将数据包放入队列的数据区
	ptr=(float*)Send_Msg_Package;
	*ptr=*((float*)object);
	//将producer仓库缓冲更新
	ptr=(float*)last_data;
	*ptr=*((float*)object);
}
	/****************************************************************

 Function: // char_arry3数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // memcpy函数
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void arry3_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	//将数据包放入队列的数据区
	memcpy(Send_Msg_Package,object,3);
	//将producer仓库缓冲更新
	memcpy(last_data,object,3);
}
	/****************************************************************

 Function: // char_arry5数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // memcpy函数
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void arry5_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	//将数据包放入队列的数据区
	memcpy(Send_Msg_Package,object,5);
	//将producer仓库缓冲更新
	memcpy(last_data,object,5);
}
	/****************************************************************

 Function: // char_arry6数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // memcpy函数
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void arry6_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{ 
	//将数据包放入队列的数据区
	memcpy(Send_Msg_Package,object,6);
	//将producer仓库缓冲更新
	memcpy(last_data,object,6);
}
	/****************************************************************

 Function: // char_arry7数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // memcpy函数
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void arry7_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{ 
	//将数据包放入队列的数据区
	memcpy(Send_Msg_Package,object,7);
	uint8_t tem[7]={0};
	memcpy(tem ,Send_Msg_Package,7);
	//将producer仓库缓冲更新
	memcpy(last_data,object,7);
}

	/****************************************************************

 Function: // char_arry8数据包入队操作函数，内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // memcpy函数
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void double_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{ 
	//将数据包放入队列的数据区
	memcpy(Send_Msg_Package,object,8);
	//将producer仓库缓冲更新
	memcpy(last_data,object,8);
}
/****************************************************************

 Function: // 数据包入队操作函数（函数数组），内部函数
 Description: // 根据不同数据类型，调用不同的函数，完成数据包的入队
 Calls: // 无
 Called By: //生产者函数 uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package发送数据包，struct type_Dictionary_def *Pointer具体字典记录，
 Output: // 
 Return: // 返回值为空类型
******************************************************************/
static void (*Add_Send_Package[12])(char *Send_Msg_Package,void *object , char *last_data) = {
		uint8_Add_Send_Package,
		uint16_Add_Send_Package,
		uint32_Add_Send_Package,
		int8_Add_Send_Package,
		int16_Add_Send_Package,
		int32_Add_Send_Package,
		real_Add_Send_Package,
		arry3_Add_Send_Package,
		arry5_Add_Send_Package,
		arry6_Add_Send_Package,
		arry7_Add_Send_Package,
		double_Add_Send_Package
};
/****************************************************************

 Function: //		生产者函数
 Description: // 完成对数据字典数据变化的检测，生产CAN包，并将CAN包根据优先级放入不同的消息队列，并返回CAN包的数量
 Calls: //由主函数调用
 Called By: //比较函数Compare，数据包入队函数Add_Send_Package
 Input: //两个发送消息队列Send_High_Priority_Queue,Send_Low_Priority_Queue
 Output: // CAN包
 Return: // CAN包数量
 Others: //

******************************************************************/
uint8_t Producer_Event()
{
	uint8_t num=0;//记录需要生产多少can包。
	uint16_t i=0;//循环遍历目录
	for(i=0;i<CONTENTS_LENGTH;i++)
	{
		if(ContentsDictionary[i].SegmentLength != 0)//该字典段本检测器用到
		{
			int j,id,index=ContentsDictionary[i].StartIndex;	//j 遍历段   id数据类型  index总字典下标
			for(j=index;j<index+ContentsDictionary[i].SegmentLength;j++)
			{
				if(Dictionary_Data[j].producer_object != NULL)//如果是生产者
				{			id = Dictionary_Data[j].data_type;
					if((*Compare[id])(Dictionary_Data[j].producer_object,Dictionary_Data[j].data_buffer))//调用比较函数，如果数据改变，就生产CAN包
					{
											
						if(Dictionary_Data[j].priority == HIGH_PRIORITY )			//高优先级的话，放到高优先级队列,并且更新last_data数据
						{
									
									Send_High_Priority_Queue.Data[Send_High_Priority_Queue.tail].CAN_Msg.Dict_SegmentIndex =(uint8_t)(j-index);//数据域的index
									Send_High_Priority_Queue.Data[Send_High_Priority_Queue.tail].CAN_Msg.SegmentId = (uint8_t)(i);//段索引
									(*Add_Send_Package[id])((Send_High_Priority_Queue.Data[Send_High_Priority_Queue.tail].CAN_Msg.Data),Dictionary_Data[j].producer_object,Dictionary_Data[j].data_buffer);
									Send_High_Priority_Queue.tail=(Send_High_Priority_Queue.tail+1)%CAN_QUEUE_LENGTH;//队列后移
						}
						else																							//低优先级的话，放到低优先级队列,并且更新last_data数据
						{
									Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.tail].CAN_Msg.Dict_SegmentIndex = (uint8_t)(j-index);//数据域的index
									Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.tail].CAN_Msg.SegmentId = (uint8_t)(i);//段索引
									(*Add_Send_Package[id])((Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.tail].CAN_Msg.Data),Dictionary_Data[j].producer_object,Dictionary_Data[j].data_buffer);
									Send_Low_Priority_Queue.tail=(Send_Low_Priority_Queue.tail+1)%CAN_QUEUE_LENGTH;//队列后移
							
						}
						num++;
					
					}//end_if 比较函数
				}//end_if 生产者
			}//end_for for段循环
		}//end_if 段长度判断
	}//end_for 目录循环
	return num;
}//end_Producer_Func
/****************************************************************************************

 Function: //发布者函数
 Description: // 发布函数，将两个发送消息队列里需要发送的CAN包，发送出去
								。并将发送成功的CAN包从消息队列移除
 Calls: //调用CAN发送函数Send_MessagesQueue,Error_Handler错误处理
 Called By: //被主函数调用
 Input: //两个发送消息队列

*******************************************************************************************/
void Deliver_Event(void)
	{
		while(Send_High_Priority_Queue.head!=Send_High_Priority_Queue.tail)//高优先级有数据要发送
		{
				if(Send_MessagesQueue(&Send_High_Priority_Queue.Data[Send_High_Priority_Queue.head].CAN_Msg)== HAL_OK)//发送。
				{
						Send_High_Priority_Queue.head = (Send_High_Priority_Queue.head + 1)%CAN_QUEUE_LENGTH;	//将发送过的队列后移
				}
				else				//发送失败
				{
						Error_Handler();
				}
		}//end_while 高优先级
		
		while(Send_Low_Priority_Queue.head!=Send_Low_Priority_Queue.tail)//低优先级有数据要发送
		{
				if(Send_MessagesQueue(&Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.head].CAN_Msg)==HAL_OK)//发送.
				{
						Send_Low_Priority_Queue.head = (Send_Low_Priority_Queue.head + 1)%CAN_QUEUE_LENGTH;	//将发送过的队列后移�
				
				}
				else				//发送失败
				{
						Error_Handler();
				}
				while(Send_High_Priority_Queue.head!=Send_High_Priority_Queue.tail)//高优先级有数据要发送
				{
					if(Send_MessagesQueue(&Send_High_Priority_Queue.Data[Send_High_Priority_Queue.head].CAN_Msg)== HAL_OK )//发送。
					{
							Send_High_Priority_Queue.head = (Send_High_Priority_Queue.head + 1)%CAN_QUEUE_LENGTH;	//将发送过的队列后移
					}
					else				//发送失败
					{
							Error_Handler();
					}
				}//end_while 高优先级
		}//end_while 低优先级
}
