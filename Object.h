#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <iostream>
#include <string>

class Object
{
private:
public:
    SDL_Surface *surface = NULL;
    SDL_Rect pos;
    SDL_Texture *texture = NULL;

    double x;
    double y;

    const int velocity = 1000;

    Object(){};
    Object(SDL_Renderer*, SDL_PixelFormat *, int, int, int, int);
    Object(SDL_Renderer*,SDL_PixelFormat *, std::string, int, int, int, int);

    void updatePos(double, double);

    ~Object();
};