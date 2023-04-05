#ifndef __AD7172_2_H
#define __AD7172_2_H

#include "stm32f1xx_hal.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;

#define AD7172_nCS_GPIO_Port AD_nCS_GPIO_Port 
#define AD7172_nCS_Pin       AD_nCS_Pin 
#define AD7172_DOUT_GPIO_Port AD_DOUT_GPIO_Port
#define AD7172_DOUT_Pin AD_DOUT_Pin




#define COMMS												0x00  //通信寄存器
#define COMMS_WEN_DIS   						0x80 	//要与ADC开始通信，此位必须为低电平
#define COMMS_READ      						0x40	//此位决定命令是读操作还是写操作,0:写命令,1:读命令

#define STATUS											0x00	//状态寄存器
#define STATUS_RDY_DIS  						0x80  //0:新数据结果可用,1:等待新数据结果
#define STATUS_ADC_ERROR	  	 	  	0x40	//此位默认指示是否发生ADC超量程或欠量程事件
#define STATUS_CRC_ERROR						0x20	//此位指示寄存器写操作期间是否发生CRC错误
#define STATUS_REG_ERROR						0x10	//此位指示一个内部寄存器的内容是否发生变化
#define STATUS_CHANNEL0							0x00  //这些位指示数据寄存器中当前存储的结果所对应的ADC转换通道
#define STATUS_CHANNEL1							0x01
#define STATUS_CHANNEL2							0x02
#define STATUS_CHANNEL3							0x03

#define ADCMODE											0x01		//ADC模式寄存器
#define ADCMODE_REF_EN							0x8000	//此位使能内部基准电压源并输出2.5 V缓冲电压到REFOUT引脚。
#define ADCMODE_HIDE_DELAY					0x4000	//对于使用sinc5 + sinc1滤波器的选定数据速率，如果已利用DELAY位设置了可编程延迟，此位允许将延迟吸收到转换时间中，从而隐藏延迟。
#define ADCMODE_SING_CYC						0x2000	//仅单个通道有效时，可以使用此位来设置ADC仅以建立的滤波器数据速率输出。
#define ADCMODE_DELAY0							0x0000	//这些位允许通道切换后增加一个可编程的延迟时间，以便外部电路能在ADC开始处理其输入前稳定下来。
#define ADCMODE_DELAY1							0x0100
#define ADCMODE_DELAY2							0x0200
#define ADCMODE_DELAY3							0x0300
#define ADCMODE_DELAY4							0x0400
#define ADCMODE_DELAY5							0x0500
#define ADCMODE_DELAY6							0x0600
#define ADCMODE_DELAY7							0x0700
#define ADCMODE_MODE_CONTINU  			0x0000	//连续转换模式(默认）     
#define ADCMODE_MODE_SINGLE   			0x0010	//单次转换模式
#define ADCMODE_MODE_WAIT     			0x0020	//待机模式
#define ADCMODE_MODE_SHUT     			0x0030	//关断模式
#define ADCMODE_MODE_IN_CALI  			0x0040	//内部失调校准
#define ADCMODE_MODE_SYS_CALI 			0x0060	//系统失调校准
#define ADCMODE_MODE_SYS_GAIN 			0x0070	//系统增益校准
#define ADCMODE_CLOCKSEL_IN_OSC			0x0000	//内部振荡器(默认）     
#define ADCMODE_CLOCKSEL_CLKIO_OUT  0x0004	//XTAL2/CLKIO引脚上的内部振荡器输出
#define ADCMODE_CLOCKSEL_CLKIO_IN   0x0008	//XTAL2/CLKIO引脚上的外部时钟输入
#define ADCMODE_CLOCKSEL_OUT_OSC    0x000c  //XTAL1和XTAL2/CLKIO引脚上的外部晶振

