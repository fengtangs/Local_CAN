#ifndef __AD7172_2_H
#define __AD7172_2_H

#include "stm32f1xx_hal.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;

#define AD7172_nCS_GPIO_Port AD_nCS_GPIO_Port 
#define AD7172_nCS_Pin       AD_nCS_Pin 
#define AD7172_DOUT_GPIO_Port AD_DOUT_GPIO_Port
#define AD7172_DOUT_Pin AD_DOUT_Pin




#define COMMS												0x00  //ͨ�żĴ���
#define COMMS_WEN_DIS   						0x80 	//Ҫ��ADC��ʼͨ�ţ���λ����Ϊ�͵�ƽ
#define COMMS_READ      						0x40	//��λ���������Ƕ���������д����,0:д����,1:������

#define STATUS											0x00	//״̬�Ĵ���
#define STATUS_RDY_DIS  						0x80  //0:�����ݽ������,1:�ȴ������ݽ��
#define STATUS_ADC_ERROR	  	 	  	0x40	//��λĬ��ָʾ�Ƿ���ADC�����̻�Ƿ�����¼�
#define STATUS_CRC_ERROR						0x20	//��λָʾ�Ĵ���д�����ڼ��Ƿ���CRC����
#define STATUS_REG_ERROR						0x10	//��λָʾһ���ڲ��Ĵ����������Ƿ����仯
#define STATUS_CHANNEL0							0x00  //��Щλָʾ���ݼĴ����е�ǰ�洢�Ľ������Ӧ��ADCת��ͨ��
#define STATUS_CHANNEL1							0x01
#define STATUS_CHANNEL2							0x02
#define STATUS_CHANNEL3							0x03

#define ADCMODE											0x01		//ADCģʽ�Ĵ���
#define ADCMODE_REF_EN							0x8000	//��λʹ���ڲ���׼��ѹԴ�����2.5 V�����ѹ��REFOUT���š�
#define ADCMODE_HIDE_DELAY					0x4000	//����ʹ��sinc5 + sinc1�˲�����ѡ���������ʣ����������DELAYλ�����˿ɱ���ӳ٣���λ�����ӳ����յ�ת��ʱ���У��Ӷ������ӳ١�
#define ADCMODE_SING_CYC						0x2000	//������ͨ����Чʱ������ʹ�ô�λ������ADC���Խ������˲����������������
#define ADCMODE_DELAY0							0x0000	//��Щλ����ͨ���л�������һ���ɱ�̵��ӳ�ʱ�䣬�Ա��ⲿ��·����ADC��ʼ����������ǰ�ȶ�������
#define ADCMODE_DELAY1							0x0100
#define ADCMODE_DELAY2							0x0200
#define ADCMODE_DELAY3							0x0300
#define ADCMODE_DELAY4							0x0400
#define ADCMODE_DELAY5							0x0500
#define ADCMODE_DELAY6							0x0600
#define ADCMODE_DELAY7							0x0700
#define ADCMODE_MODE_CONTINU  			0x0000	//����ת��ģʽ(Ĭ�ϣ�     
#define ADCMODE_MODE_SINGLE   			0x0010	//����ת��ģʽ
#define ADCMODE_MODE_WAIT     			0x0020	//����ģʽ
#define ADCMODE_MODE_SHUT     			0x0030	//�ض�ģʽ
#define ADCMODE_MODE_IN_CALI  			0x0040	//�ڲ�ʧ��У׼
#define ADCMODE_MODE_SYS_CALI 			0x0060	//ϵͳʧ��У׼
#define ADCMODE_MODE_SYS_GAIN 			0x0070	//ϵͳ����У׼
#define ADCMODE_CLOCKSEL_IN_OSC			0x0000	//�ڲ�����(Ĭ�ϣ�     
#define ADCMODE_CLOCKSEL_CLKIO_OUT  0x0004	//XTAL2/CLKIO�����ϵ��ڲ��������
#define ADCMODE_CLOCKSEL_CLKIO_IN   0x0008	//XTAL2/CLKIO�����ϵ��ⲿʱ������
#define ADCMODE_CLOCKSEL_OUT_OSC    0x000c  //XTAL1��XTAL2/CLKIO�����ϵ��ⲿ����

