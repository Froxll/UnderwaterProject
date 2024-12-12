#include <SDL.h>
#include <iostream>
#include <vector>
#include "boid.hpp"
#include "behavior.hpp"
#include "render.hpp"
#include "viewport.hpp"
#include "welcomeScreen.hpp"
#include "plantes.hpp"
#include "diver.hpp"
#include "coins.hpp"
#include <SDL_image.h>

const int MAP_WIDTH = 1920;  // Largeur de la carte
const int MAP_HEIGHT = 1080; // Hauteur de la carte
const int VIEWPORT_WIDTH = 800;  // Largeur de la fenêtre (viewport)
const int VIEWPORT_HEIGHT = 600; // Hauteur de la fenêtre (viewport)
const int NUM_BOIDS = 20;

//Plantes
const int MAX_PLANTES = 5;

//Coins 

const int FRAME_WIDTH = 16;  
const int FRAME_HEIGHT = 17; 
const int NUM_FRAMES = 5; 
const int MAX_COINS = 10;   



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

    Diver diver(renderer);

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

    
    Uint32 lastSpawnTime = SDL_GetTicks();
    int spawnInterval = 2000;             

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

    //Stocker les plantes

    std::vector<std::unique_ptr<Plantes>> plantes;


    //Stocker les coins 

    std::vector<std::unique_ptr<Coins>> coins;

    int currentNbCoins = 0;

    Uint32 lastCoinSpawnTime = SDL_GetTicks();
    const Uint32 coinSpawnInterval = 3000; 


    SDL_Texture* fishTextures[4];
    fishTextures[0] = IMG_LoadTexture(renderer, "../img/Poissons/fish1Texture.png");
    fishTextures[1] = IMG_LoadTexture(renderer, "../img/Poissons/fish2Texture.png");
    fishTextures[2] = IMG_LoadTexture(renderer, "../img/Poissons/fish3Texture.png");
    fishTextures[3] = IMG_LoadTexture(renderer, "../img/Poissons/fish4Texture.png");


    Uint32 startTime = SDL_GetTicks();
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

        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        float timeFactor = 0.3f + elapsedTime / 50000.0f;

        for (Boid& boid : boids) {
            updateBoid(boid, boids, MAP_WIDTH, MAP_HEIGHT, timeFactor);
        }
        SDL_RenderClear(renderer);
        drawBackground(renderer, viewport, mapTexture);

        for (const Boid& boid : boids) {
            if (boid.x >= viewport.x && boid.x < viewport.x + VIEWPORT_WIDTH &&
                boid.y >= viewport.y && boid.y < viewport.y + VIEWPORT_HEIGHT) {
                drawBoid(renderer, boid, viewport, fishTextures);
            }
        }
        

        //Apparition des plantes 

        Uint32 currentTime = SDL_GetTicks();

        if (currentTime > lastSpawnTime + spawnInterval) {

            int x = rand() % 1920; 
            int y = 750;
            plantes.push_back(std::make_unique<Plantes>(renderer, x, y));
            
            lastSpawnTime = currentTime;


            spawnInterval = 15000 + rand() % 10000;
        }


        for (const auto& plante : plantes) {
            plante->draw(renderer, viewport); 
            plante->checkEvolution(renderer);
        }

        //Gestion coins

        int currentFrame = 0;
        Uint32 frameTime = 100;  
        Uint32 lastFrameTime = 0;


        if (currentTime > lastCoinSpawnTime + coinSpawnInterval && currentNbCoins <= MAX_COINS) {
            std::cout << "i" << std::endl;
            int x = rand() % MAP_WIDTH;  
            int y = rand() % MAP_HEIGHT; 
            coins.push_back(std::make_unique<Coins>(renderer, x, y));
            lastCoinSpawnTime = currentTime;
            currentNbCoins += 1;
        }
        
        for (const auto& coin : coins) {
            if (coin->getX() >= viewport.x && coin->getX() < viewport.x + VIEWPORT_WIDTH &&
                coin->getY() >= viewport.y && coin->getY() < viewport.y + VIEWPORT_HEIGHT) {
                int currentFrame = (currentTime / 100) % NUM_FRAMES; 
                coin->draw(renderer, viewport, FRAME_WIDTH, FRAME_HEIGHT, currentFrame);
            }
        }






        //Gestion diver
        int mapWidth, mapHeight;
        SDL_QueryTexture(mapTexture, nullptr, nullptr, &mapWidth, &mapHeight);

        diver.updateAngle(keyState);
        diver.draw(renderer, viewport);

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
