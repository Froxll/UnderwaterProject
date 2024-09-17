cmake_minimum_required(VERSION 3.16)
project(UnderwaterProject)

set(CMAKE_CXX_STANDARD 17)

# Trouver SDL2
find_package(SDL2 REQUIRED)

# Trouver SDL_image
find_package(SDL2_image REQUIRED)

# Inclure les headers SDL2 et SDL_image
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Ajouter le fichier source et définir l'exécutable
add_executable(UnderwaterProject src/main.cpp)

# Lier SDL2 et SDL_image avec l'exécutable
target_link_libraries(UnderwaterProject ${SDL2_LIBRARIES} -lSDL2_image)