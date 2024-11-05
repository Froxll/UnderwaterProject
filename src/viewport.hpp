#ifndef PROJETPOISSON_VIEWPORT_HPP
#define PROJETPOISSON_VIEWPORT_HPP

#pragma once
#include <SDL2/SDL.h>

struct Viewport {
    float x;      // Position X du viewport dans le monde
    float y;      // Position Y du viewport dans le monde
    int width;    // Largeur du viewport (pixels à l'écran)
    int height;   // Hauteur du viewport (pixels à l'écran)
};

struct GameWorld {
    static const int WIDTH = 2000;
    static const int HEIGHT = 2000;
};

extern const int VIEWPORT_WIDTH;  // Déclaré comme externe
extern const int VIEWPORT_HEIGHT; // Déclaré comme externe

// Déclaration de la fonction ici
SDL_Point worldToScreen(float worldX, float worldY, const Viewport& viewport);

#endif //PROJETPOISSON_VIEWPORT_HPP
