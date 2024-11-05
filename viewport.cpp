#include "viewport.hpp"

SDL_Point worldToScreen(float worldX, float worldY, const Viewport& viewport) {
    SDL_Point screen;
    screen.x = 0;
    screen.y = 0;
    return screen;
}