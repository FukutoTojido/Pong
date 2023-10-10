#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class Text
{
public:
    std::string text = "";
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect rect;
    TTF_Font *font;
    SDL_Renderer *renderer = NULL;

    int x;
    int y;

    Text(std::string, TTF_Font *, SDL_Renderer *, int, int);
    Text(){};

    void updateText(std::string);
    void clearText();

    ~Text();
};
