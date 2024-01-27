cmake_minimum_required(VERSION 3.16)

project(real LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_FLAGS "-fuse-ld=mold")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_FLAGS} -fsanitize=undefined,address -g3 -O0")

add_library(real SHARED
    Real.cpp
    Real.hpp
)

add_executable(real_bin main.cpp)
target_link_libraries(real_bin real)
