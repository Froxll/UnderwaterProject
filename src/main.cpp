#include <SDL.h>
#include <iostream>
#include <vector>
#include "boid.hpp"
#include "behavior.hpp"
#include "render.hpp"
#include "viewport.hpp"
#include "screensManager.hpp"
#include "plantes.hpp"
#include "diver.hpp"
#include "collision.hpp"
#include "coins.hpp"
#include <SDL_mixer.h>
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

    Uint32 collisionTime = 0;
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

    SDL_Texture* heartFullTexture = IMG_LoadTexture(renderer, "../img/assets/Heart_Full.png");
    SDL_Texture* heartEmptyTexture = IMG_LoadTexture(renderer, "../img/assets/Heart_Empty.png");
    if (!heartFullTexture || !heartEmptyTexture) {
        std::cerr << "Erreur de chargement des textures des cœurs : " << IMG_GetError() << std::endl;
        return 1;
    }
    int lives=3;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Erreur SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    Mix_Chunk* one_lives_sound = Mix_LoadWAV("../songs/1lives_sound.wav");
    Mix_Chunk* two_lives_sound = Mix_LoadWAV("../songs/2lives_sound.wav");
    Mix_Chunk* gameOverSound = Mix_LoadWAV("../songs/death_sound.wav");

    if (!one_lives_sound || !two_lives_sound || !gameOverSound) {
        std::cerr << "Erreur de chargement des sons : " << Mix_GetError() << std::endl;
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
    Plantes maPlante(renderer, 100, 750);

    bool isPaused = false;
    bool isGameLaunched = true;
    bool isWaitingScreenShowed = false;

    SDL_Texture* pauseButtonTexture = IMG_LoadTexture(renderer, "../img/assets/Pause.png");
    if (!pauseButtonTexture) {
        std::cerr << "Erreur : Impossible de charger la texture du bouton !" << std::endl;
        return 1;
    }

    SDL_Rect pauseButton = {680, 20, 100, 50};

    SDL_Texture* resumeTexture = createTexture(renderer, window, "../img/assets/Start.png");
    SDL_Texture* quitTexture = createTexture(renderer, window, "../img/assets/Stop.png");
    SDL_Texture* newGameTexture = createTexture(renderer, window, "../img/assets/New_Game.png");


    Uint32 startTime = SDL_GetTicks();

    while (running) {

        if (isPaused) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_Rect overlay = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
            SDL_RenderFillRect(renderer, &overlay);

            // Bouton start/resume
            SDL_Rect resumeButton = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 150,  BUTTON_RESUME_WIDTH, BUTTON_RESUME_HEIGHT};
            SDL_RenderCopy(renderer, resumeTexture, nullptr, &resumeButton);

            // Bouton stop
            SDL_Rect quitButton = {WINDOW_WIDTH / 2 - 95, WINDOW_HEIGHT / 2 - 50,  BUTTON_STOP_WIDTH, BUTTON_STOP_HEIGHT};
            SDL_RenderCopy(renderer, quitTexture, nullptr, &quitButton);

            // Bouton new game
            SDL_Rect newGameButton = {WINDOW_WIDTH / 2 - 160, WINDOW_HEIGHT / 2 + 45,  BUTTON_NEWGAME_WIDTH, BUTTON_NEWGAME_HEIGHT};
            SDL_RenderCopy(renderer, newGameTexture, nullptr, &newGameButton);

            SDL_RenderPresent(renderer);

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x = event.button.x;
                    int y = event.button.y;

                    // Click sur le bouton Start/Resume
                    if (x >= resumeButton.x && x <= resumeButton.x + resumeButton.w &&
                        y >= resumeButton.y && y <= resumeButton.y + resumeButton.h) {
                        isPaused = false;
                    }

                    // Click sur le bouton Stop
                    if (x >= quitButton.x && x <= quitButton.x + quitButton.w &&
                        y >= quitButton.y && y <= quitButton.y + quitButton.h) {
                        running = false;
                    }

                    // Click sur le bouton New Game
                    if (x >= newGameButton.x && x <= newGameButton.x + newGameButton.w &&
                        y >= newGameButton.y && y <= newGameButton.y + newGameButton.h) {
                        running = false;
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_DestroyTexture(mapTexture);
                        IMG_Quit();
                        SDL_Quit();
                        main(0, nullptr);
                        return 0;
                    }
                } else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        isPaused = false;
                    }
                }
            }
        } else {

            SDL_RenderCopy(renderer, pauseButtonTexture, nullptr, &pauseButton);
            SDL_RenderPresent(renderer);

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x = event.button.x;
                    int y = event.button.y;

                    if (x >= pauseButton.x && x <= pauseButton.x + BUTTON_PAUSE_WIDTH && y >= pauseButton.y && y <= pauseButton.y + BUTTON_PAUSE_HEIGHT) {
                        isPaused = true;
                    }
                } else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        isPaused = true;
                    }
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

        SDL_Rect diverRect = {
                static_cast<int>(diver.getPosX() - 50),  
                static_cast<int>(diver.getPosY() - 50),  
                100,  // width
                100   // height
        };

        for (const Boid& boid : boids) {
            if (boid.x >= viewport.x && boid.x < viewport.x + VIEWPORT_WIDTH &&
                boid.y >= viewport.y && boid.y < viewport.y + VIEWPORT_HEIGHT) {


                SDL_Rect boidRect = {
                        static_cast<int>(boid.x - viewport.x - 25),  
                        static_cast<int>(boid.y - viewport.y - 25),
                        50, 
                        50
                };

                drawBoid(renderer, boid, viewport, fishTextures);
                SDL_RenderDrawRect(renderer, &boidRect);  // Draw boid hitbox

                Uint32 currentTime = SDL_GetTicks();  // Temps actuel
                if (checkCollision(diverRect, boidRect) && (currentTime - collisionTime > 1000)) {
                    collisionTime = currentTime;  // Réinitialiser le timer de collision
                    std::cout << "Collision!" << std::endl;

                    if (lives > 0) {
                        lives--;  // Réduire le nombre de vies

                        // Jouer le son approprié selon la vie restante
                        if (lives == 2) {
                            Mix_PlayChannel(-1, one_lives_sound, 0);  // Perte de la première vie
                        } else if (lives == 1) {
                            Mix_PlayChannel(-1, two_lives_sound, 0);  // Perte de la deuxième vie
                        } else if (lives == 0) {
                            Mix_PlayChannel(-1, gameOverSound, 0);   // Game over
                        }
                    }
                }
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

        int heartWidth = 50;  // Largeur d'un cœur (ajustez selon votre image)
        int heartHeight = 50; // Hauteur d'un cœur
        int heartSpacing = 10; // Espacement entre les cœurs
        int startX = 10; // Position de départ en X (en haut à gauche)
        int startY = 10; // Position de départ en Y (en haut à gauche)

        for (int i = 0; i < 3; i++) {
            SDL_Rect heartRect = {
                    startX + i * (heartWidth + heartSpacing), // Position X avec espacement
                    startY,                                  // Position Y fixe
                    heartWidth,                              // Largeur du cœur
                    heartHeight                              // Hauteur du cœur
            };

            if (i < lives) {
                SDL_RenderCopy(renderer, heartFullTexture, nullptr, &heartRect); // Cœur plein
            } else {
                SDL_RenderCopy(renderer, heartEmptyTexture, nullptr, &heartRect); // Cœur vide
            }
        }

            SDL_Delay(16);
        }
    }

    for (auto texture : fishTextures) {
        SDL_DestroyTexture(texture);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyTexture(heartFullTexture);
    SDL_DestroyTexture(heartEmptyTexture);
    Mix_FreeChunk(one_lives_sound);
    Mix_FreeChunk(two_lives_sound);
    Mix_FreeChunk(gameOverSound);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
