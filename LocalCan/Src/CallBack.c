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
int32_t a=0;
void CallBack_Func_FID_Gear_Or_TCD_Current(void *Control_Data) 
{
	 /* Prevent unused argument(s) compilation warning */
  //UNUSED(Control_Data);
	a=*((int32_t *)Control_Data);
	Dictionary_Data[4].producer_object =  &a;
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

/*设置通道x温度，x取值0~7*/
float b=0;
 void  CallBack_Func_channelx_temperature_set(void *Control_Data) /*Sensor0 AD_data*/
{
	 /* Prevent unused argument(s) compilation warning */
		
  //UNUSED(Control_Data);
	b=*((float *)Control_Data);
  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */}
/*设置通道x温度保护值，x取值0~7*/
__weak void  CallBack_Func_channelx_temperature_protection_set(void *Control_Data) /*Sensor0 AD_data*/
{

		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*通道xP设置，x取值0~7*/
__weak void  CallBack_Func_channel_xP_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*后开门P设置*/
__weak void  CallBack_Func_backdoor_P_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*通道xI设置，x取值0~7*/
__weak void  CallBack_Func_channel_xI_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*后开门I设置*/
__weak void  CallBack_Func_backdoor_I_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*通道xD设置，x取值0~7*/
__weak void  CallBack_Func_channel_xD_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*后开门D设置*/
__weak void  CallBack_Func_backdoor_D_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*通道x点火电流/功率大小，x取值0~2*/
__weak void  CallBack_Func_channelx_fire_current_or_power_set(void *Control_Data)/*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*通道x点火时间，x取值0~2*/
__weak void  CallBack_Func_channelx_fire_time_set(void *Control_Data)/*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*IO输出值*/
__weak void  CallBack_Func_IO_output(void *Control_Data)/*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*各通道开关设定*/
__weak void  CallBack_Func_channel_switch_set(void *Control_Data)
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*0通道工作模式设置*/
__weak void  CallBack_Func_channel0_work_mode_set(void *Control_Data)
{

		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*点火开关*/
__weak void  CallBack_Func_fire_switch(void *Control_Data)
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}




