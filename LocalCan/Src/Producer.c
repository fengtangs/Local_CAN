#include "Producer.h"
#include "Dictionary.h"
#include "string.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANProducer
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: CAN Producer Function��
		Can packets are generated and put into different
		message queues, and can packets are sent

-------------------------------------------------------------*/

	/*���ȼ����ж��壬extern���壬Ӧ������������*/
CAN_Msg_FIFO Send_High_Priority_Queue={0};		//�����ȼ�����
CAN_Msg_FIFO Send_Low_Priority_Queue={0};			//�����ȼ�����
		//�����ֵ�
extern type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH];
		//�ֵ�Ŀ¼
extern  Contents_def ContentsDictionary[CONTENTS_LENGTH]; 
	//CAN


//error����
extern void Error_Handler(void);

	//���ݳ�������
const uint8_t Data_Length[12]={2,3,5,2,3,5,5,4,6,7,8,8};

CAN_TxBuf_typedef CAN_Send;

 /****************************************************************************************

 Function: //uint8���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //uint16���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //uint32���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //int8���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //int16���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //int32���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //real���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //char arry3���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //char arry5���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //char arry6���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //char arry7���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //char arry8���ͱȽϺ������ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ������ã�uint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //�������ͱȽϺ���������ָ�룩�ڲ�����
 Description: // ���ݲ�ͬ�������͵��ò�ͬ�ıȽϺ������������ݻ�����last_data�洢���ϴ�����
									�������в��������ݽ��бȽϣ������ͬ���򷵻�1�����򷵻�0
 Calls: //��
 Called By: //�����ߺ�������uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *Pointerĳһ������ֵ��¼
 Output: // 
 Return: // ����uint8_t���ͣ������1����˵���Ƚ����ݲ�ͬ�����򷵻�0
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

 Function: //������Ϣ���з��ͺ���
 Description: // ����Ϣ��������Ҫ���͵����ݷ�װ����
 Calls: //HAL_CAN_AddTxMessage(),HAL_CAN_GetTxMailboxesFreeLevel();HAL_Delay()
 Called By: //�����ߺ������ã�Deliver();
 Input: //Send_Packagef�������ݰ��ṹ��
 Output: // �����ݰ�ͨ��CAN���߷��ͳ�ȥ
 Return: //���ͳɹ�������1��ʧ�ܷ���0
*******************************************************************************************/
static uint32_t Send_MessagesQueue(CAN_Send_package_typedef *Send_Package)
{
	uint32_t status= 0;
	uint32_t i=Send_Package->SegmentId;//�κ�
	uint8_t SegmentIndex = Send_Package->Dict_SegmentIndex;

	CAN_Send.TxMessage.Identifier  = (BID<<6)+i;		//��׼id ���κ���BID����Ϊ��׼ID
	
	uint32_t index = Send_Package->Dict_SegmentIndex+ ContentsDictionary[i].StartIndex ;
	uint32_t DLength = Data_Length[Dictionary_Data[index].data_type];
	CAN_Send.TxMessage.DataLength =DLength<<16; 	//���ݶγ���	
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

 Function: // uint8���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // ��
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���void *object, char * last_data�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void uint8_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{

	uint8_t *ptr;
	//�����ݰ�������е�������
	ptr=(uint8_t*)Send_Msg_Package;
	*ptr=*((uint8_t*)object);
	//��producer�ֿ⻺�����
	ptr=(uint8_t*)last_data;
	*ptr=*((uint8_t*)object);
	
}
	/****************************************************************

 Function: // uint16���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // ��
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void uint16_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	uint16_t *ptr;
	//�����ݰ�������е�������
	ptr=(uint16_t*)Send_Msg_Package;
	*ptr=*((uint16_t*)object);
	//��producer�ֿ⻺�����
	ptr=(uint16_t*)last_data;
	*ptr=*((uint16_t*)object);
}
	/****************************************************************

 Function: // uint32���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // ��
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void uint32_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	uint32_t *ptr;
	//�����ݰ�������е�������
	ptr=(uint32_t*)Send_Msg_Package;
	*ptr=*((uint32_t*)object);
	//��producer�ֿ⻺�����
	ptr=(uint32_t*)last_data;
	*ptr=*((uint32_t*)object);
}
	/****************************************************************

 Function: // int8���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // ��
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void int8_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	int8_t *ptr;
	//�����ݰ�������е�������
	ptr=(int8_t*)Send_Msg_Package;
	*ptr=*((int8_t*)object);
	//��producer�ֿ⻺�����
	ptr=(int8_t*)last_data;
	*ptr=*((int8_t*)object);
}
	/****************************************************************

 Function: // int16���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // ��
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void int16_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	int16_t *ptr;
	//�����ݰ�������е�������
	ptr=(int16_t*)Send_Msg_Package;
	*ptr=*((int16_t*)object);
	//��producer�ֿ⻺�����
	ptr=(int16_t*)last_data;
	*ptr=*((int16_t*)object);
}
	/****************************************************************

 Function: // int32���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // ��
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void int32_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	int32_t *ptr;
	//�����ݰ�������е�������
	ptr=(int32_t*)Send_Msg_Package;
	*ptr=*((int32_t*)object);
	//��producer�ֿ⻺�����
	ptr=(int32_t*)last_data;
	*ptr=*((int32_t*)object);
}
	/****************************************************************

 Function: // float���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // ��
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void real_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	float *ptr;
	//�����ݰ�������е�������
	ptr=(float*)Send_Msg_Package;
	*ptr=*((float*)object);
	//��producer�ֿ⻺�����
	ptr=(float*)last_data;
	*ptr=*((float*)object);
}
	/****************************************************************

 Function: // char_arry3���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // memcpy����
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void arry3_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	//�����ݰ�������е�������
	memcpy(Send_Msg_Package,object,3);
	//��producer�ֿ⻺�����
	memcpy(last_data,object,3);
}
	/****************************************************************

 Function: // char_arry5���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // memcpy����
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void arry5_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	//�����ݰ�������е�������
	memcpy(Send_Msg_Package,object,5);
	//��producer�ֿ⻺�����
	memcpy(last_data,object,5);
}
	/****************************************************************

 Function: // char_arry6���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // memcpy����
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void arry6_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{ 
	//�����ݰ�������е�������
	memcpy(Send_Msg_Package,object,6);
	//��producer�ֿ⻺�����
	memcpy(last_data,object,6);
}
	/****************************************************************

 Function: // char_arry7���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // memcpy����
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void arry7_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{ 
	//�����ݰ�������е�������
	memcpy(Send_Msg_Package,object,7);
	uint8_t tem[7]={0};
	memcpy(tem ,Send_Msg_Package,7);
	//��producer�ֿ⻺�����
	memcpy(last_data,object,7);
}

	/****************************************************************

 Function: // char_arry8���ݰ���Ӳ����������ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // memcpy����
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
******************************************************************/
static void double_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{ 
	//�����ݰ�������е�������
	memcpy(Send_Msg_Package,object,8);
	//��producer�ֿ⻺�����
	memcpy(last_data,object,8);
}
/****************************************************************

 Function: // ���ݰ���Ӳ����������������飩���ڲ�����
 Description: // ���ݲ�ͬ�������ͣ����ò�ͬ�ĺ�����������ݰ������
 Calls: // ��
 Called By: //�����ߺ��� uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package�������ݰ���struct type_Dictionary_def *Pointer�����ֵ��¼��
 Output: // 
 Return: // ����ֵΪ������
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

 Function: //		�����ߺ���
 Description: // ��ɶ������ֵ����ݱ仯�ļ�⣬����CAN��������CAN���������ȼ����벻ͬ����Ϣ���У�������CAN��������
 Calls: //������������
 Called By: //�ȽϺ���Compare�����ݰ���Ӻ���Add_Send_Package
 Input: //����������Ϣ����Send_High_Priority_Queue,Send_Low_Priority_Queue
 Output: // CAN��
 Return: // CAN������
 Others: //

******************************************************************/
uint8_t Producer_Event()
{
	uint8_t num=0;//��¼��Ҫ��������can����
	uint16_t i=0;//ѭ������Ŀ¼
	for(i=0;i<CONTENTS_LENGTH;i++)
	{
		if(ContentsDictionary[i].SegmentLength != 0)//���ֵ�α�������õ�
		{
			int j,id,index=ContentsDictionary[i].StartIndex;	//j ������   id��������  index���ֵ��±�
			for(j=index;j<index+ContentsDictionary[i].SegmentLength;j++)
			{
				if(Dictionary_Data[j].producer_object != NULL)//�����������
				{			id = Dictionary_Data[j].data_type;
					if((*Compare[id])(Dictionary_Data[j].producer_object,Dictionary_Data[j].data_buffer))//���ñȽϺ�����������ݸı䣬������CAN��
					{
											
						if(Dictionary_Data[j].priority == HIGH_PRIORITY )			//�����ȼ��Ļ����ŵ������ȼ�����,���Ҹ���last_data����
						{
									
									Send_High_Priority_Queue.Data[Send_High_Priority_Queue.tail].CAN_Msg.Dict_SegmentIndex =(uint8_t)(j-index);//�������index
									Send_High_Priority_Queue.Data[Send_High_Priority_Queue.tail].CAN_Msg.SegmentId = (uint8_t)(i);//������
									(*Add_Send_Package[id])((Send_High_Priority_Queue.Data[Send_High_Priority_Queue.tail].CAN_Msg.Data),Dictionary_Data[j].producer_object,Dictionary_Data[j].data_buffer);
									Send_High_Priority_Queue.tail=(Send_High_Priority_Queue.tail+1)%CAN_QUEUE_LENGTH;//���к���
						}
						else																							//�����ȼ��Ļ����ŵ������ȼ�����,���Ҹ���last_data����
						{
									Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.tail].CAN_Msg.Dict_SegmentIndex = (uint8_t)(j-index);//�������index
									Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.tail].CAN_Msg.SegmentId = (uint8_t)(i);//������
									(*Add_Send_Package[id])((Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.tail].CAN_Msg.Data),Dictionary_Data[j].producer_object,Dictionary_Data[j].data_buffer);
									Send_Low_Priority_Queue.tail=(Send_Low_Priority_Queue.tail+1)%CAN_QUEUE_LENGTH;//���к���
							
						}
						num++;
					
					}//end_if �ȽϺ���
				}//end_if ������
			}//end_for for��ѭ��
		}//end_if �γ����ж�
	}//end_for Ŀ¼ѭ��
	return num;
}//end_Producer_Func
/****************************************************************************************

 Function: //�����ߺ���
 Description: // ����������������������Ϣ��������Ҫ���͵�CAN�������ͳ�ȥ
								���������ͳɹ���CAN������Ϣ�����Ƴ�
 Calls: //����CAN���ͺ���Send_MessagesQueue,Error_Handler������
 Called By: //������������
 Input: //����������Ϣ����

*******************************************************************************************/
void Deliver_Event(void)
	{
		while(Send_High_Priority_Queue.head!=Send_High_Priority_Queue.tail)//�����ȼ�������Ҫ����
		{
				if(Send_MessagesQueue(&Send_High_Priority_Queue.Data[Send_High_Priority_Queue.head].CAN_Msg)== HAL_OK)//���͡�
				{
						Send_High_Priority_Queue.head = (Send_High_Priority_Queue.head + 1)%CAN_QUEUE_LENGTH;	//�����͹��Ķ��к���
				}
				else				//����ʧ��
				{
						Error_Handler();
				}
		}//end_while �����ȼ�
		
		while(Send_Low_Priority_Queue.head!=Send_Low_Priority_Queue.tail)//�����ȼ�������Ҫ����
		{
				if(Send_MessagesQueue(&Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.head].CAN_Msg)==HAL_OK)//����.
				{
						Send_Low_Priority_Queue.head = (Send_Low_Priority_Queue.head + 1)%CAN_QUEUE_LENGTH;	//�����͹��Ķ��к��ƣ
				
				}
				else				//����ʧ��
				{
						Error_Handler();
				}
				while(Send_High_Priority_Queue.head!=Send_High_Priority_Queue.tail)//�����ȼ�������Ҫ����
				{
					if(Send_MessagesQueue(&Send_High_Priority_Queue.Data[Send_High_Priority_Queue.head].CAN_Msg)== HAL_OK )//���͡�
					{
							Send_High_Priority_Queue.head = (Send_High_Priority_Queue.head + 1)%CAN_QUEUE_LENGTH;	//�����͹��Ķ��к���
					}
					else				//����ʧ��
					{
							Error_Handler();
					}
				}//end_while �����ȼ�
		}//end_while �����ȼ�
}
