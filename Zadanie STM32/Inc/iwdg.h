#ifndef __IWDG_H
#define __IWDG_H

#include "stm32f2xx_hal.h"

//costam watchdog
extern IWDG_HandleTypeDef hiwdg;
void MX_IWDG_Init(void);

#endif
