#include "render.hpp"
#include <cmath>

void drawBoid(SDL_Renderer* renderer, const Boid& boid, const Viewport& viewport) {
    // Convertir la position du boid en coordonnées écran
    SDL_Point screenPos = worldToScreen(boid.x, boid.y, viewport);

    // Taille du triangle représentant le boid
    const int size = 10;

    // Calculer l'angle de rotation en radians
    float angle = atan2(boid.vy, boid.vx);

    // Points du triangle
    SDL_Point points[3];
    points[0] = {screenPos.x + static_cast<int>(size * cos(angle)),
                 screenPos.y + static_cast<int>(size * sin(angle))};
    points[1] = {screenPos.x + static_cast<int>(size * cos(angle + 2.5)),
                 screenPos.y + static_cast<int>(size * sin(angle + 2.5))};
    points[2] = {screenPos.x + static_cast<int>(size * cos(angle - 2.5)),
                 screenPos.y + static_cast<int>(size * sin(angle - 2.5))};

    // Dessiner le boid
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < 3; i++) {
        SDL_RenderDrawLine(renderer,
                           points[i].x, points[i].y,
                           points[(i + 1) % 3].x, points[(i + 1) % 3].y);
    }
}