//
// Created by ethan on 04/12/2024.
//

#include "screensManager.hpp"

SDL_Texture* createTexture(SDL_Renderer* renderer, SDL_Window* window, const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface) {
        std::cerr << "Erreur de chargement de l'image: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return nullptr;
    }

    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!buttonTexture) {
        std::cerr << "Erreur de création de la texture: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return nullptr;
    }

    return buttonTexture;

}



bool showWelcomeScreen(SDL_Renderer* renderer, SDL_Window* window, string* playerName) {
    SDL_Event event;
    bool running = true;
    bool startGame = false;
    *playerName = "";

    SDL_Texture* buttonTexture = createTexture(renderer, window, "../img/assets/New_Game.png");
    if (!buttonTexture) {
        SDL_Log("Erreur : Impossible de charger la texture du bouton !");
        return false;
    }

    SDL_Texture* backgroundTexture = createTexture(renderer, window, "../img/Background_WelcomeScreen.jpg");
    if (!backgroundTexture) {
        SDL_Log("Erreur : Impossible de charger la texture de l'arrière-plan !");
        SDL_DestroyTexture(buttonTexture);
        return false;
    }

    SDL_Texture* titleTexture = createTexture(renderer, window, "../img/Fish_Esquive.png");
    if (!titleTexture) {
        SDL_Log("Erreur : Impossible de charger la texture du titre !");
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(backgroundTexture);
        return false;
    }

    if (TTF_Init() == -1) {
        SDL_Log("Erreur : Impossible d'initialiser SDL_ttf : %s", TTF_GetError());
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyTexture(titleTexture);
        return false;
    }

    TTF_Font* font = TTF_OpenFont("../fonts/arial.ttf", 24);
    if (!font) {
        SDL_Log("Erreur : Impossible de charger la police : %s", TTF_GetError());
        TTF_Quit();
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyTexture(titleTexture);
        return false;
    }

    SDL_Color textColor = {255, 255, 255, 255}; // Blanc

    SDL_Rect startButton = {270, 400, BUTTON_START_WIDTH, BUTTON_START_HEIGHT};
    SDL_Rect title = {300, 40, 210, 181};
    SDL_Rect backgroundRect = {0, 0, 800, 600};
    SDL_Rect inputBox = {200, 300, 400, 50};

    SDL_StartTextInput();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (x >= startButton.x && x <= startButton.x + BUTTON_START_WIDTH &&
                    y >= startButton.y && y <= startButton.y + BUTTON_START_HEIGHT) {
                    startGame = true;
                    running = false;
                }
            } else if (event.type == SDL_TEXTINPUT) {
                if (playerName->length() < 16) {
                    *playerName += event.text.text;
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && !playerName->empty()) {
                    playerName->pop_back();
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    // ça fait rien
                }
            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, backgroundTexture, nullptr, &backgroundRect);

        SDL_RenderCopy(renderer, titleTexture, nullptr, &title);

        SDL_RenderCopy(renderer, buttonTexture, nullptr, &startButton);

        SDL_SetRenderDrawColor(renderer, 137, 125, 167, 255); // Gris foncé pour le fond du champ
        SDL_RenderFillRect(renderer, &inputBox);

        if (!playerName->empty()) {
            SDL_Surface* textSurface = TTF_RenderText_Blended(font, playerName->c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            int textWidth = textSurface->w;
            int textHeight = textSurface->h;

            SDL_Rect textRect;
            textRect.x = inputBox.x + (inputBox.w - textWidth) / 2;
            textRect.y = inputBox.y + (inputBox.h - textHeight) / 2;
            textRect.w = textWidth;
            textRect.h = textHeight;

            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(titleTexture);

    return startGame;
}

