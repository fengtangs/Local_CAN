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

 Function: //������Ϣ�ص���������
 Description: // Ϊһ�ຯ�������ݽ������ݰ���ͬ�����ò�ͬ�Ļص������������Ӧ�Ĺ���
 Calls: //
 Called By: //�����ߺ���
 Input: //uint16_t index�ֵ�������type_Dictionary_def *Pointer�����ֵ��ֶ�
 Output: // 
 Return: // 
 Others: //

******************************************************************/
/*���ڿ���FID�ĵ�λ��TCD���ŵ���*/
 void CallBack_Func_FID_Gear_Or_TCD_Current(void *Control_Data);  
/*��������ID*/
 void CallBack_Func_Sensor_SET_NodeID(void *Control_Data);   

/*����ͨ��x�¶ȣ�xȡֵ0~7*/
 void CallBack_Func_channelx_temperature_set(void* );   
/*����ͨ��x�¶ȱ���ֵ��xȡֵ0~7*/
 void CallBack_Func_channelx_temperature_protection_set(void* ); 
/*ͨ��xP���ã�xȡֵ0~7*/
 void CallBack_Func_channel_xP_set(void* ); 
/*����P����*/
 void CallBack_Func_backdoor_P_set(void* ); 
/*ͨ��xI���ã�xȡֵ0~7*/
 void CallBack_Func_channel_xI_set(void* ); 
/*����I����*/
 void CallBack_Func_backdoor_I_set(void* ); 
/*ͨ��xD���ã�xȡֵ0~7*/
 void CallBack_Func_channel_xD_set(void* ); 
/*����D����*/
 void CallBack_Func_backdoor_D_set(void* ); 
/*ͨ��x������/���ʴ�С��xȡֵ0~2*/
 void CallBack_Func_channelx_fire_current_or_power_set(void* );
/*ͨ��x���ʱ�䣬xȡֵ0~2*/
 void CallBack_Func_channelx_fire_time_set(void* );
/*IO���ֵ*/
__weak  void CallBack_Func_IO_output(void* );
/*��ͨ�������趨*/
 void CallBack_Func_channel_switch_set(void* );
/*0ͨ������ģʽ����*/
 void CallBack_Func_channel0_work_mode_set(void* );
/*��𿪹�*/
 void CallBack_Func_fire_switch(void* );
#endif /*__CALLBACK_H*/
