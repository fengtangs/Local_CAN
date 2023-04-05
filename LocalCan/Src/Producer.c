#include "Producer.h"
#include "Dictionary.h"
#include "string.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANProducer
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: CAN Producer Function£¬
		Can packets are generated and put into different
		message queues, and can packets are sent

-------------------------------------------------------------*/

	/*ÓÅÏÈ¼¶¶ÓÁĞ¶¨Òå£¬extern¶¨Òå£¬Ó¦ÔÚÖ÷º¯Êı¶¨Òå*/
CAN_Msg_FIFO Send_High_Priority_Queue={0};		//¸ßÓÅÏÈ¼¶¶ÓÁĞ
CAN_Msg_FIFO Send_Low_Priority_Queue={0};			//µÍÓÅÏÈ¼¶¶ÓÁĞ
		//Êı¾İ×Öµä
extern type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH];
		//×ÖµäÄ¿Â¼
extern  Contents_def ContentsDictionary[CONTENTS_LENGTH]; 
	//CAN


//errorº¯µ÷
extern void Error_Handler(void);

	//Êı¾İ³¤¶ÈÊı×é
const uint8_t Data_Length[12]={2,3,5,2,3,5,5,4,6,7,8,8};

CAN_TxBuf_typedef CAN_Send;

 /****************************************************************************************

 Function: //uint8ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //uint16ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //uint32ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //int8ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //int16ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //int32ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //realÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //char arry3ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //char arry5ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //char arry6ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //char arry7ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //char arry8ÀàĞÍ±È½Ïº¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃ£ºuint8_t Producer(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //Êı¾İÀàĞÍ±È½Ïº¯Êı£¨º¯ÊıÖ¸Õë£©ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍµ÷ÓÃ²»Í¬µÄ±È½Ïº¯Êı£¬¸ù¾İÊı¾İ»º³åÇølast_data´æ´¢µÄÉÏ´ÎÊı¾İ
									£¬ÓëÏÖÓĞ²úÉúµÄÊı¾İ½øĞĞ±È½Ï£¬Èç¹û²»Í¬£¬Ôò·µ»Ø1£¬·ñÔò·µ»Ø0
 Calls: //ÎŞ
 Called By: //Éú²úÕßº¯Êıµ÷ÓÃuint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: //type_Dictionary_def *PointerÄ³Ò»¾ßÌåµÄ×Öµä¼ÇÂ¼
 Output: // 
 Return: // ·µ»Øuint8_tÀàĞÍ£¬Èç¹ûÊÇ1£¬ÔòËµÃ÷±È½ÏÊı¾İ²»Í¬£¬·ñÔò·µ»Ø0
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

 Function: //´¦ÀíÏûÏ¢¶ÓÁĞ·¢ËÍº¯Êı
 Description: // ½«ÏûÏ¢¶ÓÁĞÀïĞèÒª·¢ËÍµÄÊı¾İ·â×°·¢ËÍ
 Calls: //HAL_CAN_AddTxMessage(),HAL_CAN_GetTxMailboxesFreeLevel();HAL_Delay()
 Called By: //·¢²¼Õßº¯Êıµ÷ÓÃ£ºDeliver();
 Input: //Send_Packagef·¢ËÍÊı¾İ°ü½á¹¹Ìå
 Output: // ½«Êı¾İ°üÍ¨¹ıCAN×ÜÏß·¢ËÍ³öÈ¥
 Return: //·¢ËÍ³É¹¦£¬·µ»Ø1£¬Ê§°Ü·µ»Ø0
*******************************************************************************************/
static uint32_t Send_MessagesQueue(CAN_Send_package_typedef *Send_Package)
{
	uint32_t status= 0;
	uint32_t i=Send_Package->SegmentId;//¶ÎºÅ
	uint8_t SegmentIndex = Send_Package->Dict_SegmentIndex;

	CAN_Send.TxMessage.Identifier  = (BID<<6)+i;		//±ê×¼id ½«¶ÎºÅÓëBIDÉèÖÃÎª±ê×¼ID
	
	uint32_t index = Send_Package->Dict_SegmentIndex+ ContentsDictionary[i].StartIndex ;
	uint32_t DLength = Data_Length[Dictionary_Data[index].data_type];
	CAN_Send.TxMessage.DataLength =DLength<<16; 	//Êı¾İ¶Î³¤¶È	
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

 Function: // uint8Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // ÎŞ
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬void *object, char * last_data¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void uint8_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{

	uint8_t *ptr;
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	ptr=(uint8_t*)Send_Msg_Package;
	*ptr=*((uint8_t*)object);
	//½«producer²Ö¿â»º³å¸üĞÂ
	ptr=(uint8_t*)last_data;
	*ptr=*((uint8_t*)object);
	
}
	/****************************************************************

 Function: // uint16Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // ÎŞ
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void uint16_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	uint16_t *ptr;
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	ptr=(uint16_t*)Send_Msg_Package;
	*ptr=*((uint16_t*)object);
	//½«producer²Ö¿â»º³å¸üĞÂ
	ptr=(uint16_t*)last_data;
	*ptr=*((uint16_t*)object);
}
	/****************************************************************

 Function: // uint32Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // ÎŞ
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void uint32_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	uint32_t *ptr;
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	ptr=(uint32_t*)Send_Msg_Package;
	*ptr=*((uint32_t*)object);
	//½«producer²Ö¿â»º³å¸üĞÂ
	ptr=(uint32_t*)last_data;
	*ptr=*((uint32_t*)object);
}
	/****************************************************************

 Function: // int8Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // ÎŞ
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void int8_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	int8_t *ptr;
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	ptr=(int8_t*)Send_Msg_Package;
	*ptr=*((int8_t*)object);
	//½«producer²Ö¿â»º³å¸üĞÂ
	ptr=(int8_t*)last_data;
	*ptr=*((int8_t*)object);
}
	/****************************************************************

 Function: // int16Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // ÎŞ
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void int16_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	int16_t *ptr;
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	ptr=(int16_t*)Send_Msg_Package;
	*ptr=*((int16_t*)object);
	//½«producer²Ö¿â»º³å¸üĞÂ
	ptr=(int16_t*)last_data;
	*ptr=*((int16_t*)object);
}
	/****************************************************************

 Function: // int32Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // ÎŞ
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void int32_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	int32_t *ptr;
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	ptr=(int32_t*)Send_Msg_Package;
	*ptr=*((int32_t*)object);
	//½«producer²Ö¿â»º³å¸üĞÂ
	ptr=(int32_t*)last_data;
	*ptr=*((int32_t*)object);
}
	/****************************************************************

 Function: // floatÊı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // ÎŞ
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void real_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	float *ptr;
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	ptr=(float*)Send_Msg_Package;
	*ptr=*((float*)object);
	//½«producer²Ö¿â»º³å¸üĞÂ
	ptr=(float*)last_data;
	*ptr=*((float*)object);
}
	/****************************************************************

 Function: // char_arry3Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // memcpyº¯Êı
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void arry3_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	memcpy(Send_Msg_Package,object,3);
	//½«producer²Ö¿â»º³å¸üĞÂ
	memcpy(last_data,object,3);
}
	/****************************************************************

 Function: // char_arry5Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // memcpyº¯Êı
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void arry5_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	memcpy(Send_Msg_Package,object,5);
	//½«producer²Ö¿â»º³å¸üĞÂ
	memcpy(last_data,object,5);
}
	/****************************************************************

 Function: // char_arry6Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // memcpyº¯Êı
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void arry6_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{ 
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	memcpy(Send_Msg_Package,object,6);
	//½«producer²Ö¿â»º³å¸üĞÂ
	memcpy(last_data,object,6);
}
	/****************************************************************

 Function: // char_arry7Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // memcpyº¯Êı
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void arry7_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{ 
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	memcpy(Send_Msg_Package,object,7);
	uint8_t tem[7]={0};
	memcpy(tem ,Send_Msg_Package,7);
	//½«producer²Ö¿â»º³å¸üĞÂ
	memcpy(last_data,object,7);
}

	/****************************************************************

 Function: // char_arry8Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // memcpyº¯Êı
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
******************************************************************/
static void double_Add_Send_Package(char *Send_Msg_Package,void *object , char *last_data)
{ 
	//½«Êı¾İ°ü·ÅÈë¶ÓÁĞµÄÊı¾İÇø
	memcpy(Send_Msg_Package,object,8);
	//½«producer²Ö¿â»º³å¸üĞÂ
	memcpy(last_data,object,8);
}
/****************************************************************

 Function: // Êı¾İ°üÈë¶Ó²Ù×÷º¯Êı£¨º¯ÊıÊı×é£©£¬ÄÚ²¿º¯Êı
 Description: // ¸ù¾İ²»Í¬Êı¾İÀàĞÍ£¬µ÷ÓÃ²»Í¬µÄº¯Êı£¬Íê³ÉÊı¾İ°üµÄÈë¶Ó
 Calls: // ÎŞ
 Called By: //Éú²úÕßº¯Êı uint8_t Producer_Func(CAN_Msg_FIFO ,CAN_Msg_FIFO )
 Input: // Send_Msg_Package·¢ËÍÊı¾İ°ü£¬struct type_Dictionary_def *Pointer¾ßÌå×Öµä¼ÇÂ¼£¬
 Output: // 
 Return: // ·µ»ØÖµÎª¿ÕÀàĞÍ
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

 Function: //		Éú²úÕßº¯Êı
 Description: // Íê³É¶ÔÊı¾İ×ÖµäÊı¾İ±ä»¯µÄ¼ì²â£¬Éú²úCAN°ü£¬²¢½«CAN°ü¸ù¾İÓÅÏÈ¼¶·ÅÈë²»Í¬µÄÏûÏ¢¶ÓÁĞ£¬²¢·µ»ØCAN°üµÄÊıÁ¿
 Calls: //ÓÉÖ÷º¯Êıµ÷ÓÃ
 Called By: //±È½Ïº¯ÊıCompare£¬Êı¾İ°üÈë¶Óº¯ÊıAdd_Send_Package
 Input: //Á½¸ö·¢ËÍÏûÏ¢¶ÓÁĞSend_High_Priority_Queue,Send_Low_Priority_Queue
 Output: // CAN°ü
 Return: // CAN°üÊıÁ¿
 Others: //

******************************************************************/
uint8_t Producer_Event()
{
	uint8_t num=0;//¼ÇÂ¼ĞèÒªÉú²ú¶àÉÙcan°ü¡£
	uint16_t i=0;//Ñ­»·±éÀúÄ¿Â¼
	for(i=0;i<CONTENTS_LENGTH;i++)
	{
		if(ContentsDictionary[i].SegmentLength != 0)//¸Ã×Öµä¶Î±¾¼ì²âÆ÷ÓÃµ½
		{
			int j,id,index=ContentsDictionary[i].StartIndex;	//j ±éÀú¶Î   idÊı¾İÀàĞÍ  index×Ü×ÖµäÏÂ±ê
			for(j=index;j<index+ContentsDictionary[i].SegmentLength;j++)
			{
				if(Dictionary_Data[j].producer_object != NULL)//Èç¹ûÊÇÉú²úÕß
				{			id = Dictionary_Data[j].data_type;
					if((*Compare[id])(Dictionary_Data[j].producer_object,Dictionary_Data[j].data_buffer))//µ÷ÓÃ±È½Ïº¯Êı£¬Èç¹ûÊı¾İ¸Ä±ä£¬¾ÍÉú²úCAN°ü
					{
											
						if(Dictionary_Data[j].priority == HIGH_PRIORITY )			//¸ßÓÅÏÈ¼¶µÄ»°£¬·Åµ½¸ßÓÅÏÈ¼¶¶ÓÁĞ,²¢ÇÒ¸üĞÂlast_dataÊı¾İ
						{
									
									Send_High_Priority_Queue.Data[Send_High_Priority_Queue.tail].CAN_Msg.Dict_SegmentIndex =(uint8_t)(j-index);//Êı¾İÓòµÄindex
									Send_High_Priority_Queue.Data[Send_High_Priority_Queue.tail].CAN_Msg.SegmentId = (uint8_t)(i);//¶ÎË÷Òı
									(*Add_Send_Package[id])((Send_High_Priority_Queue.Data[Send_High_Priority_Queue.tail].CAN_Msg.Data),Dictionary_Data[j].producer_object,Dictionary_Data[j].data_buffer);
									Send_High_Priority_Queue.tail=(Send_High_Priority_Queue.tail+1)%CAN_QUEUE_LENGTH;//¶ÓÁĞºóÒÆ
						}
						else																							//µÍÓÅÏÈ¼¶µÄ»°£¬·Åµ½µÍÓÅÏÈ¼¶¶ÓÁĞ,²¢ÇÒ¸üĞÂlast_dataÊı¾İ
						{
									Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.tail].CAN_Msg.Dict_SegmentIndex = (uint8_t)(j-index);//Êı¾İÓòµÄindex
									Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.tail].CAN_Msg.SegmentId = (uint8_t)(i);//¶ÎË÷Òı
									(*Add_Send_Package[id])((Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.tail].CAN_Msg.Data),Dictionary_Data[j].producer_object,Dictionary_Data[j].data_buffer);
									Send_Low_Priority_Queue.tail=(Send_Low_Priority_Queue.tail+1)%CAN_QUEUE_LENGTH;//¶ÓÁĞºóÒÆ
							
						}
						num++;
					
					}//end_if ±È½Ïº¯Êı
				}//end_if Éú²úÕß
			}//end_for for¶ÎÑ­»·
		}//end_if ¶Î³¤¶ÈÅĞ¶Ï
	}//end_for Ä¿Â¼Ñ­»·
	return num;
}//end_Producer_Func
/****************************************************************************************

 Function: //·¢²¼Õßº¯Êı
 Description: // ·¢²¼º¯Êı£¬½«Á½¸ö·¢ËÍÏûÏ¢¶ÓÁĞÀïĞèÒª·¢ËÍµÄCAN°ü£¬·¢ËÍ³öÈ¥
								¡£²¢½«·¢ËÍ³É¹¦µÄCAN°ü´ÓÏûÏ¢¶ÓÁĞÒÆ³ı
 Calls: //µ÷ÓÃCAN·¢ËÍº¯ÊıSend_MessagesQueue,Error_Handler´íÎó´¦Àí
 Called By: //±»Ö÷º¯Êıµ÷ÓÃ
 Input: //Á½¸ö·¢ËÍÏûÏ¢¶ÓÁĞ

*******************************************************************************************/
void Deliver_Event(void)
	{
		while(Send_High_Priority_Queue.head!=Send_High_Priority_Queue.tail)//¸ßÓÅÏÈ¼¶ÓĞÊı¾İÒª·¢ËÍ
		{
				if(Send_MessagesQueue(&Send_High_Priority_Queue.Data[Send_High_Priority_Queue.head].CAN_Msg)== HAL_OK)//·¢ËÍ¡£
				{
						Send_High_Priority_Queue.head = (Send_High_Priority_Queue.head + 1)%CAN_QUEUE_LENGTH;	//½«·¢ËÍ¹ıµÄ¶ÓÁĞºóÒÆ
				}
				else				//·¢ËÍÊ§°Ü
				{
						Error_Handler();
				}
		}//end_while ¸ßÓÅÏÈ¼¶
		
		while(Send_Low_Priority_Queue.head!=Send_Low_Priority_Queue.tail)//µÍÓÅÏÈ¼¶ÓĞÊı¾İÒª·¢ËÍ
		{
				if(Send_MessagesQueue(&Send_Low_Priority_Queue.Data[Send_Low_Priority_Queue.head].CAN_Msg)==HAL_OK)//·¢ËÍ.
				{
						Send_Low_Priority_Queue.head = (Send_Low_Priority_Queue.head + 1)%CAN_QUEUE_LENGTH;	//½«·¢ËÍ¹ıµÄ¶ÓÁĞºóÒÆ£
				
				}
				else				//·¢ËÍÊ§°Ü
				{
						Error_Handler();
				}
				while(Send_High_Priority_Queue.head!=Send_High_Priority_Queue.tail)//¸ßÓÅÏÈ¼¶ÓĞÊı¾İÒª·¢ËÍ
				{
					if(Send_MessagesQueue(&Send_High_Priority_Queue.Data[Send_High_Priority_Queue.head].CAN_Msg)== HAL_OK )//·¢ËÍ¡£
					{
							Send_High_Priority_Queue.head = (Send_High_Priority_Queue.head + 1)%CAN_QUEUE_LENGTH;	//½«·¢ËÍ¹ıµÄ¶ÓÁĞºóÒÆ
					}
					else				//·¢ËÍÊ§°Ü
					{
							Error_Handler();
					}
				}//end_while ¸ßÓÅÏÈ¼¶
		}//end_while µÍÓÅÏÈ¼¶
}
