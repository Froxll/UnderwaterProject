#ifndef COINS_H
#define COINS_H
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <memory>
#include "viewport.hpp"



class Coins {
private:
    SDL_Texture* texture = nullptr;
    int posX, posY;
    int largeur, hauteur;
    Uint32 creationTime;
public:
    Coins(SDL_Renderer* renderer, int x, int y)
            : posX(x), posY(y)
    {
        creationTime = SDL_GetTicks();
        this->updateTexture(renderer);
    }
    ~Coins() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    SDL_Texture* loadTexture(SDL_Renderer* renderer) {
            SDL_Surface* surface = IMG_Load("../img/Coins/Coins_Yellow.png");
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

    void draw(SDL_Renderer* renderer, const Viewport& viewport, int frameWidth, int frameHeight, int currentFrame);


    void updateTexture(SDL_Renderer* renderer);
    int getX(){
        return posX;
    }

    int getY(){
        return posY;
    }

};





#endif // COINS_H