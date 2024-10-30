# Platform-independent CMakefile to build LSS
# -------------------------------------------

cmake_minimum_required (VERSION 3.9)

project (mode)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

add_executable (mode main.c)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(mode PUBLIC OpenMP::OpenMP_CXX)
endif()

install (TARGETS mode DESTINATION . )
