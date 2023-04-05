#include "Dev_Ini.h"
#include "Can_Filter_Init.h"
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCANCallBack
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description:Device initialization



-------------------------------------------------------------*/
volatile int    Sem_Sn = 0;
extern char SN[7];
extern char Rx_ID[7];
extern uint8_t sensor_type;
extern  Contents_def ContentsDictionary[CONTENTS_LENGTH];
extern CAN_HandleTypeDef hcan;
extern volatile int OneConvert;

		uint16_t x=0;
void GetSTM32MCUID(char *id)
{

    id[1]=*(char*)(0x1FFFF7E8+1);
    id[2]=*(char*)(0x1FFFF7E8+2);
		id[3]=*(char*)(0x1FFFF7E8+3);
    id[4]=*(char*)(0x1FFFF7E8+4);
    id[5]=*(char*)(0x1FFFF7E8+5);
		id[6]=*(char*)(0x1FFFF7E8+6);

}

 void CallBack_Func_Sensor_SET_NodeID(void *Control_Data) /*Sensor ID*/
{
		if(*((char* )Control_Data+1)!= SN[1]||*((char* )Control_Data+2)!=SN[2]||
					*((char* )Control_Data+3)!=SN[3]||*((char* )Control_Data+4)!=SN[4]||
					*((char* )Control_Data+5)!=SN[5]||*((char* )Control_Data+6)!=SN[6])
		{
				Sem_Sn = 0;	
		}
		else 
		{
			uint8_t Sem = Rx_ID[0];
			ContentsDictionary[Sem].SegmentLength = 3;
			Set_Can_Filter1(&hcan);
			sensor_type=0xa;
			Producer_Event();
			Deliver_Event();
			Sem_Sn=1;
		}
}
void DevIni()
{
	GetSTM32MCUID(SN);
	uint8_t i =0;
	while(Sem_Sn == 0)
	{

		if(OneConvert==1)
		{	x++;
			if(x>2)
			{
					x=0;
					SN[0]=i;
					Producer_Event();
					Deliver_Event();
					i++;
					OneConvert =0;			
			
			}

		}
	Consumer_Event();

	}

}
