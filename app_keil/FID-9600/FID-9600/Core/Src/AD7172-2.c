#include "stm32f1xx_hal.h"

#include "ad7172-2.h"
#include "stdlib.h"

const uint16_t Filte    =FILTCONx_ENHFILT_86dB
	                       +FILTCONx_ORDER_SINC5_1
                         +0x0011 ;

const uint16_t SetUpCon =SETUPCONx_BI_UNIPOLAR
	                      +SETUPCONx_AINBUF_POS
                        +SETUPCONx_AINBUF_NEG
                        +SETUPCONx__REF_SEL_IN2V5;
const uint16_t ADCMode  =ADCMODE_REF_EN;


//**************************************************************************
uint32_t ad7172_read(uint8_t Add,int8_t length,AD7172_ReadTypeDef ReadType)//这里没有把状态寄存器的数据追加到数据寄存器，所以可以处理8-24位
{

   uint8_t  comms,Temp;
   uint32_t	result =0;
	
	 comms = Add & 0x7f;
	 comms |= COMMS_READ;//读取命令
	 
	 HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_RESET);  //准备命令发送
	 if(ReadType == AD7172_DATA)//读数据
	 {	
	   while (HAL_GPIO_ReadPin(AD7172_DOUT_GPIO_Port, AD7172_DOUT_Pin))//读取数据
		 {
			 HAL_Delay(1);
		 };
	 };	 
	
	 HAL_SPI_Transmit(&AD7172_A_HSPI,&comms,1,HAL_MAX_DELAY);
	 HAL_SPI_Receive(&AD7172_A_HSPI,&Temp,1,HAL_MAX_DELAY);//接受第一个数据
	 
	 result = Temp;
	 if(length >1)  
	 {	 
			 HAL_SPI_Receive(&AD7172_A_HSPI,&Temp,1,HAL_MAX_DELAY);//接受第二个数据
			
			 result <<=8;
			 result +=Temp;
	 };	
	
	 if(length > 2)  
	 {	 
	
			 HAL_SPI_Receive(&AD7172_A_HSPI,&Temp,1,HAL_MAX_DELAY);//接受第三个
			
			 result <<=8;
			 result +=Temp;
	 };
	 HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_SET);  //结束通信
	 return(result);

}
//**************************************************************************
void  ad7172_write(uint8_t Add,uint8_t *pData,int8_t length)//向AD发送各种命令
{
	
   uint8_t  comms;
	
	 comms = Add & 0x7f;
	 
	 HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_RESET);  //先将片选信号置低电平，开始通讯

	 HAL_SPI_Transmit(&AD7172_A_HSPI,&comms,1,HAL_MAX_DELAY);//发送操作命令
	 HAL_SPI_Transmit(&AD7172_A_HSPI,pData,length,HAL_MAX_DELAY);//发送具体指令内容
	 HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_SET);  	//通信结束，恢复高电平
}


static void ad7172_Reset(void)//芯片复位
{
     uint8_t Buf[] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
		 HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_RESET);  
		 HAL_SPI_Transmit(&AD7172_A_HSPI,Buf,8,HAL_MAX_DELAY);
	   HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_SET);  	

};	


//**************************************************************************	
void ad7172_ini(void)
{
	  uint8_t Buf[2];
	
		HAL_Delay(100);
	  ad7172_Reset();
	  HAL_Delay(100);
	
    Buf[0] = Filte/256;
		Buf[1] = Filte%256;//设置滤波寄存器，设置速率？31250？20ps 86db

		ad7172_write(FILTCON0,Buf,2);//这个函数作用，向AD写相关命令，参数1 操作的目标寄存器，参数2操作的命令的起始地址，参数3操作的长度

    Buf[0] = ADCMode/256;
		Buf[1] = ADCMode%256;//内部基准电压源使能

		ad7172_write(ADCMODE,Buf,2);
	
	  Buf[0] = SetUpCon/256;
		Buf[1] = SetUpCon%256;//设置双极性编码，禁用REF缓冲器，使用AIIN缓冲，等等设置，是对配置寄存器0的配置，
		ad7172_write(SETUPCON0,Buf,2);//ADC模式寄存器相关设置
	
}


