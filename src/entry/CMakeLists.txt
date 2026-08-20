cmake_minimum_required(VERSION 4.2)

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/windows_main.cpp
  )

add_executable(entry WIN32 ${SOURCE})

target_compile_definitions(entry PRIVATE UNICODE _UNICODE)

target_link_libraries(entry PUBLIC
    screen
    tutorial_basic_cursor
    ${DIRECTX_LIBRARIES}
    ${WINDOWS_LIBRARIES}
)

