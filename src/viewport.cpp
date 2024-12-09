#include "viewport.hpp"
#include <iostream>
#include <vector>
// Fonction pour convertir les coordonnées monde en coordonnées écran
SDL_Point worldToScreen(float worldX, float worldY, const Viewport& viewport) {
    SDL_Point screen;
    screen.x = static_cast<int>((worldX - viewport.x) * viewport.width / VIEWPORT_WIDTH);
    screen.y = static_cast<int>((worldY - viewport.y) * viewport.height / VIEWPORT_HEIGHT);
    return screen;
}

void drawBackground(SDL_Renderer* renderer, const Viewport& viewport, SDL_Texture* mapTexture) {

    int textureWidth, textureHeight;
    SDL_QueryTexture(mapTexture, nullptr, nullptr, &textureWidth, &textureHeight);


    SDL_Rect srcRect = {
        static_cast<int>(std::max(0.0f, std::min(viewport.x, static_cast<float>(textureWidth - viewport.width)))),
        static_cast<int>(std::max(0.0f, std::min(viewport.y, static_cast<float>(textureHeight - viewport.height)))),
        static_cast<int>(std::min(static_cast<float>(viewport.width), static_cast<float>(textureWidth))),
        static_cast<int>(std::min(static_cast<float>(viewport.height), static_cast<float>(textureHeight)))
    };
    SDL_Rect dstRect = {0, 0, viewport.width, viewport.height};

    SDL_RenderCopy(renderer, mapTexture, &srcRect, &dstRect);
}