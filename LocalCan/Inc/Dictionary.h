#ifndef __CANDICTIONARY_H
#define __CANDICTIONARY_H
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANDictionary
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: CAN data dictionary definition

-------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#define DICTIONARY_LENGTH  				8					/*�ֵ䳤��*/
#define SEGMENTDICTIONARY_LENGTH  256					/*���ֵ䳤��*/
#define CAN_QUEUE_LENGTH  				100					/*��Ϣ���г���*/
#define BUFFER_LENGTH 		 				1					/*���ݻ�������*/
#define CONTENTS_LENGTH 				  56					/*Ŀ¼����*/

#define BID 		 									0x0					/*ϵͳ���*/
#define STANDARD_MODE							0						//����ģʽ   0����׼ģʽ��1��չģʽ

#define TYPE_UINT8								0					  /*��������*/
#define TYPE_UINT16								1
#define TYPE_UINT32								2
#define TYPE_INT8									3
#define TYPE_INT16								4
#define TYPE_INT32 								5
#define TYPE_REAL									6
#define TYPE_CHAR_ARRAY_3					7
#define TYPE_CHAR_ARRAY_5					8
#define TYPE_CHAR_ARRAY_6					9
#define TYPE_CHAR_ARRAY_7					10
#define TYPE_DOUBLE								11

				/*���ȼ�*/
#define 	HIGH_PRIORITY							0xc					
#define 	LOW_PRIORITY							0xd
				
				/*�����ֵ����Ͷ���*/
typedef struct type_Dictionary_def
{
	uint8_t data_type;																							/*��������*/
	uint8_t priority;																								/*���ȼ�:��0xc ��0xd*/
	void 	*consumer_object;																					/*������������ָ��*/
	void *producer_object;																					/*������������ָ��*/
	char *data_buffer;																							/*�����ֿ߲�ָ��*/
	void (*Callback_func)(void *);																	/*�ص�����*/
}type_Dictionary_def;

			/*Ŀ¼����*/
typedef struct 
{
	uint16_t StartIndex;					/*��ʼindex*/
	uint16_t SegmentLength;				/*�γ�*/
}Contents_def;

extern       Contents_def ContentsDictionary[CONTENTS_LENGTH];
extern       type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH];




#endif /*__CANDICTIONARY2_H*/


