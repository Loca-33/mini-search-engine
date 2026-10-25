# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MiniSearchEngine_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MiniSearchEngine_autogen.dir\\ParseCache.txt"
  "MiniSearchEngine_autogen"
  )
endif()
