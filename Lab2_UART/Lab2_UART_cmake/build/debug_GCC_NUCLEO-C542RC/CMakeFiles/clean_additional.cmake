# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "debug_GCC_NUCLEO-C542RC")
  file(REMOVE_RECURSE
  "Lab2_UART.elf"
  "Lab2_UART.map"
  )
endif()
