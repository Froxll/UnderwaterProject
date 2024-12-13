//
// Created by ethan on 04/12/2024.
//

#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

const int BUTTON_START_WIDTH = 256;
const int BUTTON_START_HEIGHT = 73;

const int BUTTON_PAUSE_WIDTH = 90;
const int BUTTON_PAUSE_HEIGHT = 41;

const int BUTTON_RESUME_WIDTH = 230;
const int BUTTON_RESUME_HEIGHT = 90;

const int BUTTON_STOP_WIDTH = 216;
const int BUTTON_STOP_HEIGHT = 91;

const int BUTTON_NEWGAME_WIDTH = 350;
const int BUTTON_NEWGAME_HEIGHT = 99;

using namespace std;

SDL_Texture* createTexture(SDL_Renderer* renderer, SDL_Window* window, const char* filePath);

bool showWelcomeScreen(SDL_Renderer* renderer, SDL_Window* window, string* playerName);

bool showPauseScreen(SDL_Renderer* renderer, SDL_Window* window);


#endif //WELCOMESCREEN_H
