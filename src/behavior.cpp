#include "behavior.hpp"
#include <cmath>
#include <algorithm>

// Constantes pour le comportement des boids
const float visual_range = 100.0f;
const float protected_range = 50.0f;
const float centering_factor = 0.005f;
const float matching_factor = 0.05f;
const float avoidfactor = 0.1f;
const float turnfactor = 0.1f;
const float minspeed = 1.5f;
const float maxspeed = 6.0f;

void updateBoid(Boid& boid, const std::vector<Boid>& boids, int worldWidth, int worldHeight, float timeFactor) {
    float xpos_avg = 0, ypos_avg = 0, xvel_avg = 0, yvel_avg = 0;
    int neighboring_boids = 0;
    float close_dx = 0, close_dy = 0;

    for (const Boid& otherboid : boids) {
        if (&otherboid == &boid) continue;

        float dx = boid.x - otherboid.x;
        float dy = boid.y - otherboid.y;

        // Gérer les bords du monde de manière toroïdale
        if (dx > worldWidth / 2) dx -= worldWidth;
        else if (dx < -worldWidth / 2) dx += worldWidth;
        if (dy > worldHeight / 2) dy -= worldHeight;
        else if (dy < -worldHeight / 2) dy += worldHeight;

        float squared_distance = dx * dx + dy * dy;

        if (squared_distance < protected_range * protected_range) {
            close_dx += dx;
            close_dy += dy;
        } else if (squared_distance < visual_range * visual_range) {
            xpos_avg += otherboid.x;
            ypos_avg += otherboid.y;
            xvel_avg += otherboid.vx;
            yvel_avg += otherboid.vy;
            neighboring_boids++;
        }
    }

    if (neighboring_boids > 0) {
        xpos_avg /= neighboring_boids;
        ypos_avg /= neighboring_boids;
        xvel_avg /= neighboring_boids;
        yvel_avg /= neighboring_boids;

        boid.vx += (xpos_avg - boid.x) * centering_factor +
                   (xvel_avg - boid.vx) * matching_factor;
        boid.vy += (ypos_avg - boid.y) * centering_factor +
                   (yvel_avg - boid.vy) * matching_factor;
    }

    boid.vx += close_dx * avoidfactor;
    boid.vy += close_dy * avoidfactor;

    // Appliquer le facteur de temps à la vitesse
    boid.vx *= timeFactor;
    boid.vy *= timeFactor;

    // Limite de vitesse
    float speed = std::sqrt(boid.vx * boid.vx + boid.vy * boid.vy);
    if (speed > maxspeed) {
        boid.vx = (boid.vx / speed) * maxspeed;
        boid.vy = (boid.vy / speed) * maxspeed;
    }
    if (speed < minspeed) {
        boid.vx = (boid.vx / speed) * minspeed;
        boid.vy = (boid.vy / speed) * minspeed;
    }

    // Mise à jour de la position avec gestion des bords
    boid.x += boid.vx;
    boid.y += boid.vy;

    // Gérer les bords du monde de manière toroïdale
    if (boid.x < 0) boid.x += worldWidth;
    if (boid.x >= worldWidth) boid.x -= worldWidth;
    if (boid.y < 0) boid.y += worldHeight;
    if (boid.y >= worldHeight) boid.y -= worldHeight;
}

