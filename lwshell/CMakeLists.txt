cmake_minimum_required(VERSION 3.22)

# Debug message
message("Entering ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")

# Register core library
add_library(lwshell INTERFACE)
target_sources(lwshell PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/lwshell/lwshell.c)
target_include_directories(lwshell INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/include)

# Register other modules

# Debug message
message("Exiting ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")
