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

/*���ͽṹ��*/
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


		/*���ݰ���ʽ*/
typedef __packed struct
{
	 uint8_t  SegmentId;//�κ�
   uint8_t  Dict_SegmentIndex;//�������ֵ�����
	 char     Data[8];		//����
}CAN_Send_package_typedef;
	
typedef __packed union
{
	 CAN_Send_package_typedef CAN_Msg;
	 uint8_t        				 Buf[10];
}CAN_TxUnion_typedef;


		/*������Ϣ���нṹ��*/
typedef __packed struct
{
   __IO uint32_t  head;			//ͷָ��
	 __IO uint32_t  tail;			//βָ��
	 CAN_TxUnion_typedef Data[CAN_QUEUE_LENGTH];		//��������
}CAN_Msg_FIFO;

/****************************************************************

 Function: //		�����ߺ���
 Description: // ��ɶ������ֵ����ݱ仯�ļ�⣬����CAN��������CAN���������ȼ����벻ͬ����Ϣ���У�������CAN��������
 Calls: //������������
 Called By: //�ȽϺ��������ݰ���Ӻ���
 Input: //
 Output: // CAN��
 Return: // CAN������

******************************************************************/
uint8_t Producer_Event(void);

/****************************************************************************************

 Function: //�����ߺ���
 Description: // ����������������������Ϣ��������Ҫ���͵�CAN�������ͳ�ȥ
								���������ͳɹ���CAN������Ϣ�����Ƴ�
 Calls: //����CAN���ͺ���Send_MessagesQueue,Error_Handler������
 Called By: //������������
 Input: //

*******************************************************************************************/
void Deliver_Event(void);

#endif /*__LOCAL_CANPRODUCER_H*/
