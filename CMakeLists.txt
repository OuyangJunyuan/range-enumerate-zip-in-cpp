cmake_minimum_required(VERSION 3.17)
project(test)
#SET(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp range.hpp)
target_link_libraries(test pthread)