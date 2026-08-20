cmake_minimum_required(VERSION 4.2)

enable_testing()

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/ExceptionTest.cpp
  )

add_executable(observabilitytest ${SOURCE})

include_directories("${GTEST_INCLUDE_DIRS}")
#include_directories("${OBSERVABILITY_INCLUDE_DIRS}")

target_link_libraries(observabilitytest PUBLIC
    observability
    ${GTEST_LIBRARY_PATH}
	${GTEST_MAIN_LIBRARY_PATH}
)

add_test(
	NAME observabilitytests
    COMMAND observabilitytest
)

