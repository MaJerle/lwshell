cmake_minimum_required(VERSION 3.22)

# Register core library
add_library(lwshell INTERFACE)
target_sources(lwshell PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/lwshell/lwshell.c)
target_include_directories(lwshell INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/include)

# Create config file
if(DEFINED LWSHELL_OPTS_DIR AND NOT EXISTS ${LWSHELL_OPTS_DIR}/lwshell_opts.h)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/src/include/lwshell/lwshell_opts_template.h ${LWSHELL_OPTS_DIR}/lwshell_opts.h COPYONLY)
endif()