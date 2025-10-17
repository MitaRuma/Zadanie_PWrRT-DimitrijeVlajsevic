#include "iwdg.h"

IWDG_HandleTypeDef hiwdg;

//inicjalizacja watchdoga, ustawienia
void MX_IWDG_Init(void)
{
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
    hiwdg.Init.Reload = 1024;
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
    {
        Error_Handler(); //wyjdz jesli sie zepsuje
    }
}
