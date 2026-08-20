set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Exception.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Exception.hpp
  )

SET(OBSERVABILITY_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Declare the library
add_library(observability STATIC ${SOURCE})

target_include_directories(observability PUBLIC ${OBSERVABILITY_INCLUDE_DIRS})

add_subdirectory(tests)
