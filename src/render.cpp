#include "render.hpp"
#include <iostream>

using namespace std;

void drawBoid(SDL_Renderer* renderer, SDL_Texture* texture, const Boid& boid) {
    if (!texture) {
        cerr << "Texture invalide!" << endl;
        return;
    }

    SDL_Rect rect = { static_cast<int>(boid.x), static_cast<int>(boid.y), 20, 20 };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

