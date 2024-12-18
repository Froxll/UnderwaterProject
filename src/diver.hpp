#ifndef UNDERWATERPROJECT_DIVER_HPP
#define UNDERWATERPROJECT_DIVER_HPP

#include <SDL2/SDL.h>
#include "viewport.hpp"

class Diver {
private:
    float angle;
    SDL_Texture* texture;
    int posX, posY;
    int numberOfCoins = 0;
    int lives = 3;

public:
    Diver(SDL_Renderer* renderer);
    ~Diver();
    void draw(SDL_Renderer* renderer, const Viewport& viewport);
    void updateAngle(const Uint8* keyState);
    float getAngle() const { return angle; }
    int getPosX() const { return posX; }
    int getPosY() const { return posY; }
    void setPosX(int newPosX);
    void setPosY(int newPosY);
    int getCoins() { return this->numberOfCoins; }
    int getLives() { return this->lives; }
    void incrementCoins(int number){ this->numberOfCoins+=number;}
    void incrementLives(int number){ 
        if(this->lives > 0 && this->lives <= 3){
            this->lives+=number;
        }

    }
};

#endif //UNDERWATERPROJECT_DIVER_HPP
