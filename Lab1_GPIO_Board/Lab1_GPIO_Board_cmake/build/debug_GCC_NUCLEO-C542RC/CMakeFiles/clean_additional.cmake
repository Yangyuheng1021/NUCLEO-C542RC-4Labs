# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "debug_GCC_NUCLEO-C542RC")
  file(REMOVE_RECURSE
  "Lab1_GPIO_Board.elf"
  "Lab1_GPIO_Board.map"
  )
endif()
