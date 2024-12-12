#include <SDL.h>
#include <iostream>
#include <vector>
#include "boid.hpp"
#include "behavior.hpp"
#include "render.hpp"
#include "viewport.hpp"
#include "welcomeScreen.hpp"
#include "plantes.hpp"
#include <SDL_image.h>

const int MAP_WIDTH = 1920;  // Largeur de la carte
const int MAP_HEIGHT = 1080; // Hauteur de la carte
const int VIEWPORT_WIDTH = 800;  // Largeur de la fenêtre (viewport)
const int VIEWPORT_HEIGHT = 600; // Hauteur de la fenêtre (viewport)
const int NUM_BOIDS = 100;

//Plantes
const int MAX_PLANTES = 5;



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


    string playerName = "";

    // Appeler l'écran d'accueil
    if (!showWelcomeScreen(renderer, window, &playerName)) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    std:cerr << playerName << std::endl;

    // Initialiser le viewport au centre du monde
    SDL_RenderSetLogicalSize(renderer, 800, 600);
    SDL_RenderSetLogicalSize(renderer, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    
    Viewport viewport = {
            .x = 0,
            .y = 0,
            .width = WINDOW_WIDTH,
            .height = WINDOW_HEIGHT
    };

    std::vector<Boid> boids;
    for (int i = 0; i < NUM_BOIDS; i++) {
        boids.emplace_back(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 4);
    }



    bool running = true;
    SDL_Event event;
    const float CAMERA_SPEED = 5.0f;
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Erreur SDL_image: " << IMG_GetError() << std::endl;
        return 1;
    }

    // Charger la texture de la map
    SDL_Texture* mapTexture = IMG_LoadTexture(renderer, "../img/map.png");
    if (!mapTexture) {
        std::cerr << "Erreur de chargement de l'image: " << IMG_GetError() << std::endl;
        return 1;
    }

    SDL_Texture* fishTextures[4];
    fishTextures[0] = IMG_LoadTexture(renderer, "../img/Poissons/fish1Texture.png");
    fishTextures[1] = IMG_LoadTexture(renderer, "../img/Poissons/fish2Texture.png");
    fishTextures[2] = IMG_LoadTexture(renderer, "../img/Poissons/fish3Texture.png");
    fishTextures[3] = IMG_LoadTexture(renderer, "../img/Poissons/fish4Texture.png");
    Plantes maPlante(renderer, 100, 750);

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

        viewport.x = std::max(0.0f, std::min(viewport.x, float(MAP_WIDTH - VIEWPORT_WIDTH)));
        viewport.y = std::max(0.0f, std::min(viewport.y, float(MAP_HEIGHT - VIEWPORT_HEIGHT)));

        for (Boid& boid : boids) {
            updateBoid(boid, boids, MAP_WIDTH, MAP_HEIGHT);
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
