set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/IKeyboardController.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/IMenuController.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/IMouseController.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/IWindowController.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/MainWindowController.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Window.hpp
  )

SET(SCREEN_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Declare the library
add_library(screen STATIC ${SOURCE})

target_include_directories(screen PUBLIC ${SCREEN_INCLUDE_DIRS})

target_compile_definitions(screen PUBLIC UNICODE _UNICODE)

add_subdirectory(tests)
