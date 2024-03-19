# 
# LIB_PREFIX: LWSHELL
#
# This file provides set of variables for end user
# and also generates one (or more) libraries, that can be added to the project using target_link_libraries(...)
#
# Before this file is included to the root CMakeLists file (using include() function), user can set some variables:
#
# LWSHELL_OPTS_FILE: If defined, it is the path to the user options file. If not defined, one will be generated for you automatically
# LWSHELL_COMPILE_OPTIONS: If defined, it provide compiler options for generated library.
# LWSHELL_COMPILE_DEFINITIONS: If defined, it provides "-D" definitions to the library build
#

# Custom include directory
set(LWSHELL_CUSTOM_INC_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib_inc)

# Library core sources
set(lwshell_core_SRCS 
    ${CMAKE_CURRENT_LIST_DIR}/src/lwshell/lwshell.c
)

# Setup include directories
set(lwshell_include_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/src/include
    ${LWSHELL_CUSTOM_INC_DIR}
)

# Register library to the system
add_library(lwshell INTERFACE)
target_sources(lwshell INTERFACE ${lwshell_core_SRCS})
target_include_directories(lwshell INTERFACE ${lwshell_include_DIRS})
target_compile_options(lwshell PRIVATE ${LWSHELL_COMPILE_OPTIONS})
target_compile_definitions(lwshell PRIVATE ${LWSHELL_COMPILE_DEFINITIONS})

# Create config file if user didn't provide one info himself
if(NOT LWSHELL_OPTS_FILE)
    message(STATUS "Using default lwshell_opts.h file")
    set(LWSHELL_OPTS_FILE ${CMAKE_CURRENT_LIST_DIR}/src/include/lwshell/lwshell_opts_template.h)
else()
    message(STATUS "Using custom lwshell_opts.h file from ${LWSHELL_OPTS_FILE}")
endif()
configure_file(${LWSHELL_OPTS_FILE} ${LWSHELL_CUSTOM_INC_DIR}/lwshell_opts.h COPYONLY)
