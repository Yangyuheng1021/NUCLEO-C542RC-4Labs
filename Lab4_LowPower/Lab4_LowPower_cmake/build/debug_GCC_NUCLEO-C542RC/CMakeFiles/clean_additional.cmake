# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "debug_GCC_NUCLEO-C542RC")
  file(REMOVE_RECURSE
  "Lab4_LowPower.elf"
  "Lab4_LowPower.map"
  )
endif()
