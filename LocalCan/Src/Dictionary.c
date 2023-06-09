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
定义目录
索引+长度
若长度为0，则表示该模块不需要此段，或等待初始�
�
说明：用户在使用前，首先根据所设置字典，生成自己的字典目录
，以方便进行初始化配置，按需更改字典目录长度
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
	//生产者仓库
 __packed char BufferData[BUFFER_LENGTH][8];

uint8_t data=11;

/************************************************
名称：字典表
说明：用户在使用前，应先根据需求调整字典表各个变量。
将数据指针指向数据区，按需分配生产者仓库。
**************************************************/
   type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH]={
	/*Segment_11*/ /*IO板*/			
	/*ALL_index 0 Senment_0*/	{TYPE_UINT8,LOW_PRIORITY, NULL, &data,BufferData[0],NULL},			              /*点火开关*/	
//	/*ALL_index 1 Senment_1*/	{TYPE_UINT8,LOW_PRIORITY, (void *)&Out_Value,(void *)&Fire_Data.Status,BufferData[0],OutPut},	/*I/O输出值*/
};
	
 
