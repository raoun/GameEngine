cmake_minimum_required(VERSION 4.2)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

SET(3PL ${PROJECT_SOURCE_DIR}/3pl)

SET(GTEST_INCLUDE_DIRS ${3PL}/googletest/googletest/include)
SET(GTEST_LIBRARY_PATH ${3PL}/googletest/build-dir/lib/debug/gtest.lib)
SET(GTEST_LIBRARY googletest)
SET(GTEST_MAIN_LIBRARY_PATH ${3PL}/googletest/build-dir/lib/debug/gtest_main.lib)
SET(GTEST_MAIN_LIBRARY gtest_main)

SET(GMOCK_INCLUDE_DIRS ${3PL}/googletest/googlemock/include)
SET(GMOCK_LIBRARY_PATH ${3PL}/googletest/build-dir/lib/debug/gmock.lib)
SET(GMOCK_LIBRARY gmock)
SET(GMOCK_MAIN_LIBRARY_PATH ${3PL}/googletest/build-dir/lib/debug/gmock_main.lib)
SET(GMOCK_MAIN_LIBRARY gmock_main)

#include(FetchContent)
#FetchContent_Declare(
#  googletest
#  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

SET(OPEN_GL_INCLUDE_DIRS ${3PL}/glfw-3.5.1/include)
SET(OPEN_GL_LIBRARY_PATH ${3PL}/glfw-3.5.1/build-dir/src/debug/glfw3.lib)
SET(OPEN_GL_LIBRARY opengl32)

SET(GLEW_INCLUDE_DIRS ${3PL}/glew-2.3.1/include)
SET(GLEW_LIBRARY_PATH ${3PL}/glew-2.3.1/lib/Release/glew32s.lib)
SET(GLEW_LIBRARY ${3PL}/bin/Release/x64/glew32)

# Direct3D 11 and the Win32 headers/libs ship with the Windows SDK that
# comes bundled with the MSVC toolchain, so there is nothing to fetch
# into 3pl for these - the compiler/linker find them on their default paths.
SET(DIRECTX_LIBRARIES d3d11 dxgi d3dcompiler)
SET(WINDOWS_LIBRARIES user32 gdi32)


enable_testing()

add_subdirectory(src)

set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT entry)




