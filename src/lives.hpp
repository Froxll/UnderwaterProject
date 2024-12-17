#ifndef LIVES_H
#define LIVES_H
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <memory>
#include "viewport.hpp"



class Lives {
private:
    SDL_Texture* texture = nullptr;
    int posX, posY;
    int largeur, hauteur;
    Uint32 creationTime;
public:
    Lives(SDL_Renderer* renderer, int x, int y)
            : posX(x), posY(y), largeur(20), hauteur(20)
    {
        creationTime = SDL_GetTicks();
        this->updateTexture(renderer);
    }
    ~Lives() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    SDL_Texture* loadTexture(SDL_Renderer* renderer) {
            SDL_Surface* surface = IMG_Load("../img/assets/Heart_Full.png");
            if (!surface) {
                SDL_Log("Erreur de chargement de l'image : %s", IMG_GetError());
                return nullptr;
            }
            
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);  
            if (!texture) {
                SDL_Log("Erreur de création de la texture : %s", SDL_GetError());
            }
            return texture;
    }

    void draw(SDL_Renderer* renderer, const Viewport& viewport);


    void updateTexture(SDL_Renderer* renderer);
    
    int getX(){
        return posX;
    }

    int getY(){
        return posY;
    }

};





#endif // LIVES_H