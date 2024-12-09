#include "viewport.hpp"

// Fonction pour convertir les coordonnées monde en coordonnées écran
SDL_Point worldToScreen(float worldX, float worldY, const Viewport& viewport) {
    SDL_Point screen;
    screen.x = static_cast<int>((worldX - viewport.x) * viewport.width / VIEWPORT_WIDTH);
    screen.y = static_cast<int>((worldY - viewport.y) * viewport.height / VIEWPORT_HEIGHT);
    return screen;
}

void drawBackground(SDL_Renderer* renderer, const Viewport& viewport, SDL_Texture* mapTexture) {
    SDL_Rect srcRect = {static_cast<int>(viewport.x), static_cast<int>(viewport.y), 
                        static_cast<int>(viewport.width), static_cast<int>(viewport.height)};
    SDL_Rect dstRect = {0, 0, viewport.width, viewport.height};

    SDL_RenderCopy(renderer, mapTexture, &srcRect, &dstRect);
}