#define IFMODE											0x02		//�ӿ�ģʽ�Ĵ���
#define IFMODE_ALT_SYNC_EN          0x1000	//��λʹ��SYNC/ERROR���ŵĲ�ͬ��Ϊ���Ա�����SYNC/ERROR������ѭ��ͨ����ת��
#define IFMODE_IOSTRENGTH_EN        0x0800	//��λ����DOUT/RDY���ŵ�����ǿ�ȡ���IOVDD��Դ�ϵ��ҵ����еȵ�����¸��ٶ�ȡ���нӿ�ʱ��Ӧ����λ��1��
#define IFMODE_DOUT_RESET_EN        0x0100
#define IFMODE_CONTREAD_EN          0x0080	//��λʹ��������ȡADC���ݼĴ�����Ҫʹ��������ȡ�� ADC��������Ϊ����ת��ģʽ
#define IFMODE_DATA_STAT_EN         0x0040	//��λʹ״̬�Ĵ��������ڶ�ȡʱ���ӵ����ݼĴ����ϣ�ʹ��ͨ����״̬��Ϣ������һͬ���䡣����ȷ����״̬�Ĵ���������ͨ��λ�����ݼĴ����е����ݶ�Ӧ��Ψһ��ʽ��
#define IFMODE_REG_CHECK_EN    			0x0020	//��λʹ�ܼĴ��������Լ�飬���ô˼��ɼ����û��Ĵ���ֵ���κα仯��
#define IFMODE_CRC_EN_DIS           0x0000	//����
#define IFMODE_CRC_EN_XOR_CRC       0x0004	//�Ĵ���������ʹ��XORУ��ͣ��Ĵ���д������Ȼʹ��CRC��
#define IFMODE_CRC_EN_CRC           0x0008	//����д�����ʹ��CRCУ���
#define IFMODE_WL16									0x0001  //��λ��ADC���ݼĴ�����Ϊ16λ��д��ӿ�ģʽ�Ĵ������ḴλADC����ˣ�д���λ�� ADC��������������뵽��ȷ���ֳ�����һ���µ�ADC�������ȷ�ġ�               

#define REGCHECK 										0x03		//�Ĵ������
#define DATA    										0x04		//���ݼĴ���

#define GPIOCON											0x06		//GPIO���üĴ���
#define GPIOCON_MUX_IO							0x1000  //��λ����ADC�����ⲿ��·�����������ڲ�ͨ��˳��ͬ��ʹ��GPIO0/GPIO1������һ��ͨ����ģ�����������Կɰ�ͨ������ѡ��
#define GPIOCON_SYNC_EN             0x0800	//��λ��ʹSYNC/ERROR��������ͬ������
#define GPIOCON_ERR_EN_DIS  				0x0000
#define GPIOCON_ERR_EN_ERROR_IN     0x0200	//SYNC/ERROR�Ǵ������롣
#define GPIOCON_ERR_EN_ERROR_OUT    0x0400	//SYNC/ERROR�ǿ�©�������
#define GPIOCON_ERR_EN_GPIO         0x0600	//SYNC/ERROR��ͨ�������
#define GPIOCON_ERR_DAT							0x0100  //SYNC/ERROR��������ͨ�����ʱ����λ�������߼���ƽ����������������ʱ����λ��ӳ��ض�״̬��
#define GPIOCON_IP_EN1							0x0020	//��λ��GPIO1��Ϊ���롣
#define GPIOCON_IP_EN0							0x0010  //��λ��GPIO0��Ϊ���롣
#define GPIOCON_OP_EN1							0x0008  //��λ��GPIO1��Ϊ�����
#define GPIOCON_OP_EN0							0x0004	//��λ��GPIO0��Ϊ�����
#define GPIOCON_GP_DATA1            0x0002  //��λ��GPIO1�Ļض���д�����ݡ�
#define GPIOCON_GP_DATA0						0x0001	//��λ��GPIO0�Ļض���д�����ݡ�

#define ID			    								0x07		//ID�Ĵ���

#define CH0													0x10		//ͨ���Ĵ���
#define CH1													0x11
#define CH2													0x12			
#define CH3													0x13
#define CHx_CH_EN 									0x8000 //��λʹ��ͨ����
#define CHx_SETUP_SEL0							0x0000
#define CHx_SETUP_SEL1							0x1000
#define CHx_SETUP_SEL2							0x2000
#define CHx_SETUP_SEL3							0x3000

#define CHx_AINPOS_AIN0							0x0000		//AIN0(Ĭ��)
#define CHx_AINPOS_AIN1							0x0020
#define CHx_AINPOS_AIN2							0x0040
#define CHx_AINPOS_AIN3							0x0060
#define CHx_AINPOS_AIN4							0x0080
#define CHx_AINPOS_TEMP_POS					0x0220	//�¶ȴ�����+
#define CHx_AINPOS_TEMP_NEG					0x0240	//�¶ȴ�����-
#define CHx_AINPOS_POWER_DIV5_POS		0x0260	//((AVDD1 - AVSS)/5)+(����ʹ��ģ�����뻺����)
#define CHx_AINPOS_POWER_DIV5_NEG		0x0280	//((AVDD1 - AVSS)/5)?(����ʹ��ģ�����뻺����)
#define CHx_AINPOS_REF_POS					0x02a0	//REF+
#define CHx_AINPOS_REF_NEG					0x02c0	//REF-

