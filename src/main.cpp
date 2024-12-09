#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
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


    SDL_RenderSetLogicalSize(renderer, 800, 600);
    
    Viewport viewport = {
            .x = (GameWorld::WIDTH - VIEWPORT_WIDTH) / 2.0f,
            .y = (GameWorld::HEIGHT - VIEWPORT_HEIGHT) / 2.0f,
            .width = WINDOW_WIDTH,
            .height = WINDOW_HEIGHT
    };

    std::vector<Boid> boids;
    for (int i = 0; i < NUM_BOIDS; i++) {
        boids.emplace_back(rand() % GameWorld::WIDTH, rand() % GameWorld::HEIGHT, rand() % 4); //doc : Inserts a new element at the end of the vector, right after its current last element.
    }

    bool running = true;
    SDL_Event event;
    const float CAMERA_SPEED = 5.0f;
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Erreur SDL_image: " << IMG_GetError() << std::endl;
        return 1;
    }

    SDL_Texture* mapTexture = IMG_LoadTexture(renderer, "img/mapv2.png");
    if (!mapTexture) {
        std::cerr << "Erreur de chargement de l'image: " << IMG_GetError() << std::endl;
        return 1;
    }

    Plantes maPlante(renderer, 0, 1079);

    SDL_Texture* fishTextures[4];
    fishTextures[0] = IMG_LoadTexture(renderer, "img/Poissons/fish1Texture.png");
    fishTextures[1] = IMG_LoadTexture(renderer, "img/Poissons/fish2Texture.png");
    fishTextures[2] = IMG_LoadTexture(renderer, "img/Poissons/fish3Texture.png");
    fishTextures[3] = IMG_LoadTexture(renderer, "img/Poissons/fish4Texture.png");

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
                drawBoid(renderer, boid, viewport, fishTextures);
            }
        }

        maPlante.updateLevel(renderer,2);
        maPlante.draw(renderer, viewport);

        int mapWidth, mapHeight;
        SDL_QueryTexture(mapTexture, nullptr, nullptr, &mapWidth, &mapHeight);
        std::cout << "Map size: " << mapWidth << "x" << mapHeight << std::endl;

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    for (auto texture : fishTextures) {
        SDL_DestroyTexture(texture);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(mapTexture);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
