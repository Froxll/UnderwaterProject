#include "render.hpp"
#include <cmath>

void drawBoid(SDL_Renderer* renderer, const Boid& boid, const Viewport& viewport, SDL_Texture** fishTextures) {
    SDL_Point screenPos = worldToScreen(boid.x, boid.y, viewport);

    float angle = atan2(boid.vy, boid.vx);
    angle = angle * 180 / M_PI;

    SDL_Rect dstRect = {
            screenPos.x - 25,
            screenPos.y - 25,
            50, 50
    };

    SDL_RenderCopyEx(renderer, fishTextures[boid.fishTextureIndex], nullptr, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}