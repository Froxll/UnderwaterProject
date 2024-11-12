#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <vector>
#include "boid.hpp"
#include "behavior.hpp"
#include "render.hpp"
#include "viewport.hpp"
#include "plantes.hpp"
#include <SDL_image.h>

const int VIEWPORT_WIDTH = 1000;
const int VIEWPORT_HEIGHT = 1000;
const int NUM_BOIDS = 100;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Simulation de banc de poissons",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Viewport viewport = {
            .x = (GameWorld::WIDTH - VIEWPORT_WIDTH) / 2.0f,
            .y = (GameWorld::HEIGHT - VIEWPORT_HEIGHT) / 2.0f,
            .width = WINDOW_WIDTH,
            .height = WINDOW_HEIGHT
    };

    std::vector<Boid> boids;
    for (int i = 0; i < NUM_BOIDS; i++) {
        boids.emplace_back(rand() % GameWorld::WIDTH, rand() % GameWorld::HEIGHT);
    }

    bool running = true;
    SDL_Event event;
    const float CAMERA_SPEED = 5.0f;
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Erreur SDL_image: " << IMG_GetError() << std::endl;
        return 1;
    }

    SDL_Texture* mapTexture = IMG_LoadTexture(renderer, "img/map.png");
    if (!mapTexture) {
        std::cerr << "Erreur de chargement de l'image: " << IMG_GetError() << std::endl;
        return 1;
    }

    Plantes maPlante(renderer, "img/plante1.png", 100, 200);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        if (keyState[SDL_SCANCODE_LEFT]) viewport.x -= CAMERA_SPEED;
        if (keyState[SDL_SCANCODE_RIGHT]) viewport.x += CAMERA_SPEED;
        if (keyState[SDL_SCANCODE_UP]) viewport.y -= CAMERA_SPEED;
        if (keyState[SDL_SCANCODE_DOWN]) viewport.y += CAMERA_SPEED;

        viewport.x = std::max(0.0f, std::min(viewport.x, float(GameWorld::WIDTH - VIEWPORT_WIDTH)));
        viewport.y = std::max(0.0f, std::min(viewport.y, float(GameWorld::HEIGHT - VIEWPORT_HEIGHT)));

        for (Boid& boid : boids) {
            updateBoid(boid, boids, GameWorld::WIDTH, GameWorld::HEIGHT);
        }

        SDL_RenderClear(renderer);
        drawBackground(renderer, viewport, mapTexture);

        for (const Boid& boid : boids) {
            if (boid.x >= viewport.x && boid.x < viewport.x + VIEWPORT_WIDTH &&
                boid.y >= viewport.y && boid.y < viewport.y + VIEWPORT_HEIGHT) {
                drawBoid(renderer, boid, viewport);
            }
        }

        // Afficher et mettre à jour la plante
        maPlante.draw(renderer);
        maPlante.updateLevel(1);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(mapTexture);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
