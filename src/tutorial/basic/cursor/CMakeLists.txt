set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Line.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Cursor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CursorGame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CursorKeyboardController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CursorGameController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Line.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Cursor.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/CursorGame.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/CursorKeyboardController.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/CursorGameController.hpp
  )

SET(TUTORIAL_BASIC_CURSOR_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Declare the library
add_library(tutorial_basic_cursor STATIC ${SOURCE})

target_include_directories(tutorial_basic_cursor PUBLIC ${TUTORIAL_BASIC_CURSOR_INCLUDE_DIRS})

target_link_libraries(tutorial_basic_cursor PUBLIC screen)

add_subdirectory(tests)
