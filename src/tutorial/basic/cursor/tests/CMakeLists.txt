cmake_minimum_required(VERSION 4.2)

enable_testing()

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/LineTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CursorTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CursorGameTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CursorKeyboardControllerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CursorGameControllerTest.cpp
  )

add_executable(tutorial_basic_cursor_test ${SOURCE})

include_directories("${GTEST_INCLUDE_DIRS}")

target_link_libraries(tutorial_basic_cursor_test PUBLIC
    tutorial_basic_cursor
    ${GTEST_LIBRARY_PATH}
	${GTEST_MAIN_LIBRARY_PATH}
)

add_test(
	NAME tutorial_basic_cursor_tests
    COMMAND tutorial_basic_cursor_test
)

