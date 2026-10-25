#include "main.h"
#include "mx_gpio_default.h"
#include "mx_usart2.h"
#include <string.h>


static hal_uart_handle_t *g_uart;
static uint8_t g_rx_byte;

static void uart_send(const char *text)
{
  HAL_UART_Transmit(g_uart, text, (uint32_t)strlen(text), 1000u);
}

void HAL_UART_RxCpltCallback(hal_uart_handle_t *huart,
                             uint32_t size_byte,
                             hal_uart_rx_event_types_t rx_event)
{
  uint8_t ch = g_rx_byte;
  (void)size_byte;
  (void)rx_event;

  if (ch == '1')
  {
    HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, HAL_GPIO_PIN_SET);
    uart_send("\r\nLED ON\r\n");
  }
  else if (ch == '0')
  {
    HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, HAL_GPIO_PIN_RESET);
    uart_send("\r\nLED OFF\r\n");
  }
  else if (ch == '?')
  {
    uart_send("\r\n1=LED ON, 0=LED OFF, ?=help\r\n");
  }
  else if ((ch >= 32u) && (ch <= 126u))
  {
    HAL_UART_Transmit(huart, &ch, 1u, 100u);
  }

  HAL_UART_Receive_IT(huart, &g_rx_byte, 1u);
}


int main(void)
{
  if (mx_system_init() != SYSTEM_OK)
  {
    return (-1);
  }

  g_uart = mx_usart2_uart_gethandle();
  if (g_uart == NULL)
  {
    return (-1);
  }

  HAL_UART_Receive_IT(g_uart, &g_rx_byte, 1u);

  uart_send("\r\nNUCLEO-C542RC UART Lab\r\n");
  uart_send("USART2: PA2=TX, PA3=RX, 115200 8N1\r\n");
  uart_send("Send 1: LED ON, 0: LED OFF, ?: help\r\n");

  while (1)
  {
    HAL_Delay(100u);
  }
} 

