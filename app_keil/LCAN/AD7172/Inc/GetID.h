#ifndef ___GET_ID_H
#define __GET_ID_H
#include "stdint.h"
/*??STM32 MCU*/
typedef enum {
  STM32F_0 = 0,
  STM32F_1 ,
  STM32F_2,
  STM32F_3,
  STM32F_4,
  STM32F_7,
  STM32L_0,
  STM32L_1,
  STM32L_4,
  STM32H_7,
}MCUTypedef;

uint32_t idAddr[]={0x1FFFF7AC,  /*STM32F0œµ¡–SN–Ú¡–∫≈*/
                0x1FFFF7E8,  /*STM32F1*/
                0x1FFF7A10,  /*STM32F2*/
                0x1FFFF7AC,  /*STM32F3*/
                0x1FFF7A10,  /*STM32F4*/
                0x1FF0F420,  /*STM32F7*/
                0x1FF80050,  /*STM32L0*/
                0x1FF80050,  /*STM32L1*/
                0x1FFF7590,  /*STM32L4*/
                0x1FF0F420}; /*STM32H7*/

/*MCU ID*/
void GetSTM32MCUID(char *id,MCUTypedef type);  

#endif /* __GET_ID_H */

								