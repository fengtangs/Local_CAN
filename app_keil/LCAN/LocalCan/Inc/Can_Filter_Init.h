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
extern   Contents_def ContentsDictionary[CONTENTS_LENGTH];
	/*用户根据段表设置列表标识符过滤*/
	#if !STMF1
	void Set_Can_Filter(CAN_HandleTypeDef *);
	void Set_Can_Filter1(CAN_HandleTypeDef *);
	#else
		void Set_Can_Filter(FDCAN_HandleTypeDef *);
		void Set_Can_Filter1(FDCAN_HandleTypeDef *);
	#endif
#endif /*__CAN_FILTERINI_H*/
