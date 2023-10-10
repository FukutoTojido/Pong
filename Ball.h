#pragma once

#include "Object.h"
#include <time.h>

class Ball : public Object
{
public:
    const int velocity = 1000;
    double directionVector[2] = {0, 0};
    bool reachedBorder = false;
    double corners[4][2]; // Top left, Top right, Bottom right, Bottom left

    Ball(SDL_Renderer *, SDL_PixelFormat *);

    void update(double, Object *, Object *);
    bool collide(Object *, Object *);
    void setCorners(double, double);
};