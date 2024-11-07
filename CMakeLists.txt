cmake_minimum_required(VERSION 3.24)
project(UnderwaterProject)

set(CMAKE_CXX_STANDARD 23)

# Ajouter le chemin de la bibliothèque SDL2
set(CMAKE_PREFIX_PATH "C:/SDL2")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Trouver SDL_image
find_package(SDL2_image REQUIRED)

# Inclure les headers SDL2 et SDL_image
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

file(GLOB_RECURSE sourceCode src/*.cpp src/*.h)


# Ajouter le fichier source et définir l'exécutable
add_executable(UnderwaterProject ${sourceCode})

# Lier SDL2 et SDL_image avec l'exécutable
target_link_libraries(UnderwaterProject ${SDL2_LIBRARIES} -lSDL2_image)