#define IFMODE											0x02		//接口模式寄存器
#define IFMODE_ALT_SYNC_EN          0x1000	//此位使能SYNC/ERROR引脚的不同行为，以便利用SYNC/ERROR来控制循环通道的转换
#define IFMODE_IOSTRENGTH_EN        0x0800	//此位控制DOUT/RDY引脚的驱动强度。在IOVDD电源较低且电容中等的情况下高速读取串行接口时，应将此位置1。
#define IFMODE_DOUT_RESET_EN        0x0100
#define IFMODE_CONTREAD_EN          0x0080	//此位使能连续读取ADC数据寄存器。要使用连续读取， ADC必须配置为连续转换模式
#define IFMODE_DATA_STAT_EN         0x0040	//此位使状态寄存器可以在读取时附加到数据寄存器上，使得通道和状态信息与数据一同传输。这是确保从状态寄存器读出的通道位与数据寄存器中的数据对应的唯一方式。
#define IFMODE_REG_CHECK_EN    			0x0020	//此位使能寄存器完整性检查，利用此检查可监视用户寄存器值的任何变化。
#define IFMODE_CRC_EN_DIS           0x0000	//禁用
#define IFMODE_CRC_EN_XOR_CRC       0x0004	//寄存器读处理使能XOR校验和；寄存器写处理仍然使用CRC。
#define IFMODE_CRC_EN_CRC           0x0008	//读和写处理均使能CRC校验和
#define IFMODE_WL16									0x0001  //此位将ADC数据寄存器变为16位。写入接口模式寄存器不会复位ADC；因此，写入此位后， ADC结果不会立即舍入到正确的字长。第一个新的ADC结果是正确的。               

#define REGCHECK 										0x03		//寄存器检查
#define DATA    										0x04		//数据寄存器

#define GPIOCON											0x06		//GPIO配置寄存器
#define GPIOCON_MUX_IO							0x1000  //此位允许ADC控制外部多路复用器，与内部通道顺序同步使用GPIO0/GPIO1。用于一个通道的模拟输入引脚仍可按通道进行选择
#define GPIOCON_SYNC_EN             0x0800	//此位可使SYNC/ERROR引脚用作同步输入
#define GPIOCON_ERR_EN_DIS  				0x0000
#define GPIOCON_ERR_EN_ERROR_IN     0x0200	//SYNC/ERROR是错误输入。
#define GPIOCON_ERR_EN_ERROR_OUT    0x0400	//SYNC/ERROR是开漏错误输出
#define GPIOCON_ERR_EN_GPIO         0x0600	//SYNC/ERROR是通用输出。
#define GPIOCON_ERR_DAT							0x0100  //SYNC/ERROR引脚用作通用输出时，此位决定其逻辑电平。该引脚用作输入时，此位反映其回读状态。
#define GPIOCON_IP_EN1							0x0020	//此位将GPIO1变为输入。
#define GPIOCON_IP_EN0							0x0010  //此位将GPIO0变为输入。
#define GPIOCON_OP_EN1							0x0008  //此位将GPIO1变为输出。
#define GPIOCON_OP_EN0							0x0004	//此位将GPIO0变为输出。
#define GPIOCON_GP_DATA1            0x0002  //此位是GPIO1的回读或写入数据。
#define GPIOCON_GP_DATA0						0x0001	//此位是GPIO0的回读或写入数据。

#define ID			    								0x07		//ID寄存器

#define CH0													0x10		//通道寄存器
#define CH1													0x11
#define CH2													0x12			
#define CH3													0x13
#define CHx_CH_EN 									0x8000 //此位使能通道。
#define CHx_SETUP_SEL0							0x0000
#define CHx_SETUP_SEL1							0x1000
#define CHx_SETUP_SEL2							0x2000
#define CHx_SETUP_SEL3							0x3000

#define CHx_AINPOS_AIN0							0x0000		//AIN0(默认)
#define CHx_AINPOS_AIN1							0x0020
#define CHx_AINPOS_AIN2							0x0040
#define CHx_AINPOS_AIN3							0x0060
#define CHx_AINPOS_AIN4							0x0080
#define CHx_AINPOS_TEMP_POS					0x0220	//温度传感器+
#define CHx_AINPOS_TEMP_NEG					0x0240	//温度传感器-
#define CHx_AINPOS_POWER_DIV5_POS		0x0260	//((AVDD1 - AVSS)/5)+(必须使能模拟输入缓冲器)
#define CHx_AINPOS_POWER_DIV5_NEG		0x0280	//((AVDD1 - AVSS)/5)?(必须使能模拟输入缓冲器)
#define CHx_AINPOS_REF_POS					0x02a0	//REF+
#define CHx_AINPOS_REF_NEG					0x02c0	//REF-

