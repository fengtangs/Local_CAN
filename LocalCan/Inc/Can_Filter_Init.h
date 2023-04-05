#ifndef __CAN_FILTERINI_H
#define __CAN_FILTERINI_H
/*-------------------------------------------------------------
*Author:NSF
*File_Name:LocalCAN_Ini
*Time:2021/5/9
		*Last modified time:2021/5/14
		*Function description:CAN filter group initialization configuration

-------------------------------------------------------------*/
#include "Dictionary.h"
#include "CallBack.h"
#include "Producer.h"
#include "Consumer.h"

	/*用户根据段表设置列表标识符过滤*/
void Set_Can_Filter(FDCAN_HandleTypeDef *);
#endif /*__CAN_FILTERINI_H*/
