#ifndef PLANTES_H
#define PLANTES_H
#include <vector>
#include "boid.hpp"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <memory>
#include "viewport.hpp"

class Plantes {
private:
    SDL_Texture* texture = nullptr;
    int posX, posY;
    int largeur, hauteur;
    Uint32 creationTime;
    class PlanteLevel {
    public:
        virtual SDL_Texture* loadTexture(SDL_Renderer* renderer) = 0;
        virtual int getLargeur() const = 0;
        virtual int getHauteur() const = 0;
        virtual ~PlanteLevel() = default;
    };
    class PlantesLevel1 : public PlanteLevel {
    public:
        SDL_Texture* loadTexture(SDL_Renderer* renderer) override {
            SDL_Surface* surface = IMG_Load("../img/Plantes/PlanteLevel1.png");
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
        int getLargeur() const override { return 200; }
        int getHauteur() const override { return 250; }
    };
    class PlantesLevel2 : public PlanteLevel {
    public:
        SDL_Texture* loadTexture(SDL_Renderer* renderer) override {
            SDL_Surface* surface = IMG_Load("../img/Plantes/PlanteLevel2.png");
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
        int getLargeur() const override { return 200; }
        int getHauteur() const override { return 300; }
    };
    class PlantesLevel3 : public PlanteLevel {
    public:
        SDL_Texture* loadTexture(SDL_Renderer* renderer) override {
            SDL_Surface* surface = IMG_Load("../img/Plantes/PlanteLevel3.png");
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
        int getLargeur() const override { return 90; }
        int getHauteur() const override { return 90; }
    };
    std::unique_ptr<PlanteLevel> currentLevel;
    std::unique_ptr<PlanteLevel> previousLevel;
public:
    Plantes(SDL_Renderer* renderer, int x, int y)
            : posX(x), posY(y), currentLevel(std::make_unique<PlantesLevel1>()) 
    {
        creationTime = SDL_GetTicks();
        this->updateTexture(renderer);
    }
    ~Plantes() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    void draw(SDL_Renderer* renderer, const Viewport& viewport);
    void updateLevel(SDL_Renderer* renderer,int level);
    int getLevel();
    void setPosition(int x, int y);
    void updateTexture(SDL_Renderer* renderer);
    void checkEvolution(SDL_Renderer* renderer);
};
#endif // PLANTES_H