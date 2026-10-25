#include "main.h"
#include "mx_gpio_default.h"

static void led_blink(uint32_t times)
{
  for (uint32_t i = 0u; i < times; i++)
  {
    HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, HAL_GPIO_PIN_SET);
    HAL_Delay(100u);
    HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, HAL_GPIO_PIN_RESET);
    HAL_Delay(100u);
  }
}

void HAL_EXTI_TriggerCallback(hal_exti_handle_t *hexti, hal_exti_trigger_t trigger)
{
  (void)hexti;
  (void)trigger;
}

int main(void)
{
  if (mx_system_init() != SYSTEM_OK)
  {
    return (-1);
  }

  hal_exti_handle_t *hexti = mx_gpio_default_exti13_gethandle();
  if (hexti == NULL)
  {
    return (-1);
  }

  HAL_EXTI_Enable(hexti, HAL_EXTI_MODE_INTERRUPT);

  while (1)
  {
    led_blink(3u);

    HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, HAL_GPIO_PIN_RESET);
    HAL_EXTI_ClearPending(hexti, HAL_EXTI_TRIGGER_RISING);

    HAL_SuspendTick();
    HAL_PWR_EnterSleepMode(HAL_PWR_LOW_PWR_MODE_WFI);
    HAL_ResumeTick();

    HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, HAL_GPIO_PIN_SET);
    HAL_Delay(500u);
    HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, HAL_GPIO_PIN_RESET);
    HAL_Delay(200u);
  }
} 

