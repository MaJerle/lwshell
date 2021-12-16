cmake_minimum_required(VERSION 3.0.0)
project(LwLibPROJECT VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME}
    lwshell/src/lwshell/lwshell.c
    dev/VisualStudio/main.c
    )

target_include_directories(${PROJECT_NAME} PRIVATE
    dev/VisualStudio
    lwshell/src/include
    )

target_compile_definitions(${PROJECT_NAME} PRIVATE
    WIN32
    _DEBUG
    CONSOLE
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)