#define CHx_AINNEG_AIN0							0x0000		//AIN0
#define CHx_AINNEG_AIN1							0x0020		//(默认)
#define CHx_AINNEG_AIN2							0x0040
#define CHx_AINNEG_AIN3							0x0060
#define CHx_AINNEG_AIN4							0x0080
#define CHx_AINNEG_TEMP_POS					0x0220	//温度传感器+
#define CHx_AINNEG_TEMP_NEG					0x0240	//温度传感器-
#define CHx_AINNEG_POWER_DIV5_POS		0x0260	//((AVDD1 - AVSS)/5)+(必须使能模拟输入缓冲器)
#define CHx_AINNEG_POWER_DIV5_NEG		0x0280	//((AVDD1 - AVSS)/5)?(必须使能模拟输入缓冲器)
#define CHx_AINNEG_REF_POS					0x02a0	//REF+
#define CHx_AINNEG_REF_NEG					0x02c0	//REF-

#define SETUPCON0										0x20	//设置配置寄存器
#define SETUPCON1										0x21
#define SETUPCON2										0x22
#define SETUPCON3										0x23

#define SETUPCONx_BI_UNIPOLAR       0x1000 //0:单极性编码输出,1:双极性编码模式(偏移二进制)
#define SETUPCONx_REFBUF_POS				0x0800 //0 禁用REF+缓冲器 1 使能REF+缓冲器
#define SETUPCONx_REFBUF_NEG        0x0400 //0 禁用REF-缓冲器 1 使能REF-缓冲器
#define SETUPCONx_AINBUF_POS        0x0200 //0 禁用AIN+缓冲器,1 使能AIN+缓冲器
#define SETUPCONx_AINBUF_NEG        0x0100 //0 禁用AIN-缓冲器,1 使能AIN-缓冲器
#define SETUPCONx_BURNOUT_EN        0x0080 //此位在所选正模拟输入上使能10 μA源电流，在所选负模拟输入上使能10 μA吸电流。
#define SETUPCONx_REF_SEL_EXT       0x0000 //外部基准电压源。
#define SETUPCONx__REF_SEL_IN2V5    0x0020 //2.5 V内部基准电压源。 ADC模式寄存器也必须使能REF_EN位。 
#define SETUPCONx__REF_SEL_POWER_   0x0030 //AVDD1 - AVSS。


#define FILTCON0										0x28	//滤波器配置寄存器0
#define FILTCON1										0x29	//滤波器配置寄存器1
#define FILTCON2										0x2a	//滤波器配置寄存器2
#define FILTCON3										0x2b	//滤波器配置寄存器3

#define FILTCONx_SINC3_MAP					0x8000 //如果此位置1，滤波器寄存器的映射将变为直接对设置0的Sinc3滤波器的抽取率进行编程。所有其他选项均无效。这种情况下，可以对输出数据速率和滤波器陷波进行精密调整，以便抑制特定频率。对于单个通道，数据速率等于fMOD/(32 × FILTCON0[14:0])。
#define FILTCONx_ENHFILTEN					0x0800 //此位使能设置0的各种后置滤波器，以提供增强的50 Hz和60 Hz抑制性能。为此， ORDER0位必须设置为00以选择Sinc5 + Sinc1滤波器。
#define FILTCONx_ENHFILT_47dB				0x0200 //这些位选择设置0的各种后置滤波器，以提供增强的50 Hz和60 Hz抑制性能。
#define FILTCONx_ENHFILT_62dB				0x0300
#define FILTCONx_ENHFILT_86dB				0x0500
#define FILTCONx_ENHFILT_92dB				0x0600
#define FILTCONx_ORDER_SINC5_1      0x0000  //这些位控制设置0的数字滤波器
#define FILTCONx_ORDER_SINC3        0x0060


#define OFFSET0										  0x30	//失调寄存器0
#define OFFSET1										  0x31	//失调寄存器1
#define OFFSET2										  0x32	//失调寄存器2
#define OFFSET3										  0x33	//失调寄存器3

#define GAIN0											  0x38	//增益寄存器0
#define GAIN1											  0x39	//增益寄存器1
#define GAIN2											  0x3a	//增益寄存器2
#define GAIN3											  0x3b	//增益寄存器3

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
