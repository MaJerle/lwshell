# 
# This file provides set of variables for end user
# and also generates one (or more) libraries, that can be added to the project using target_link_libraries(...)
#
# Before this file is included to the root CMakeLists file (using include() function), user can set some variables:
#
# LWSHELL_OPTS_DIR: If defined, it should set the folder path where options file shall be generated.
# LWSHELL_COMPILE_OPTIONS: If defined, it provide compiler options for generated library.
# LWSHELL_COMPILE_DEFINITIONS: If defined, it provides "-D" definitions to the library build
#

# Library core sources
set(lwshell_core_SRCS 
    ${CMAKE_CURRENT_LIST_DIR}/src/lwshell/lwshell.c
)

# Setup include directories
set(lwshell_include_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/src/include
)

# Register library to the system
add_library(lwshell INTERFACE)
target_sources(lwshell INTERFACE ${lwshell_core_SRCS})
target_include_directories(lwshell INTERFACE ${lwshell_include_DIRS})
target_compile_options(lwshell PRIVATE ${LWSHELL_COMPILE_OPTIONS})
target_compile_definitions(lwshell PRIVATE ${LWSHELL_COMPILE_DEFINITIONS})

# Create config file
if(DEFINED LWSHELL_OPTS_DIR AND NOT EXISTS ${LWSHELL_OPTS_DIR}/lwshell_opts.h)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/src/include/lwshell/lwshell_opts_template.h ${LWSHELL_OPTS_DIR}/lwshell_opts.h COPYONLY)
endif()