cmake_minimum_required(VERSION 3.13)

# Debug message
message("LWSHELL: Entering lib source CMakeLists.txt")

# Set library name
set(LWSHELL_LIB_NAME "lwshell")

# Register library to the system
add_library(${LWSHELL_LIB_NAME} INTERFACE)

# Setup generic source files
target_sources(${LWSHELL_LIB_NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/lwshell/lwshell.c
    )

# Setup include directories
target_include_directories(${LWSHELL_LIB_NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/include
    )
