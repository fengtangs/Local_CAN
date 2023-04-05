#include "CallBack.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANCallBack
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description:CAN user operation callback function



-------------------------------------------------------------*/
		 //�����ֵ�
extern type_Dictionary_def Dictionary_Data[DICTIONARY_LENGTH];
/****************************************************************

 Function: //������Ϣ�ص���������
 Description: // Ϊһ�ຯ�������ݽ������ݰ���ͬ�����ò�ͬ�Ļص������������Ӧ�Ĺ���
							���뽫�麯��ʵ�֣��ſ��Ե�����Ӧ�Ļص�������
 Calls: //
 Called By: //�����ߺ���
 Input: //uint16_t index�ֵ�������type_Dictionary_def *Pointer�����ֵ��ֶ�
 Output: // 
 Return: // 
 Others: //

******************************************************************/
/*���ڿ���FID�ĵ�λ��TCD���ŵ���*/
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
/*��������ID*/
__weak void CallBack_Func_Sensor_SET_NodeID(void *Control_Data) /*Sensor0 AD_data*/
{

	 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);
  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}

/*����ͨ��x�¶ȣ�xȡֵ0~7*/
float b=0;
 void  CallBack_Func_channelx_temperature_set(void *Control_Data) /*Sensor0 AD_data*/
{
	 /* Prevent unused argument(s) compilation warning */
		
  //UNUSED(Control_Data);
	b=*((float *)Control_Data);
  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */}
/*����ͨ��x�¶ȱ���ֵ��xȡֵ0~7*/
__weak void  CallBack_Func_channelx_temperature_protection_set(void *Control_Data) /*Sensor0 AD_data*/
{

		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*ͨ��xP���ã�xȡֵ0~7*/
__weak void  CallBack_Func_channel_xP_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*����P����*/
__weak void  CallBack_Func_backdoor_P_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*ͨ��xI���ã�xȡֵ0~7*/
__weak void  CallBack_Func_channel_xI_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*����I����*/
__weak void  CallBack_Func_backdoor_I_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*ͨ��xD���ã�xȡֵ0~7*/
__weak void  CallBack_Func_channel_xD_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*����D����*/
__weak void  CallBack_Func_backdoor_D_set(void *Control_Data) /*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*ͨ��x������/���ʴ�С��xȡֵ0~2*/
__weak void  CallBack_Func_channelx_fire_current_or_power_set(void *Control_Data)/*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*ͨ��x���ʱ�䣬xȡֵ0~2*/
__weak void  CallBack_Func_channelx_fire_time_set(void *Control_Data)/*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*IO���ֵ*/
__weak void  CallBack_Func_IO_output(void *Control_Data)/*Sensor0 AD_data*/
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*��ͨ�������趨*/
__weak void  CallBack_Func_channel_switch_set(void *Control_Data)
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*0ͨ������ģʽ����*/
__weak void  CallBack_Func_channel0_work_mode_set(void *Control_Data)
{

		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}
/*��𿪹�*/
__weak void  CallBack_Func_fire_switch(void *Control_Data)
{
		 /* Prevent unused argument(s) compilation warning */
  UNUSED(Control_Data);

  /* NOTE : This function should not be modified, when the callback is needed,
            the CallBack_Func_Sensor_SET_NodeID could be implemented in the user file
   */
}




