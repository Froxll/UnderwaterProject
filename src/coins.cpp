#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "coins.hpp"
// Plantes functions here

void Coins::updateTexture(SDL_Renderer* renderer) {
    if (this->texture == nullptr) {
        SDL_DestroyTexture(this->texture);  
        this->texture = nullptr;
    }
    this->texture = loadTexture(renderer);
    if (!this->texture) {
        SDL_Log("Erreur de chargement de la texture : %s", IMG_GetError());
    } 
}


void Coins::draw(SDL_Renderer* renderer, const Viewport& viewport, int frameWidth, int frameHeight, int currentFrame) {

    SDL_Point screenPos = worldToScreen(this->posX, this->posY, viewport);
    

    SDL_Rect dstRect = {screenPos.x, screenPos.y, frameWidth, frameHeight};

    SDL_Rect srcRect = {currentFrame * frameWidth, 0, frameWidth, frameHeight};

    if (texture) {

        SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
    } else {
        SDL_Log("Texture non chargée pour les pièces !");
    }


    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);

}