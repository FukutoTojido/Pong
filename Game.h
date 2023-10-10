#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "Object.h"
#include "Ball.h"
#include "Text.h"
#include <time.h>

class Game
{
private:
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;
    Text *textLeft = NULL;
    Text *textRight = NULL;
    Object *player1, *player2;
    Object *background;
    Ball *ball;
    TTF_Font *font;

public:
    inline static int SCREEN_WIDTH;
    inline static int SCREEN_HEIGHT;
    inline static int scoreLeft = 0;
    inline static int scoreRight = 0;

    Game();
    Game(int, int);

    int init(void);
    void loop(void);
    void update(int);

    ~Game();
};
