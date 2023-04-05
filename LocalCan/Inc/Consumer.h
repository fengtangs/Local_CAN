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
	/*������Ϣ���ݰ�*/
typedef __packed struct
{
	 uint8_t  Index;		//�����ֵ�����
	 char      Data[8];	//���ݰ�
	 uint8_t   SegmentId; //�κ�
}CAN_Msg_typedef;

/*������Ϣ���ݰ���������*/
typedef __packed union
{
	 CAN_Msg_typedef CAN_Msg;
	 uint8_t         Buf[9];
}CAN_RxBuf_typedef;

		/*���յ���CAN����֡����*/
typedef struct
{
   FDCAN_RxHeaderTypeDef RxMessage;	//����֡�������
   CAN_RxBuf_typedef   Data;			  //CAN���ݰ�
}CAN_Receive_typedef;
//����CAN���ն���
typedef struct
{
__IO   int Queue_first;				//����ͷָ��
__IO	 int Queue_tail;				//����βָ��
   CAN_Receive_typedef CAN_Receive[CAN_QUEUE_LENGTH];	//������������
}CAN_Queue_typedef;

		/*���������Ϣ���к���*/
void Consumer_Event(void );
#endif /*__LOCAL_CAnCONSUMER_H*/