#define CHx_AINNEG_AIN0							0x0000		//AIN0
#define CHx_AINNEG_AIN1							0x0020		//(Ĭ��)
#define CHx_AINNEG_AIN2							0x0040
#define CHx_AINNEG_AIN3							0x0060
#define CHx_AINNEG_AIN4							0x0080
#define CHx_AINNEG_TEMP_POS					0x0220	//�¶ȴ�����+
#define CHx_AINNEG_TEMP_NEG					0x0240	//�¶ȴ�����-
#define CHx_AINNEG_POWER_DIV5_POS		0x0260	//((AVDD1 - AVSS)/5)+(����ʹ��ģ�����뻺����)
#define CHx_AINNEG_POWER_DIV5_NEG		0x0280	//((AVDD1 - AVSS)/5)?(����ʹ��ģ�����뻺����)
#define CHx_AINNEG_REF_POS					0x02a0	//REF+
#define CHx_AINNEG_REF_NEG					0x02c0	//REF-

#define SETUPCON0										0x20	//�������üĴ���
#define SETUPCON1										0x21
#define SETUPCON2										0x22
#define SETUPCON3										0x23

#define SETUPCONx_BI_UNIPOLAR       0x1000 //0:�����Ա������,1:˫���Ա���ģʽ(ƫ�ƶ�����)
#define SETUPCONx_REFBUF_POS				0x0800 //0 ����REF+������ 1 ʹ��REF+������
#define SETUPCONx_REFBUF_NEG        0x0400 //0 ����REF-������ 1 ʹ��REF-������
#define SETUPCONx_AINBUF_POS        0x0200 //0 ����AIN+������,1 ʹ��AIN+������
#define SETUPCONx_AINBUF_NEG        0x0100 //0 ����AIN-������,1 ʹ��AIN-������
#define SETUPCONx_BURNOUT_EN        0x0080 //��λ����ѡ��ģ��������ʹ��10 ��AԴ����������ѡ��ģ��������ʹ��10 ��A��������
#define SETUPCONx_REF_SEL_EXT       0x0000 //�ⲿ��׼��ѹԴ��
#define SETUPCONx__REF_SEL_IN2V5    0x0020 //2.5 V�ڲ���׼��ѹԴ�� ADCģʽ�Ĵ���Ҳ����ʹ��REF_ENλ�� 
#define SETUPCONx__REF_SEL_POWER_   0x0030 //AVDD1 - AVSS��


#define FILTCON0										0x28	//�˲������üĴ���0
#define FILTCON1										0x29	//�˲������üĴ���1
#define FILTCON2										0x2a	//�˲������üĴ���2
#define FILTCON3										0x2b	//�˲������üĴ���3

#define FILTCONx_SINC3_MAP					0x8000 //�����λ��1���˲����Ĵ�����ӳ�佫��Ϊֱ�Ӷ�����0��Sinc3�˲����ĳ�ȡ�ʽ��б�̡���������ѡ�����Ч����������£����Զ�����������ʺ��˲����ݲ����о��ܵ������Ա������ض�Ƶ�ʡ����ڵ���ͨ�����������ʵ���fMOD/(32 �� FILTCON0[14:0])��
#define FILTCONx_ENHFILTEN					0x0800 //��λʹ������0�ĸ��ֺ����˲��������ṩ��ǿ��50 Hz��60 Hz�������ܡ�Ϊ�ˣ� ORDER0λ��������Ϊ00��ѡ��Sinc5 + Sinc1�˲�����
#define FILTCONx_ENHFILT_47dB				0x0200 //��Щλѡ������0�ĸ��ֺ����˲��������ṩ��ǿ��50 Hz��60 Hz�������ܡ�
#define FILTCONx_ENHFILT_62dB				0x0300
#define FILTCONx_ENHFILT_86dB				0x0500
#define FILTCONx_ENHFILT_92dB				0x0600
#define FILTCONx_ORDER_SINC5_1      0x0000  //��Щλ��������0�������˲���
#define FILTCONx_ORDER_SINC3        0x0060


#define OFFSET0										  0x30	//ʧ���Ĵ���0
#define OFFSET1										  0x31	//ʧ���Ĵ���1
#define OFFSET2										  0x32	//ʧ���Ĵ���2
#define OFFSET3										  0x33	//ʧ���Ĵ���3

#define GAIN0											  0x38	//����Ĵ���0
#define GAIN1											  0x39	//����Ĵ���1
#define GAIN2											  0x3a	//����Ĵ���2
#define GAIN3											  0x3b	//����Ĵ���3

#define AD7172_A_HSPI  hspi1


typedef enum 
{
  AD7172_REG     = 0x00,
  AD7172_DATA    = 0x01,
} AD7172_ReadTypeDef;





uint32_t ad7172_read(uint8_t Add,int8_t length,AD7172_ReadTypeDef ReadType);

void     ad7172_write(uint8_t Add,uint8_t *pData,int8_t length);

void    ad7172_ini(void);



#endif /* __AD7172_2_H */
