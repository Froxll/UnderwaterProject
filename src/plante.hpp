#ifndef PLANTE_H
#define PLANTE_H

#include <vector>
#include "boid.hpp"
#include <SDL2/SDL.h>
#include <string>



class Plante {
private:
    SDL_Texture* texture;
    int niveau;
    int posX, posY;
    int largeur, hauteur;

public:

    Plante(SDL_Renderer* renderer, const std::string& cheminImage, int x, int y)
            : posX(x), posY(y), niveau(1) // Niveau initial de la plante
    {
        SDL_Surface* surface = SDL_LoadBMP(cheminImage.c_str());
        if (surface) {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            // On récupère les dimensions de l'image
            SDL_QueryTexture(texture, NULL, NULL, &largeur, &hauteur);
        } else {
            texture = nullptr;
            SDL_Log("Erreur : %s", SDL_GetError());
        }
    }

    // Destructeur pour libérer la mémoire
    ~Plante() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

    void draw(SDL_Renderer* renderer);

    void updateLevel(int ressources);

    int getLevel();

    void setPosition(int x, int y);



};

#endif // PLANTE_H
