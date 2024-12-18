#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "lives.hpp"
// Plantes functions here

void Lives::updateTexture(SDL_Renderer* renderer) {
    if (this->texture == nullptr) {
        SDL_DestroyTexture(this->texture);  
        this->texture = nullptr;
    }
    this->texture = loadTexture(renderer);
    if (!this->texture) {
        SDL_Log("Erreur de chargement de la texture : %s", IMG_GetError());
    } 
}


void Lives::draw(SDL_Renderer* renderer, const Viewport& viewport) {

    SDL_Point screenPos = worldToScreen(this->posX, this->posY, viewport);
    SDL_Rect dstRect = {screenPos.x, screenPos.y, largeur, hauteur};
    
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    } else {
        SDL_Log("Texture non chargée pour les vies !");
    }

    
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);


}