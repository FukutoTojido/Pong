#include "Text.h"
#include "Game.h"

Text::Text(std::string text, TTF_Font *font, SDL_Renderer *renderer, int x, int y)
{
    this->text = text;
    this->font = font;
    this->renderer = renderer;
    this->x = x;
    this->y = y;

    this->updateText(this->text);
}

void Text::updateText(std::string text)
{
    this->clearText();
    this->text = text;

    SDL_Color color = {0xFF, 0xFF, 0xFF};
    this->surface = TTF_RenderText_Solid(this->font, text.c_str(), color);
    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(this->texture, NULL, NULL, &texW, &texH);

    this->rect = {this->x, this->y, texW, texH};
};

void Text::clearText()
{
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
}

Text::~Text()
{
    this->clearText();
}