#include "render.hpp"

void drawBoid(SDL_Renderer* renderer, const Boid& boid) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur blanche
    SDL_Rect rect = { static_cast<int>(boid.x), static_cast<int>(boid.y), 5, 5 }; // Rectangle de 5x5 pixels
    SDL_RenderFillRect(renderer, &rect);
}
