#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>
#include "plantes.hpp"
// Plantes functions here


void Plantes::updateTexture(SDL_Renderer* renderer) {
    if (this->texture == nullptr) {
        SDL_DestroyTexture(this->texture);  
        this->texture = nullptr;
    }
    this->texture = currentLevel->loadTexture(renderer);
    if (!this->texture) {
        SDL_Log("Erreur de chargement de la texture : %s", IMG_GetError());
    } 
    else {
        this->largeur = currentLevel->getLargeur();
        this->hauteur = currentLevel->getHauteur();
    }
}


// Méthode pour dessiner la plante
void Plantes::draw(SDL_Renderer* renderer, const Viewport& viewport) {
    SDL_Point screenPos = worldToScreen(this->posX, this->posY, viewport);
    SDL_Rect dstRect = {screenPos.x, screenPos.y, currentLevel->getLargeur(), currentLevel->getHauteur()};
    
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    } else {
        SDL_Log("Texture non chargée pour les plantes !");
    }

    // Dessiner le contour de la plante (rectangle)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); 
    SDL_RenderDrawRect(renderer, &dstRect);
}

// Méthode pour mettre à jour le niveau en fonction des ressources disponibles
void Plantes::updateLevel(SDL_Renderer* renderer,int level) {

    if (currentLevel) {
        previousLevel = std::move(currentLevel);
    }


    switch(level){
        case 1:
            currentLevel = std::make_unique<PlantesLevel1>();
            break;
        case 2 :
            currentLevel = std::make_unique<PlantesLevel2>();  
            break;
        case 3 : 
            currentLevel = std::make_unique<PlantesLevel3>();
            break;
        default:
            SDL_Log("This level is not valid : %d", level);
            return; 
    }

    if (previousLevel) { 
        int deltaHeight = currentLevel->getHauteur() - previousLevel->getHauteur();
        this->posY -= deltaHeight; 
    }

    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture = currentLevel->loadTexture(renderer);
    if (!texture) {
        SDL_Log("Erreur lors du chargement de la texture pour le niveau %d", level);
    }

}




int Plantes::getLevel(){
    if (dynamic_cast<PlantesLevel1*>(currentLevel.get())) {
        return 1;
    } 
    else if (dynamic_cast<PlantesLevel2*>(currentLevel.get())) {
        return 2;
    } 
    else if (dynamic_cast<PlantesLevel3*>(currentLevel.get())) {
        return 3;
    } 
    else {
        SDL_Log("Niveau inconnu pour la plante");
        return 0;
    }
}
void Plantes::setPosition(int x, int y){
    this->posX = x;
    this->posY = y;
}