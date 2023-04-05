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
Ë÷Òı+³¤¶È
Èô³¤¶ÈÎª0£¬Ôò±íÊ¾¸ÃÄ£¿é²»ĞèÒª´Ë¶Î£¬»òµÈ´ı³õÊ¼»
¯
ËµÃ÷£ºÓÃ»§ÔÚÊ¹ÓÃÇ°£¬Ê×ÏÈ¸ù¾İËùÉèÖÃ×Öµä£¬Éú³É×Ô¼ºµÄ×ÖµäÄ¿Â¼
£¬ÒÔ·½±ã½øĞĞ³õÊ¼»¯ÅäÖÃ£¬°´Ğè¸ü¸Ä×ÖµäÄ¿Â¼³¤¶È
****************************************************************/
 Contents_def ContentsDictionary[CONTENTS_LENGTH]={
	{0,0},/*Segment_0*/
	{0,0},/*Segment_1*/
	{0,0},/*Segment_2*/
	{0,0},/*Segment_3*/
	{0,0},/*Segment_4*/
	{0,0},/*Segment_5*/
	{0,0},/*Segment_6*/
	{0,0}, /*Segment_7*/
	{0,2}, /*Segment_8*/
	{0,0}, /*Segment_9*/
	{0,0},/*Segment_10*/
	{0,0},/*Segment_11*/
	{0,0},/*Segment_12*/
	{0,0},/*Segment_13*/
	{0,0},/*Segment_14*/
	{0,0},/*Segment_15*/
	{0,0},/*Segment_16*/
	{0,0},/*Segment_17*/
	{0,0},/*Segment_18*/
	{0,0},/*Segment_19*/
	{0,0},/*Segment_20*/
	{0,0},/*Segment_21*/
	{0,0},/*Segment_22*/
	{0,0},/*Segment_23*/
	{0,0},/*Segment_24*/
	{0,0},/*Segment_25*/
	{0,0},/*Segment_26*/
	{0,0},/*Segment_27*/
	{0,0},/*Segment_28*/
	{0,0},/*Segment_29*/
	{0,0},/*Segment_30*/
	{0,0},/*Segment_31*/
	{0,0},/*Segment_32*/
	{0,0},/*Segment_33*/
	{0,0},/*Segment_34*/
	{0,0},/*Segment_35*/
	{0,0},/*Segment_36*/
	{0,0},/*Segment_37*/
	{0,0},/*Segment_38*/
	{0,0},/*Segment_39*/
	{0,0},/*Segment_40*/
	{0,0},/*Segment_41*/
	{0,0},/*Segment_42*/
	{0,0},/*Segment_43*/
	{0,0},/*Segment_44*/
	{0,0},/*Segment_45*/
	{0,0},/*Segment_46*/
	{0,0},/*Segment_47*/
	{0,0},/*Segment_48*/
	{0,0},/*Segment_49*/
	{0,0},/*Segment_50*/
	{0,0},/*Segment_51*/
	{0,0},/*Segment_52*/
	{0,0},/*Segment_53*/
	{0,0},/*Segment_54*/
	{0,0},/*Segment_55*/
}; 
	//Éú²úÕß²Ö¿â
 __packed char BufferData[BUFFER_LENGTH][8];

uint8_t data=11;

/************************************************
Ãû³Æ£º×Öµä±í
ËµÃ÷£ºÓÃ»§ÔÚÊ¹ÓÃÇ°£¬Ó¦ÏÈ¸ù¾İĞèÇóµ÷Õû×Öµä±í¸÷¸ö±äÁ¿¡£
½«Êı¾İÖ¸ÕëÖ¸ÏòÊı¾İÇø£¬°´Ğè·ÖÅäÉú²úÕß²Ö¿â¡£
**************************************************/
   type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH]={
	/*Segment_11*/ /*IO°å*/			
	/*ALL_index 0 Senment_0*/	{TYPE_UINT8,LOW_PRIORITY, NULL, &data,BufferData[0],NULL},			              /*µã»ğ¿ª¹Ø*/	
//	/*ALL_index 1 Senment_1*/	{TYPE_UINT8,LOW_PRIORITY, (void *)&Out_Value,(void *)&Fire_Data.Status,BufferData[0],OutPut},	/*I/OÊä³öÖµ*/
};
	
 
