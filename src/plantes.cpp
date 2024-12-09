#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "plantes.hpp"
// Plantes functions here


void Plantes::updateTexture(SDL_Renderer* renderer) {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);  
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
    SDL_Rect dstRect = { screenPos.x, screenPos.y, largeur, hauteur };
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    } else {
        SDL_Log("Texture non chargée pour les plantes !");
    }

}

// Méthode pour mettre à jour le niveau en fonction des ressources disponibles
void Plantes::updateLevel(SDL_Renderer* renderer,int level) {
    switch(level){
        case 1:
            currentLevel = std::make_unique<PlantesLevel1>();
            break;
        case 2 :
            currentLevel = std::make_unique<PlantesLevel2>() ;   
            break;
        case 3 : 
            currentLevel = std::make_unique<PlantesLevel3>();
            break;
        default:
            SDL_Log("This level is not valid : %d", level);
            return;    
    }

    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture = currentLevel->loadTexture(renderer);
    if (!texture) {
        SDL_Log("Erreur lors du chargement de la texture pour le niveau %d", level);
    }

}



// Getters et setters si nécessaire
int Plantes::getLevel(){
    return 0;//Trouver un moyen de retourner 1 2 ou 3 en fonction de la classe utilisée
}
void Plantes::setPosition(int x, int y){
    this->posX = x;
    this->posY = y;
}