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

    // Déclaration du constructeur
    Boid(float x_, float y_);
};
#endif // BOID_H
