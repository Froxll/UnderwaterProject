#include "boid.hpp"
#include <cstdlib>

Boid::Boid(float x_, float y_, int textureIndex)
        : x(x_), y(y_), vx(0), vy(0), biasval(0), fishTextureIndex(textureIndex) {
    vx = (rand() % 100 - 50) / 25.0f;
    vy = (rand() % 100 - 50) / 25.0f;
}