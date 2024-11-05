#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "boid.hpp"
#include "behavior.hpp"
#include "render.hpp"
#include "viewport.hpp"

#include <SDL2/SDL_image.h>

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

void drawBackground(SDL_Renderer* renderer, const Viewport& viewport, SDL_Texture* mapTexture) {
    // Définir la portion de la texture à afficher (rectangle source)
    SDL_Rect srcRect;
    srcRect.x = static_cast<int>(viewport.x);  // Coordonnée x dans la texture
    srcRect.y = static_cast<int>(viewport.y);  // Coordonnée y dans la texture
    srcRect.w = viewport.width;                // Largeur de la portion de la texture
    srcRect.h = viewport.height;               // Hauteur de la portion de la texture

    // Définir la position sur l'écran (rectangle de destination)
    SDL_Rect destRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    // Afficher la texture
    SDL_RenderCopy(renderer, mapTexture, &srcRect, &destRect);
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

    // Initialiser SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Erreur SDL_image: " << IMG_GetError() << std::endl;
        return 1;
    }

// Charger la texture de la map
    SDL_Texture* mapTexture = IMG_LoadTexture(renderer, "img/map.png");
    if (!mapTexture) {
        std::cerr << "Erreur de chargement de l'image: " << IMG_GetError() << std::endl;
        return 1;
    }

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
        SDL_RenderClear(renderer);
        drawBackground(renderer, viewport, mapTexture);

        // Dessiner le fond avec dégradé bleu
        drawGradientBackground(renderer);

        int w,h = 10;
        SDL_Texture* img = IMG_LoadTexture(renderer, "../img/fish.png");
        SDL_QueryTexture(img, NULL, NULL, &w, &h);

        // Dessiner chaque poisson
        for (const Boid& boid : boids) {
            drawBoid(renderer, img, boid);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyTexture(mapTexture); // Libérer la texture de la map
    IMG_Quit(); // Quitter SDL_image

    SDL_Quit();

    return 0;
}