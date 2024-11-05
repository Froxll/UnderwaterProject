#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "boid.hpp"
#include "behavior.hpp"
#include "render.hpp"
#include "viewport.hpp"

const int WINDOW_WIDTH = 800;  // Taille de la fenêtre
const int WINDOW_HEIGHT = 600;
const int VIEWPORT_WIDTH = 1000;  // Taille de la vue
const int VIEWPORT_HEIGHT = 1000;
const int NUM_BOIDS = 100;

// Fonction pour convertir les coordonnées monde en coordonnées écran
SDL_Point worldToScreen(float worldX, float worldY, const Viewport& viewport) {
    SDL_Point screen;
    screen.x = static_cast<int>((worldX - viewport.x) * viewport.width / VIEWPORT_WIDTH);
    screen.y = static_cast<int>((worldY - viewport.y) * viewport.height / VIEWPORT_HEIGHT);
    return screen;
}

void drawBackground(SDL_Renderer* renderer, const Viewport& viewport) {
    // Couleur de fond bleu uniforme
    SDL_SetRenderDrawColor(renderer, 0, 105, 148, 255);
    SDL_RenderClear(renderer);

    // Optionnel : Dessiner une grille ou des repères pour visualiser les limites du monde
    SDL_SetRenderDrawColor(renderer, 0, 125, 168, 255);

    // Dessiner les lignes verticales de la grille
    for (int x = 0; x < GameWorld::WIDTH; x += 200) {
        SDL_Point start = worldToScreen(x, 0, viewport);
        SDL_Point end = worldToScreen(x, GameWorld::HEIGHT, viewport);
        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }

    // Dessiner les lignes horizontales de la grille
    for (int y = 0; y < GameWorld::HEIGHT; y += 200) {
        SDL_Point start = worldToScreen(0, y, viewport);
        SDL_Point end = worldToScreen(GameWorld::WIDTH, y, viewport);
        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
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
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialiser le viewport au centre du monde
    Viewport viewport = {
            .x = (GameWorld::WIDTH - VIEWPORT_WIDTH) / 2.0f,
            .y = (GameWorld::HEIGHT - VIEWPORT_HEIGHT) / 2.0f,
            .width = WINDOW_WIDTH,
            .height = WINDOW_HEIGHT
    };

    // Créer les boids dans le monde complet
    std::vector<Boid> boids;
    for (int i = 0; i < NUM_BOIDS; i++) {
        boids.emplace_back(rand() % GameWorld::WIDTH, rand() % GameWorld::HEIGHT);
    }

    bool running = true;
    SDL_Event event;

    // Variables pour le déplacement de la caméra
    const float CAMERA_SPEED = 5.0f;
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Déplacer la caméra avec les touches fléchées
        if (keyState[SDL_SCANCODE_LEFT]) viewport.x -= CAMERA_SPEED;
        if (keyState[SDL_SCANCODE_RIGHT]) viewport.x += CAMERA_SPEED;
        if (keyState[SDL_SCANCODE_UP]) viewport.y -= CAMERA_SPEED;
        if (keyState[SDL_SCANCODE_DOWN]) viewport.y += CAMERA_SPEED;

        // Limiter la position du viewport aux limites du monde
        viewport.x = std::max(0.0f, std::min(viewport.x, float(GameWorld::WIDTH - VIEWPORT_WIDTH)));
        viewport.y = std::max(0.0f, std::min(viewport.y, float(GameWorld::HEIGHT - VIEWPORT_HEIGHT)));

        // Mettre à jour les boids
        for (Boid& boid : boids) {
            updateBoid(boid, boids, GameWorld::WIDTH, GameWorld::HEIGHT);
        }

        // Effacer l'écran et dessiner le fond
        drawBackground(renderer, viewport);

        // Dessiner les boids visibles
        for (const Boid& boid : boids) {
            // Vérifier si le boid est dans le viewport
            if (boid.x >= viewport.x && boid.x < viewport.x + VIEWPORT_WIDTH &&
                boid.y >= viewport.y && boid.y < viewport.y + VIEWPORT_HEIGHT) {
                drawBoid(renderer, boid, viewport);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}