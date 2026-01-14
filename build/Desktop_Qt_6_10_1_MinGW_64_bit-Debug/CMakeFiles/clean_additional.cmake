# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ddcar2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ddcar2_autogen.dir\\ParseCache.txt"
  "ddcar2_autogen"
  )
endif()
