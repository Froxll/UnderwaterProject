#include "diver.hpp"
#include <SDL_image.h>
#include <cmath>

Diver::Diver(SDL_Renderer* renderer) : angle(0) {
    // Charger la texture du plongeur
    texture = IMG_LoadTexture(renderer, "../img/diver.png");
    if (!texture) {
        SDL_Log("Erreur de chargement de la texture du plongeur : %s", IMG_GetError());
    }

    // Position centrale
    posX = 400;  // Ajustez selon votre résolution
    posY = 300;
}

Diver::~Diver() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Diver::draw(SDL_Renderer* renderer, const Viewport& viewport) {
    SDL_Rect dstRect = {
            posX - 50,  // Centrer l'image
            posY - 50,
            100,  // Largeur
            100   // Hauteur
    };

    // Choisissez le flip en fonction de l'angle
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (angle == 180) {
        flip = SDL_FLIP_VERTICAL;
    }


    SDL_RenderCopyEx(renderer, texture, nullptr, &dstRect, angle, nullptr, flip);
}

void Diver::updateAngle(const Uint8* keyState) {
    // Ajustez l'angle en fonction des touches
    if (keyState[SDL_SCANCODE_UP]) {
        angle = -90;  // Haut
    }
    else if (keyState[SDL_SCANCODE_DOWN]) {
        angle = 90;   // Bas
    }
    else if (keyState[SDL_SCANCODE_LEFT]) {
        angle = 180;  // Gauche
    }
    else if (keyState[SDL_SCANCODE_RIGHT]) {
        angle = 0;    // Droite
    }
        // Diagonales
    else if (keyState[SDL_SCANCODE_UP] && keyState[SDL_SCANCODE_LEFT]) {
        angle = -135; // Haut-Gauche
    }
    else if (keyState[SDL_SCANCODE_UP] && keyState[SDL_SCANCODE_RIGHT]) {
        angle = -45;  // Haut-Droite
    }
    else if (keyState[SDL_SCANCODE_DOWN] && keyState[SDL_SCANCODE_LEFT]) {
        angle = 135;  // Bas-Gauche
    }
    else if (keyState[SDL_SCANCODE_DOWN] && keyState[SDL_SCANCODE_RIGHT]) {
        angle = 45;   // Bas-Droite
    }
}