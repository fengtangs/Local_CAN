#include "Dictionary.h"
#include "CallBack.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANDictionary
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description: CAN data dictionary definition

-------------------------------------------------------------*/

/**************************************************************
¶¨ÒåÄ¿Â¼
Ë÷Òý+³¤¶È
Èô³¤¶ÈÎª0£¬Ôò±íÊ¾¸ÃÄ£¿é²»ÐèÒª´Ë¶Î£¬»òµÈ´ý³õÊ¼»
¯
ËµÃ÷£ºÓÃ»§ÔÚÊ¹ÓÃÇ°£¬Ê×ÏÈ¸ù¾ÝËùÉèÖÃ×Öµä£¬Éú³É×Ô¼ºµÄ×ÖµäÄ¿Â¼
£¬ÒÔ·½±ã½øÐÐ³õÊ¼»¯ÅäÖÃ£¬°´Ðè¸ü¸Ä×ÖµäÄ¿Â¼³¤¶È
****************************************************************/
 Contents_def ContentsDictionary[CONTENTS_LENGTH]={
	{0,0},/*Segment_0*/
	{2,3},/*Segment_1*/
	{5,0},/*Segment_2*/
	{8,0},/*Segment_3*/
	{11,0},/*Segment_4*/

}; 
	//Éú²úÕß²Ö¿â
 __packed char BufferData[BUFFER_LENGTH][8];
