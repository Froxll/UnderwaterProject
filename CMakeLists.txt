cmake_minimum_required(VERSION 3.25)
project(UnderwaterProject)

set(CMAKE_CXX_STANDARD 23)

# Ajouter le chemin de la bibliothèque SDL2
set(CMAKE_PREFIX_PATH "C:/SDL2")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(UnderwaterProject src/main.cpp)

# Lier SDL2
target_link_libraries(UnderwaterProject ${SDL2_LIBRARIES} -lSDL2_image)