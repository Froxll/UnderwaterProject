#ifndef CONFIG_HPP
#define CONFIG_HPP

// Dimensions de la fenêtre
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

// Dimensions de l'environnement
const int ENV_WIDTH = 1600;
const int ENV_HEIGHT = 1200;

// Paramètres des boids
const float VISUAL_RANGE = 100.0f;
const float PROTECTED_RANGE = 20.0f;
const float CENTERING_FACTOR = 0.05f;
const float MATCHING_FACTOR = 0.05f;
const float AVOID_FACTOR = 0.1f;
const float TURN_FACTOR = 0.1f;
const float MIN_SPEED = 1.0f;
const float MAX_SPEED = 5.0f;

#endif // CONFIG_HPP
