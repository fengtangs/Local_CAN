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
uint32_t ad7172_read(uint8_t Add,int8_t length,AD7172_ReadTypeDef ReadType)//����û�а�״̬�Ĵ���������׷�ӵ����ݼĴ��������Կ��Դ���8-24λ
{

   uint8_t  comms,Temp;
   uint32_t	result =0;
	
	 comms = Add & 0x7f;
	 comms |= COMMS_READ;//��ȡ����
	 
	 HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_RESET);  //׼�������
	 if(ReadType == AD7172_DATA)//������
	 {	
	   while (HAL_GPIO_ReadPin(AD7172_DOUT_GPIO_Port, AD7172_DOUT_Pin))//��ȡ����
		 {
			 HAL_Delay(1);
		 };
	 };	 
	
	 HAL_SPI_Transmit(&AD7172_A_HSPI,&comms,1,HAL_MAX_DELAY);
	 HAL_SPI_Receive(&AD7172_A_HSPI,&Temp,1,HAL_MAX_DELAY);//���ܵ�һ������
	 
	 result = Temp;
	 if(length >1)  
	 {	 
			 HAL_SPI_Receive(&AD7172_A_HSPI,&Temp,1,HAL_MAX_DELAY);//���ܵڶ�������
			
			 result <<=8;
			 result +=Temp;
	 };	
	
	 if(length > 2)  
	 {	 
	
			 HAL_SPI_Receive(&AD7172_A_HSPI,&Temp,1,HAL_MAX_DELAY);//���ܵ�����
			
			 result <<=8;
			 result +=Temp;
	 };
	 HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_SET);  //����ͨ��
	 return(result);

}
//**************************************************************************
void  ad7172_write(uint8_t Add,uint8_t *pData,int8_t length)//��AD���͸�������
{
	
   uint8_t  comms;
	
	 comms = Add & 0x7f;
	 
	 HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_RESET);  //�Ƚ�Ƭѡ�ź��õ͵�ƽ����ʼͨѶ

	 HAL_SPI_Transmit(&AD7172_A_HSPI,&comms,1,HAL_MAX_DELAY);//���Ͳ�������
	 HAL_SPI_Transmit(&AD7172_A_HSPI,pData,length,HAL_MAX_DELAY);//���;���ָ������
	 HAL_GPIO_WritePin(AD7172_nCS_GPIO_Port, AD7172_nCS_Pin, GPIO_PIN_SET);  	//ͨ�Ž������ָ��ߵ�ƽ
}


static void ad7172_Reset(void)//оƬ��λ
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
		Buf[1] = Filte%256;//�����˲��Ĵ������������ʣ�31250��	 86db

		ad7172_write(FILTCON0,Buf,2);//����������ã���ADд����������1 ������Ŀ��Ĵ���������2�������������ʼ��ַ������3�����ĳ���

    Buf[0] = ADCMode/256;
		Buf[1] = ADCMode%256;//�ڲ���׼��ѹԴʹ��

		ad7172_write(ADCMODE,Buf,2);
	
	  Buf[0] = SetUpCon/256;
		Buf[1] = SetUpCon%256;//����˫���Ա��룬����REF��������ʹ��AIIN���壬�ȵ����ã��Ƕ����üĴ���0�����ã�
		ad7172_write(SETUPCON0,Buf,2);//ADCģʽ�Ĵ����������
	
}


