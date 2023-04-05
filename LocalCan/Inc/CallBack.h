#ifndef __CALLBACK_H
#define __CALLBACK_H
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANCallBack
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description:CAN user operation callback function



-------------------------------------------------------------*/
#include "stdint.h"
#include "Dictionary.h"
/****************************************************************

 Function: //接收消息回调函数定义
 Description: // 为一类函数，根据接收数据包不同，调用不同的回调函数，完成相应的功能
 Calls: //
 Called By: //消费者函数
 Input: //uint16_t index字典索引，type_Dictionary_def *Pointer具体字典字段
 Output: // 
 Return: // 
 Others: //

******************************************************************/
/*用于控制FID的挡位或TCD的桥电流*/
 void CallBack_Func_FID_Gear_Or_TCD_Current(void *Control_Data);  
/*分配检测器ID*/
 void CallBack_Func_Sensor_SET_NodeID(void *Control_Data);   

/*设置通道x温度，x取值0~7*/
 void CallBack_Func_channelx_temperature_set(void* );   
/*设置通道x温度保护值，x取值0~7*/
 void CallBack_Func_channelx_temperature_protection_set(void* ); 
/*通道xP设置，x取值0~7*/
 void CallBack_Func_channel_xP_set(void* ); 
/*后开门P设置*/
 void CallBack_Func_backdoor_P_set(void* ); 
/*通道xI设置，x取值0~7*/
 void CallBack_Func_channel_xI_set(void* ); 
/*后开门I设置*/
 void CallBack_Func_backdoor_I_set(void* ); 
/*通道xD设置，x取值0~7*/
 void CallBack_Func_channel_xD_set(void* ); 
/*后开门D设置*/
 void CallBack_Func_backdoor_D_set(void* ); 
/*通道x点火电流/功率大小，x取值0~2*/
 void CallBack_Func_channelx_fire_current_or_power_set(void* );
/*通道x点火时间，x取值0~2*/
 void CallBack_Func_channelx_fire_time_set(void* );
/*IO输出值*/
__weak  void CallBack_Func_IO_output(void* );
/*各通道开关设定*/
 void CallBack_Func_channel_switch_set(void* );
/*0通道工作模式设置*/
 void CallBack_Func_channel0_work_mode_set(void* );
/*点火开关*/
 void CallBack_Func_fire_switch(void* );
#endif /*__CALLBACK_H*/
