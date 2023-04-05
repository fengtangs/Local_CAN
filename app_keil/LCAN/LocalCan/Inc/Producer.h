#ifndef __LOCAL_CANPRODUCER_H
#define __LOCAL_CANPRODUCER_H
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANDictionary
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: CAN data dictionary definition

-------------------------------------------------------------*/
#include"Dictionary.h"

/*发送结构体*/
typedef   struct
{
	#if !STMF1
		CAN_TxHeaderTypeDef TxMessage;
	#else 
		FDCAN_TxHeaderTypeDef TxMessage;
	#endif
	uint8_t  Data[8];
	uint32_t Mailbox;
}CAN_TxBuf_typedef;


		/*数据包格式*/
typedef __packed struct
{
	 uint8_t  SegmentId;//段号
   uint8_t  Dict_SegmentIndex;//段数据字典索引
	 char     Data[8];		//数据
}CAN_Send_package_typedef;
	
typedef __packed union
{
	 CAN_Send_package_typedef CAN_Msg;
	 uint8_t        				 Buf[10];
}CAN_TxUnion_typedef;


		/*发送消息队列结构体*/
typedef __packed struct
{
   __IO uint32_t  head;			//头指针
	 __IO uint32_t  tail;			//尾指针
	 CAN_TxUnion_typedef Data[CAN_QUEUE_LENGTH];		//数据数组
}CAN_Msg_FIFO;

/****************************************************************

 Function: //		生产者函数
 Description: // 完成对数据字典数据变化的检测，生产CAN包，并将CAN包根据优先级放入不同的消息队列，并返回CAN包的数量
 Calls: //由主函数调用
 Called By: //比较函数，数据包入队函数
 Input: //
 Output: // CAN包
 Return: // CAN包数量

******************************************************************/
uint8_t Producer_Event(void);

/****************************************************************************************

 Function: //发布者函数
 Description: // 发布函数，将两个发送消息队列里需要发送的CAN包，发送出去
								。并将发送成功的CAN包从消息队列移除
 Calls: //调用CAN发送函数Send_MessagesQueue,Error_Handler错误处理
 Called By: //被主函数调用
 Input: //

*******************************************************************************************/
void Deliver_Event(void);

#endif /*__LOCAL_CANPRODUCER_H*/
