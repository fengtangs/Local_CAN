#ifndef __CANDICTIONARY_H
#define __CANDICTIONARY_H
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANDictionary
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: CAN data dictionary definition

-------------------------------------------------------------*/
#define STMF1									0						//选择芯片   0：stm32f1，1 stm32H7

#if !STMF1
#include "stm32f1xx_hal.h"
#else 
#include "stm32h7xx_hal.h"
#endif

#define DICTIONARY_LENGTH  				100					/*字典长度*/
#define SEGMENTDICTIONARY_LENGTH  256					/*段字典长度*/
#define CAN_QUEUE_LENGTH  				100					/*消息队列长度*/
#define BUFFER_LENGTH 		 				50					/*数据缓区长度*/
#define CONTENTS_LENGTH 				  56					/*目录长度*/

#define BID 		 									0x0					/*系统版号*/
#define STANDARD_MODE							0						//设置模式   0：标准模式，1拓展模式
#define SET_MODE									0						//设置模式   0：标准模式，1调试


#define TYPE_UINT8								0					  /*数据类型*/
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

				/*优先级*/
#define 	HIGH_PRIORITY							0xc					
#define 	LOW_PRIORITY							0xd
				
				/*数据字典类型定义*/
typedef struct type_Dictionary_def
{
	uint8_t data_type;																							/*数据类型*/
	uint8_t priority;																								/*优先级:高0xc 低0xd*/
	void 	*consumer_object;																					/*消费者数据区指针*/
	void *producer_object;																					/*生产者数据区指针*/
	char *data_buffer;																							/*生产者仓库指针*/
	void (*Callback_func)(void *);																	/*回调函数*/
}type_Dictionary_def;

			/*目录定义*/
typedef struct 
{
	uint16_t StartIndex;					/*起始index*/
	uint16_t SegmentLength;				/*段长*/
}Contents_def;
#endif /*__CANDICTIONARY2_H*/


