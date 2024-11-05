#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "boid.hpp"

void drawBoid(SDL_Renderer* renderer, const Boid& boid);

#endif // RENDER_H
