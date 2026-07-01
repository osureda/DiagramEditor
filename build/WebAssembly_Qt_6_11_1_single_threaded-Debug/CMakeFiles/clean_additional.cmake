# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DiagramEditor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DiagramEditor_autogen.dir\\ParseCache.txt"
  "DiagramEditor_autogen"
  )
endif()
