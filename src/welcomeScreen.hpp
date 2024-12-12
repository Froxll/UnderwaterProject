//
// Created by ethan on 04/12/2024.
//

#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

const int BUTTON_WIDTH = 256;
const int BUTTON_HEIGHT = 73;

using namespace std;

SDL_Texture* createTexture(SDL_Renderer* renderer, SDL_Window* window, const char* filePath);

bool showWelcomeScreen(SDL_Renderer* renderer, SDL_Window* window, string* playerName);



#endif //WELCOMESCREEN_H
