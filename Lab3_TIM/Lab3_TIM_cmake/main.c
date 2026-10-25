#include "main.h"
#include "mx_gpio_default.h"
#include "mx_tim6.h"

void HAL_TIM_UpdateCallback(hal_tim_handle_t *htim)
{
  (void)htim;

  /* Each TIM6 update event toggles the on-board LED LD1. */
  HAL_GPIO_TogglePin(LD1_PORT, LD1_PIN);
}

int main(void)
{
  if (mx_system_init() != SYSTEM_OK)
  {
    return (-1);
  }

  hal_tim_handle_t *htim6 = mx_tim6_gethandle();
  if (htim6 == NULL)
  {
    return (-1);
  }

  /* 144 MHz / (14399 + 1) = 10 kHz, then 5000 counts = 500 ms. */
  HAL_TIM_SetPrescaler(htim6, 14399u);
  HAL_TIM_SetPeriod(htim6, 4999u);

  if (HAL_TIM_Start_IT(htim6) != HAL_OK)
  {
    return (-1);
  }

  while (1)
  {
    HAL_Delay(100u);
  }
}

