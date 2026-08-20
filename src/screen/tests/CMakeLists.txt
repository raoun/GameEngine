cmake_minimum_required(VERSION 4.2)

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowControllerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowTest.cpp
  )

add_executable(screentest ${SOURCE})

target_compile_definitions(screentest PRIVATE UNICODE _UNICODE)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories("${GMOCK_INCLUDE_DIRS}")

target_link_libraries(screentest PUBLIC
    screen
    ${GTEST_LIBRARY_PATH}
	${GTEST_MAIN_LIBRARY_PATH}
	${GMOCK_LIBRARY_PATH}
)

add_test(
	NAME screentests
    COMMAND screentest
)

