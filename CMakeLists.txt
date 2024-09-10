cmake_minimum_required(VERSION 3.25)
project(UnderwaterProject)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(UnderwaterProject main.cpp)

target_link_libraries(UnderwaterProject ${SDL2_LIBRARIES})