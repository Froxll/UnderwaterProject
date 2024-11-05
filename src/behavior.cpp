#include "behavior.hpp"
#include <cmath>
#include <limits>

const int WINDOW_WIDTH = 1000; // Largeur de la fenêtre
const int WINDOW_HEIGHT = 800; // Hauteur de la fenêtre

// Constantes pour le comportement des boids
const float visual_range = 100.0f;
const float protected_range = 20.0f;
const float centering_factor = 0.005f;
const float matching_factor = 0.05f;
const float avoidfactor = 0.05f;
const float turnfactor = 0.1f;
const float minspeed = 2.0f;
const float maxspeed = 6.0f;

void updateBoid(Boid& boid, const std::vector<Boid>& boids) {
    float xpos_avg = 0, ypos_avg = 0, xvel_avg = 0, yvel_avg = 0;
    int neighboring_boids = 0;
    float close_dx = 0, close_dy = 0;

    for (const Boid& otherboid : boids) {
        if (&otherboid == &boid) continue; // Ignorer le boid lui-même

        float dx = boid.x - otherboid.x;
        float dy = boid.y - otherboid.y;
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

    // Gestion des bordures de l'environnement
    if (boid.x < 0 || boid.x > WINDOW_WIDTH) boid.vx += turnfactor * (boid.x < 0 ? 1 : -1);
    if (boid.y < 0 || boid.y > WINDOW_HEIGHT) boid.vy += turnfactor * (boid.y < 0 ? 1 : -1);

    // Application du biais si nécessaire
    if (boid.biasval > 0) {
        boid.vx = (1 - boid.biasval) * boid.vx + (boid.biasval * 1);
    } else if (boid.biasval < 0) {
        boid.vx = (1 - boid.biasval) * boid.vx + (boid.biasval * -1);
    }

    // Calculer la vitesse du boid
    float speed = std::sqrt(boid.vx * boid.vx + boid.vy * boid.vy);

    // Limiter la vitesse du boid
    if (speed < minspeed) {
        boid.vx = (boid.vx / speed) * minspeed;
        boid.vy = (boid.vy / speed) * minspeed;
    } else if (speed > maxspeed) {
        boid.vx = (boid.vx / speed) * maxspeed;
        boid.vy = (boid.vy / speed) * maxspeed;
    }

    // Mettre à jour la position du boid
    boid.x += boid.vx;
    boid.y += boid.vy;
}
