cmake_minimum_required(VERSION 3.24)
project(UnderwaterProject)

set(CMAKE_CXX_STANDARD 23)

# Ajouter le chemin des bibliothèques SDL2
set(CMAKE_PREFIX_PATH "C:/sdl2")

# Trouver SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Trouver SDL_image
find_package(SDL2_image REQUIRED)

# Trouver SDL2_ttf
find_library(SDL2_TTF_LIBRARY SDL2_ttf PATHS C:/sdl2/lib REQUIRED)
find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h PATHS C:/sdl2/include/SDL2 REQUIRED)

include_directories(${SDL2_TTF_INCLUDE_DIR})

file(GLOB_RECURSE sourceCode src/*.cpp src/*.h)


# Ajouter le fichier source et définir l'exécutable
add_executable(UnderwaterProject ${sourceCode})

# Lier SDL2, SDL_image, et SDL2_ttf avec l'exécutable
target_link_libraries(UnderwaterProject ${SDL2_LIBRARIES} -lSDL2_image ${SDL2_TTF_LIBRARY})
