#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "boid.hpp"

#pragma once
#include "viewport.hpp"

void drawBoid(SDL_Renderer* renderer, const Boid& boid, const Viewport& viewport);

#endif // RENDER_H

