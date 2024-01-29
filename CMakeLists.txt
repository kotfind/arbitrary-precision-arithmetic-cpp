cmake_minimum_required(VERSION 3.16)

project(arbitrary-precision-arithmetic-cpp LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS "-fuse-ld=mold")
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=undefined,address -g3 -O0")

add_subdirectory(real)
include_directories(real)
add_subdirectory(pi)
add_subdirectory(tests)
