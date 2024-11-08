#include "viewport.hpp"

// Fonction pour convertir les coordonnées monde en coordonnées écran
SDL_Point worldToScreen(float worldX, float worldY, const Viewport& viewport) {
    SDL_Point screen;
    screen.x = static_cast<int>((worldX - viewport.x) * viewport.width / VIEWPORT_WIDTH);
    screen.y = static_cast<int>((worldY - viewport.y) * viewport.height / VIEWPORT_HEIGHT);
    return screen;
}

void drawBackground(SDL_Renderer* renderer, const Viewport& viewport, SDL_Texture* mapTexture) {
    // Définir la portion de la texture à afficher (rectangle source)
    SDL_Rect srcRect;
    srcRect.x = static_cast<int>(viewport.x);  // Coordonnée x dans la texture
    srcRect.y = static_cast<int>(viewport.y);  // Coordonnée y dans la texture
    srcRect.w = viewport.width;                // Largeur de la portion de la texture
    srcRect.h = viewport.height;               // Hauteur de la portion de la texture

    // Définir la position sur l'écran (rectangle de destination)
    SDL_Rect destRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    // Afficher la texture
    SDL_RenderCopy(renderer, mapTexture, &srcRect, &destRect);
}