#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "boid.hpp"
#include "behavior.hpp"
#include "render.hpp"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;
const int ENV_WIDTH = 1600;
const int ENV_HEIGHT = 1200;
const int NUM_BOIDS = 100;
const float visual_range = 100.0;
const float protected_range = 20.0;
const float centering_factor = 0.005;
const float matching_factor = 0.05;
const float avoidfactor = 0.05;
const float turnfactor = 0.1;
const float minspeed = 2.0;
const float maxspeed = 6.0;

void drawGradientBackground(SDL_Renderer* renderer) {
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        Uint8 blue = static_cast<Uint8>(255 * (1.0 - static_cast<float>(y) / WINDOW_HEIGHT));
        SDL_SetRenderDrawColor(renderer, 0, 0, blue, 255);
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Simulation de banc de poissons",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Créer un ensemble de poissons
    std::vector<Boid> boids;
    for (int i = 0; i < NUM_BOIDS; i++) {
        boids.emplace_back(rand() % ENV_WIDTH, rand() % ENV_HEIGHT);
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Mettre à jour la position de chaque poisson
        for (Boid& boid : boids) {
            updateBoid(boid, boids);
        }

        // Effacer l'écran avec un fond noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessiner le fond avec dégradé bleu
        drawGradientBackground(renderer);

        int w,h = 10;
        SDL_Texture* img = IMG_LoadTexture(renderer, "../img/fish.png");
        SDL_QueryTexture(img, NULL, NULL, &w, &h);

        // Dessiner chaque poisson
        for (const Boid& boid : boids) {
            drawBoid(renderer, img, boid);
        }

        // Afficher à l'écran
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Attente pour limiter la vitesse (environ 60 FPS)
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
