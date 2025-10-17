#ifndef __SYSTEM_STM32F2XX_H
#define __SYSTEM_STM32F2XX_H

#include "stm32f2xx.h"

extern uint32_t SystemCoreClock;
extern const uint8_t AHBPrescTable[16];

void SystemInit(void);
void SystemClock_Config(void);
void SystemCoreClockUpdate(void);

#endif
