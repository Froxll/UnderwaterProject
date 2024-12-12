#ifndef UNDERWATERPROJECT_DIVER_HPP
#define UNDERWATERPROJECT_DIVER_HPP

#include <SDL2/SDL.h>
#include "viewport.hpp"

class Diver {
private:
    float angle;
    SDL_Texture* texture;
    int posX, posY;

public:
    Diver(SDL_Renderer* renderer);
    ~Diver();
    void draw(SDL_Renderer* renderer, const Viewport& viewport);
    void updateAngle(const Uint8* keyState);
    float getAngle() const { return angle; }
};

#endif //UNDERWATERPROJECT_DIVER_HPP
