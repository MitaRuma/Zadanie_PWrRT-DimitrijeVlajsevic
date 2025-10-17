#include "main.h"
#include "iwdg.h"
#include "system_stm32f2xx.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void){

  //inicjalizacja wszystkich potrzebych rzeczy
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_IWDG_Init();

  while (1)
  {
	  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); //wlacza sie PN5 (tam gdzie dioda podlaczona)
	  HAL_Delay(100); //czekaj 100 ms [bo jak sie zmienia stan co 100ms to cykl mrugniecia = 200ms => 5Hz]
	  HAL_IWDG_Refresh(&hiwdg); //watchdoga ogarnij
  }
}

//ustawienia pinu PA5?
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

//to chyba ma zatrzymac program/funkcje jak cos pojdzie nie tak
void Error_Handler(void)
{
  __disable_irq();
  while (1){}
}
