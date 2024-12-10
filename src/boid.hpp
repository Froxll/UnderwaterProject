#ifndef BOID_H
#define BOID_H

#pragma once
#include <cstdlib>

#pragma once

struct Boid {
    float x;
    float y;
    float vx;
    float vy;
    float biasval;
    int fishTextureIndex;  // Nouvelle ligne

    Boid(float x_, float y_, int textureIndex);  // Modifiez le constructeur
};

#endif // BOID_H



