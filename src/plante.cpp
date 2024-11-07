#include <SDL2/SDL.h>
#include <string>
#include "plante.hpp"
// Plantes functions here


// Méthode pour dessiner la plante
void Plante::draw(SDL_Renderer* renderer) {
    SDL_Rect dstRect = { posX, posY, largeur, hauteur };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}

// Méthode pour mettre à jour le niveau en fonction des ressources disponibles
void Plante::updateLevel(int ressources) {
    //this->niveau = this->level / 10; // Exemple : on augmente d'un niveau tous les 10 ressources
}

// Getters et setters si nécessaire
int Plante::getLevel(){
    return this->niveau;
}
void Plante::setPosition(int x, int y){
    this->posX = x;
    this->posY = y;
}