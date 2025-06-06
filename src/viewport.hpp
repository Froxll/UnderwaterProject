#ifndef PROJETPOISSON_VIEWPORT_HPP
#define PROJETPOISSON_VIEWPORT_HPP

#pragma once
#include <SDL.h>

const int WINDOW_WIDTH = 800;  // Taille de la fenêtre
const int WINDOW_HEIGHT = 600;

const int CAMERA_WIDTH = 350;
const int CAMERA_HEIGHT = 200;
const int CAMERA_SPEED = 5;

struct Viewport {
    float x;      // Position X du viewport dans le monde
    float y;      // Position Y du viewport dans le monde
    int width;    // Largeur du viewport (pixels à l'écran)
    int height;   // Hauteur du viewport (pixels à l'écran)
};



extern const int VIEWPORT_WIDTH;  // Déclaré comme externe
extern const int VIEWPORT_HEIGHT; // Déclaré comme externe

// Déclaration de la fonction ici
SDL_Point worldToScreen(float worldX, float worldY, const Viewport& viewport);
void drawBackground(SDL_Renderer* renderer, const Viewport& viewport, SDL_Texture* mapTexture);

#endif //PROJETPOISSON_VIEWPORT_HPP
