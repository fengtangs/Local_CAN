#include "CallBack.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANCallBack
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description:CAN user operation callback function



-------------------------------------------------------------*/
		 //数据字典
extern type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH];
/****************************************************************

 Function: //接收消息回调函数定义
 Description: // 为一类函数，根据接收数据包不同，调用不同的回调函数，完成相应的功能
							必须将虚函数实现，才可以调用相应的回调函数。
 Calls: //
 Called By: //消费者函数
 Input: //uint16_t index字典索引，type_Dictionary_def *Pointer具体字典字段
 Output: // 
 Return: // 
 Others: //

******************************************************************/
/*用于控制FID的挡位或TCD的桥电流*/
__weak void CallBack_Func_FID_Gear_Or_TCD_Current(void *Control_Data) 
{
	 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);
  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_FID_Gear_Or_TCD_Current could be implemented in the user file
   */
}
/*分配检测器ID*/
__weak void CallBack_Func_Sensor_SET_NodeID(void *Control_Data) /*Sensor0 AD_data*/
{

	 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);
  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*?????ID*/

/*????x??,x??0~7*/
float b=0;
 void  CallBack_Func_channelx_temperature_set(void *Control_Data) /*Sensor0 AD_data*/
{
	 /* Prevent unused argument(s) compilation warning */
		
  //UNUSED(Control_Data);
	b=*((float *)Control_Data);
  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */}
/*????x?????,x??0~7*/
__weak void  CallBack_Func_channelx_temperature_protection_set(void *Control_Data) /*Sensor0 AD_data*/
{

		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*??xP??,x??0~7*/
__weak void  CallBack_Func_channel_xP_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*???P??*/
__weak void  CallBack_Func_backdoor_P_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*??xI??,x??0~7*/
__weak void  CallBack_Func_channel_xI_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*???I??*/
__weak void  CallBack_Func_backdoor_I_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*??xD??,x??0~7*/
__weak void  CallBack_Func_channel_xD_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*???D??*/
__weak void  CallBack_Func_backdoor_D_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*??x????/????,x??0~2*/
__weak void  CallBack_Func_channelx_fire_current_or_power_set(void *Control_Data)/*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*??x????,x??0~2*/
__weak void  CallBack_Func_channelx_fire_time_set(void *Control_Data)/*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*IO???*/
__weak void  CallBack_Func_IO_output(void *Control_Data)/*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*???????*/
__weak void  CallBack_Func_channel_switch_set(void *Control_Data)
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*0????????*/
__weak void  CallBack_Func_channel0_work_mode_set(void *Control_Data)
{

		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*????*/
__weak void  CallBack_Func_fire_switch(void *Control_Data)
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
