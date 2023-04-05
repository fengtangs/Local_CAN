#ifndef __LOCAL_CAnCONSUMER_H
#define __LOCAL_CAnCONSUMER_H
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANConsumer
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: Consumer function, the received CAN 
		packet analysis, do the corresponding action

-------------------------------------------------------------*/
#include "Dictionary.h"
	/*接收消息数据包*/
typedef __packed struct
{
	 uint8_t  Index;		//段内字典索引
	 char      Data[8];	//数据包
	 uint8_t   SegmentId; //段号
}CAN_Msg_typedef;

/*接收消息数据包解析处理*/
typedef __packed union
{
	 CAN_Msg_typedef CAN_Msg;
	 uint8_t         Buf[9];
}CAN_RxBuf_typedef;

		/*接收到的CAN数据帧处理*/
typedef struct
{
	#if !STMF1
   CAN_RxHeaderTypeDef RxMessage;		//数据帧相关数据
	#else
	 FDCAN_RxHeaderTypeDef RxMessage;	//数据帧相关数据
	#endif
   CAN_RxBuf_typedef   Data;			//CAN数据包
}CAN_Receive_typedef;
//定义CAN接收队列
typedef struct
{
__IO   int Queue_first;				//队列头指针
__IO	 int Queue_tail;				//队列尾指针
   CAN_Receive_typedef CAN_Receive[CAN_QUEUE_LENGTH];	//接收数据数组
}CAN_Queue_typedef;

		/*处理接收消息队列函数*/
void Consumer_Event(void );
#endif /*__LOCAL_CAnCONSUMER_H*/