char SN[7]={0};
char Rx_ID[7]={0};
int32_t AD_Data=0;
int32_t AD_Data_Filiter=0;
uint8_t sensor_type = 0;
uint8_t sensor_type1 = 0;
int16_t FID_Gear_Or_TCD_Current=0;
/************************************************
Ãû³Æ£º×Öµä±í
ËµÃ÷£ºÓÃ»§ÔÚÊ¹ÓÃÇ°£¬Ó¦ÏÈ¸ù¾ÝÐèÇóµ÷Õû×Öµä±í¸÷¸ö±äÁ¿¡£
½«Êý¾ÝÖ¸ÕëÖ¸ÏòÊý¾ÝÇø£¬°´Ðè·ÖÅäÉú²úÕß²Ö¿â¡£
**************************************************/
 const type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH]={
	 /*Segment_0*/
	/*ALL_index 0 Senment_0*/	{TYPE_CHAR_ARRAY_7,HIGH_PRIORITY,NULL,SN,BufferData[0],NULL},			                       /*sensor ×¢²áSNÐÅÏ¢*/
	/*ALL_index 1 Senment_1*/	{TYPE_CHAR_ARRAY_7,HIGH_PRIORITY,Rx_ID,NULL,NULL,CallBack_Func_Sensor_SET_NodeID},			     /*sensor ·ÖÅäIDÐÅÏ¢*/
	
	/*Segment_1*/ /*sensor¡ª¡ª0*/
	/*ALL_index 2 Senment_0*/		{TYPE_INT32,HIGH_PRIORITY,NULL,&AD_Data,BufferData[1],NULL},																/*Sensor0 AD_data*/
	/*ALL_index 3 Senment_1*/		{TYPE_UINT8,LOW_PRIORITY,NULL,&sensor_type,BufferData[2],NULL},	 																/*sensor0 type*/
	/*ALL_index 4 Senment_2*/		{TYPE_INT16,LOW_PRIORITY,&FID_Gear_Or_TCD_Current,NULL,NULL,CallBack_Func_FID_Gear_Or_TCD_Current},			   /*sensor0 µµÎ»ÇÅµçÁ÷*/
	
	/*Segment_2*/ /*sensor¡ª¡ª1*/
	/*ALL_index_5 Senment_0*/		{TYPE_INT32,LOW_PRIORITY,NULL,&AD_Data,BufferData[3],NULL},																/*Sensor1 AD_data*/
	/*ALL_index_6 Senment_1*/		{TYPE_UINT8,LOW_PRIORITY,NULL,&sensor_type1,BufferData[4],NULL},	 			                            /*sensor1 type*/
	/*ALL_index_7 Senment_2*/		{TYPE_INT16,LOW_PRIORITY,&FID_Gear_Or_TCD_Current,NULL,NULL,CallBack_Func_FID_Gear_Or_TCD_Current},				   /*sensor1 µµÎ»ÇÅµçÁ÷*/

	/*Segment_3*/ /*sensor¡ª¡ª2*/
	/*ALL_index_8 Senment_0*/		{TYPE_INT32,HIGH_PRIORITY,NULL,&AD_Data,BufferData[5],NULL},															/*Sensor2 AD_data*/
	/*ALL_index_9 Senment_1*/		{TYPE_UINT8,LOW_PRIORITY,NULL,&sensor_type,BufferData[6],NULL},	 		                            /*sensor2 type*/
	/*ALL_index_10 Senment_2*/	{TYPE_INT16,LOW_PRIORITY,&FID_Gear_Or_TCD_Current,NULL,NULL,CallBack_Func_FID_Gear_Or_TCD_Current},			   /*sensor2 µµÎ»ÇÅµçÁ÷*/	
	
	/*Segment_4*/ /*sensor¡ª¡ª3*/
	/*ALL_index_11 Senment_0*/		{TYPE_INT32,HIGH_PRIORITY,NULL,&AD_Data,BufferData[7],NULL},																/*Sensor3AD_data*/
	/*ALL_index_12 Senment_1*/		{TYPE_UINT8,LOW_PRIORITY,NULL,&sensor_type,BufferData[8],NULL},	 	                             /*sensor3 type*/
	/*ALL_index_13 Senment_2*/		{TYPE_INT16,LOW_PRIORITY,&FID_Gear_Or_TCD_Current,NULL,NULL,CallBack_Func_FID_Gear_Or_TCD_Current},			   /*sensor3 µµÎ»ÇÅµçÁ÷*/		

	
/*Segment_5*/ /*???——??*/
	/*ALL_index_14 Senment_0*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,BufferData[9],NULL},			                                     /*channal_X temperature*/
	/*ALL_index_15 Senment_1*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,BufferData[10],NULL},
	/*ALL_index_16 Senment_2*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,BufferData[11],NULL},
	/*ALL_index_17 Senment_3*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,BufferData[12],NULL},
	/*ALL_index_18 Senment_4*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,BufferData[13],NULL},
	/*ALL_index_19 Senment_5*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,BufferData[14],NULL},
	/*ALL_index_20 Senment_6*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,BufferData[15],NULL},
	/*ALL_index_21 Senment_7*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,BufferData[16],NULL},
	
	/*Segment_6*/ /*???——????*/
	/*ALL_index_index 22 Senment_0*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_set},			   /*channal set temperature 	*/
	/*ALL_index_index 23 Senment_1*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_set},
	/*ALL_index_index 24 Senment_2*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_set},
	/*ALL_index_index 25 Senment_3*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_set},
	/*ALL_index_index 26 Senment_4*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_set},
	/*ALL_index_index 27 Senment_5*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_set},
	/*ALL_index_index 28 Senment_6*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_set},
	/*ALL_index_index 29 Senment_7*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_set},
	
	/*Segment_7*/ /*???——??????*/	
	/*ALL_index 30 Senment_0*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_protection_set},			/*channal_X(0 to 7) protect temperature*/
	/*ALL_index 31 Senment_1*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_protection_set},
	/*ALL_index 32 Senment_2*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_protection_set},
	/*ALL_index 33 Senment_3*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_protection_set},
	/*ALL_index 34 Senment_4*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_protection_set},
	/*ALL_index 35 Senment_5*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_protection_set},
	/*ALL_index 36 Senment_6*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_protection_set},
	/*ALL_index 37 Senment_7*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_temperature_protection_set},

	/*Segment_8*/ /*???——????*/		
	/*ALL_index 38 Senment_0*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xP_set},			/*channal_X(0 to 7) set_XP */
	/*ALL_index 39 Senment_1*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xP_set},
	/*ALL_index 40 Senment_2*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xP_set},
	/*ALL_index 41 Senment_3*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xP_set},
	/*ALL_index 42 Senment_4*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xP_set},
	/*ALL_index 43 Senment_5*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xP_set},
	/*ALL_index 44 Senment_6*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xP_set},
	/*ALL_index 45 Senment_7*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xP_set},	
	/*ALL_index 46 Senment_8*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_backdoor_P_set},			/*???P??*/	
	/*ALL_index 47 Senment_9*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xI_set},			/*channal set_XI */
	/*ALL_index 48 Senment_10*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xI_set},
	/*ALL_index 49 Senment_11*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xI_set},
	/*ALL_index 50 Senment_12*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xI_set},
	/*ALL_index 51 Senment_13*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xI_set},
	/*ALL_index 52 Senment_14*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xI_set},
	/*ALL_index 53 Senment_15*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xI_set},
	/*ALL_index 54 Senment_16*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xI_set},
	/*ALL_index 55 Senment_17*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_backdoor_D_set},			/*???I??*/
	/*ALL_index 56 Senment_18*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xD_set},			/*channal set_XD */
	/*ALL_index 57 Senment_19*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xD_set},	
	/*ALL_index 58 Senment_20*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xD_set},	
	/*ALL_index 59 Senment_21*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xD_set},	
	/*ALL_index 60 Senment_22*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xD_set},	
	/*ALL_index 61 Senment_23*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xD_set},	
	/*ALL_index 62 Senment_24*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xD_set},	
	/*ALL_index 63 Senment_25*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_xD_set},	
	/*ALL_index 64 Senment_26*/	{TYPE_REAL,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_backdoor_D_set},			/*???D??*/

	/*Segment_9*/ /*???——status info*/			
	/*ALL_index 65 Senment_0*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[17],NULL},			/*channal status info*/
	/*ALL_index 66 Senment_1*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[18],NULL},
	/*ALL_index 67 Senment_2*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[19],NULL},
	/*ALL_index 68 Senment_3*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[20],NULL},
	/*ALL_index 69 Senment_4*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[21],NULL},
	/*ALL_index 70 Senment_5*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[22],NULL},
	/*ALL_index 71 Senment_6*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[23],NULL},
	/*ALL_index 72 Senment_7*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[24],NULL},

	/*Segment_10*/ /*???*/			
	/*ALL_index 73 Senment_0*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[25],NULL},			/*??????*/		
	/*ALL_index 74 Senment_1*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel_switch_set},			/*???????*/	
	/*ALL_index 75 Senment_2*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channel0_work_mode_set},			/*0????????*/
	
	/*Segment_11*/ /*IO?*/			
	/*ALL_index 76 Senment_0*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_fire_switch},			/*????*/	
	/*ALL_index 77 Senment_1*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,BufferData[26],NULL},			/*fire_status */	
	/*ALL_index 78 Senment_2*/	{TYPE_UINT16,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_fire_current_or_power_set},			/*??????????*/
	/*ALL_index 79 Senment_3*/	{TYPE_UINT16,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_fire_current_or_power_set},
	/*ALL_index 80 Senment_4*/	{TYPE_UINT16,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_fire_current_or_power_set},
	/*ALL_index 81 Senment_5*/	{TYPE_UINT16,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_fire_time_set},			/*????*/
	/*ALL_index 82 Senment_6*/	{TYPE_UINT16,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_fire_time_set},
	/*ALL_index 83 Senment_7*/	{TYPE_UINT16,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_channelx_fire_time_set},
	/*ALL_index 84 Senment_8*/	{TYPE_UINT8,LOW_PRIORITY,NULL,NULL,NULL,CallBack_Func_IO_output},			/*I/O???*/
	
	};
 
