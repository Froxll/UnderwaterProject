//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <iostream>
//
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//const int ENV_WIDTH = 1600;
//const int ENV_HEIGHT = 1200;
//
//void drawGradientBackground(SDL_Renderer* renderer) {
//    for (int y = 0; y < ENV_HEIGHT; y++) {
//        Uint8 blue = static_cast<Uint8>(255 * (1.0 - static_cast<float>(y) / ENV_HEIGHT));
//        SDL_SetRenderDrawColor(renderer, 0, 0, blue, 255);
//        SDL_RenderDrawLine(renderer, 0, y, ENV_WIDTH, y);
//    }
//}
//
//int main(int argc, char* argv[]) {
//    // Initialiser SDL
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cerr << "Erreur d'initialisation de SDL: " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    // Créer une fenêtre
//    SDL_Window* window = SDL_CreateWindow("BloubBloub les poissons",
//                                          SDL_WINDOWPOS_CENTERED,
//                                          SDL_WINDOWPOS_CENTERED,
//                                          WINDOW_WIDTH, WINDOW_HEIGHT,
//                                          SDL_WINDOW_FULLSCREEN);
//    if (window == nullptr) {
//        std::cerr << "Erreur de création de la fenêtre: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//        return 1;
//    }
//
//    int screenWidth, screenHeight;
//    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
//
//    //initialisation de sdl image
//    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
//        std::cerr << "Erreur lors de l'initialisation de SDL_image: " << IMG_GetError() << std::endl;
//        SDL_Quit();
//        return -1;
//    }
//
//    // Créer un renderer avec SDL_RENDERER_SOFTWARE
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
//    if (renderer == nullptr) {
//        std::cerr << "Erreur de création du renderer: " << SDL_GetError() << std::endl;
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }
//
//    // Charger l'image PNG
//    SDL_Surface* imageSurface = IMG_Load("../img/map.png");
//    if (imageSurface == nullptr) {
//        std::cerr << "Erreur lors du chargement de l'image PNG: " << IMG_GetError() << std::endl;
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        IMG_Quit();
//        SDL_Quit();
//        return -1;
//    }
//    // Créer une texture à partir de la surface
//    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
//    SDL_FreeSurface(imageSurface);  // Libérer la surface maintenant que la texture est créée
//    if (texture == nullptr) {
//        std::cerr << "Erreur lors de la création de la texture: " << SDL_GetError() << std::endl;
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        IMG_Quit();
//        SDL_Quit();
//        return 1;
//    }
//
//
//    // Boucle principale
//    bool running = true;
//    SDL_Event event;
//    int offsetX = 0, offsetY = 0; // Offsets pour le défilement
//
//    while (running) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//            // Gérer les événements de clavier pour le défilement
//            if (event.type == SDL_KEYDOWN) {
//                switch (event.key.keysym.sym) {
//                    case SDLK_LEFT: offsetX -= 10; break;
//                    case SDLK_RIGHT: offsetX += 10; break;
//                    case SDLK_UP: offsetY -= 10; break;
//                    case SDLK_DOWN: offsetY += 10; break;
//                }
//            }
//        }
//
//        // Limiter les offsets pour ne pas sortir de l'environnement
//        if (offsetX < 0) offsetX = 0;
//        if (offsetY < 0) offsetY = 0;
//        if (offsetX > ENV_WIDTH - WINDOW_WIDTH) offsetX = ENV_WIDTH - WINDOW_WIDTH;
//        if (offsetY > ENV_HEIGHT - WINDOW_HEIGHT) offsetY = ENV_HEIGHT - WINDOW_HEIGHT;
//
//        // Effacer l'écran
//        if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) != 0) {
//            std::cerr << "Erreur de SDL_SetRenderDrawColor: " << SDL_GetError() << std::endl;
//        }
//        if (SDL_RenderClear(renderer) != 0) {
//            std::cerr << "Erreur de SDL_RenderClear: " << SDL_GetError() << std::endl;
//        }
//
//        // Définir la zone de découpage
//        SDL_Rect viewport = { offsetX, offsetY, screenWidth, screenHeight };
//        if (SDL_RenderSetClipRect(renderer, &viewport) != 0) {
//            std::cerr << "Erreur de SDL_RenderSetClipRect: " << SDL_GetError() << std::endl;
//        }
//
//        // Dessiner le fond en dégradé
//        drawGradientBackground(renderer);
//
//        // Réinitialiser la zone de découpage
//        if (SDL_RenderSetClipRect(renderer, nullptr) != 0) {
//            std::cerr << "Erreur de SDL_RenderSetClipRect: " << SDL_GetError() << std::endl;
//        }
//
//        // Présenter le rendu
//        /*
//        SDL_Rect rect = {100, 100, 200, 100};
//        SDL_RenderFillRect(renderer, &rect);
//         */
//        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
//        SDL_RenderPresent(renderer);
//
//    }
//
//    // Détruire le renderer et la fenêtre, et quitter SDL
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//
//}
