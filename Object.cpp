#include "Game.h"
#include "Object.h"

Object::Object(SDL_Renderer* renderer, SDL_PixelFormat *fmt, int x, int y, int w, int h)
{
    try
    {
        // Create surface
        SDL_Surface *ret = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        if (!ret)
            throw "Cannot optimize image";

        this->surface = ret;
        SDL_FillRect(ret, NULL, SDL_MapRGB(fmt, 0xFF, 0xFF, 0xFF));

        this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
        this->pos.x = x;
        this->pos.y = y;
        this->pos.w = w;
        this->pos.h = h;

        this->x = x;
        this->y = y;

    }
    catch (const char *error)
    {
        std::cout << error << ": " << IMG_GetError() << '\n';
    }
}

Object::Object(SDL_Renderer* renderer, SDL_PixelFormat *fmt, std::string path, int x, int y, int w, int h)
{
    try
    {
        // Load Image
        SDL_Surface *loaded = IMG_Load(path.c_str());
        if (!loaded)
            throw "Cannot load image";

        // Convert to screen format
        SDL_Surface *ret = SDL_ConvertSurface(loaded, fmt, 0);
        if (!ret)
            throw "Cannot optimize image";

        // Free loaded
        SDL_FreeSurface(loaded);

        this->surface = ret;
        this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
        this->pos.x = x;
        this->pos.y = y;
        this->pos.w = w;
        this->pos.h = h;

        this->x = x;
        this->y = y;
    }
    catch (const char *error)
    {
        std::cout << error << ": " << IMG_GetError() << '\n';
    }
}

void Object::updatePos(double x, double y)
{
    if (x > Game::SCREEN_WIDTH - this->pos.w|| x < 0)
        return;

    if (y > Game::SCREEN_HEIGHT - this->pos.h || y < 0)
        return;

    if (x)
        this->x = x;

    if (y)
        this->y = y;

    this->pos.x = round(this->x);
    this->pos.y = round(this->y);
}

Object::~Object()
{
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
}