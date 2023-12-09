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