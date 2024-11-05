#ifndef BOID_H
#define BOID_H

struct Boid {
    float x, y;   // Position
    float vx, vy; // Vitesse
    float biasval; // Valeur de biais pour le scout group

    Boid(float startX, float startY);
};

#endif // BOID_H
