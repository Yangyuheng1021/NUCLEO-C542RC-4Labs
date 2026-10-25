#include "main.h"
#include "mx_gpio_default.h"

#define BLINK_PERIOD_MS 500u
#define DEBOUNCE_MS     20u

int main(void)
{
  if (mx_system_init() != SYSTEM_OK)
  {
    return (-1);
  }

  uint8_t blink_enabled = 1;
  uint8_t button_was_pressed = 0;
  uint32_t last_blink_tick = HAL_GetTick();

  while (1)
  {
    uint8_t button_pressed = (HAL_GPIO_ReadPin(B1_PORT, B1_PIN) == HAL_GPIO_PIN_SET);

    /* Detect a new press (rising edge) and debounce it. */
    if (button_pressed && !button_was_pressed)
    {
      HAL_Delay(DEBOUNCE_MS);

      if (HAL_GPIO_ReadPin(B1_PORT, B1_PIN) == HAL_GPIO_PIN_SET)
      {
        blink_enabled = !blink_enabled;

        if (blink_enabled)
        {
          HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, HAL_GPIO_PIN_SET);
        }
        else
        {
          HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, HAL_GPIO_PIN_RESET);
        }

        last_blink_tick = HAL_GetTick();
      }
    }

    button_was_pressed = button_pressed;

    if (blink_enabled && ((HAL_GetTick() - last_blink_tick) >= BLINK_PERIOD_MS))
    {
      HAL_GPIO_TogglePin(LD1_PORT, LD1_PIN);
      last_blink_tick += BLINK_PERIOD_MS;

      /* Resynchronize if the loop was delayed. */
      if ((HAL_GetTick() - last_blink_tick) >= BLINK_PERIOD_MS)
      {
        last_blink_tick = HAL_GetTick();
      }
    }
  }
}

