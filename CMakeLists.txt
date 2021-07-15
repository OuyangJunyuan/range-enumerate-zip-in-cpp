cmake_minimum_required(VERSION 3.13.2)
project(test)
#SET(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp )
target_link_libraries(test )
install(DIRECTORY iteration_utils
        DESTINATION include)