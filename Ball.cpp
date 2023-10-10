#include "Ball.h"
#include "Game.h"

Ball::Ball(SDL_Renderer *renderer, SDL_PixelFormat *fmt) : Object(renderer, fmt, Game::SCREEN_WIDTH / 2 - 5, Game::SCREEN_HEIGHT / 2 - 5, 10, 10)
{
    // Randomize Direction Vector for BALL!
    bool rand_x = rand() & 1;
    bool rand_y = rand() & 1;

    double vec_x = ((double)rand() / (RAND_MAX)) * (rand_x * 1 + !rand_x * -1);
    double vec_y = ((double)rand() / (RAND_MAX)) * (rand_y * 1 + !rand_y * -1);

    while (abs(vec_x) / abs(vec_y) < 0.577 || abs(vec_x) / abs(vec_y) > 1.73)
    {
        vec_x = ((double)rand() / (RAND_MAX)) * (rand_x * 1 + !rand_x * -1);
        vec_y = ((double)rand() / (RAND_MAX)) * (rand_y * 1 + !rand_y * -1);
    }

    double length = hypot(vec_x, vec_y);

    this->directionVector[0] = vec_x / length;
    this->directionVector[1] = vec_y / length;
    this->setCorners(Game::SCREEN_WIDTH / 2 - 5, Game::SCREEN_HEIGHT / 2 - 5);

    SDL_DestroyTexture(this->texture);
    SDL_FillRect(this->surface, NULL, SDL_MapRGB(fmt, 0xFF, 0x00, 0x00));
    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
}

void Ball::update(double delta_t, Object *player1, Object *player2)
{
    double new_x = this->x + this->directionVector[0] * this->velocity * delta_t / 1000.0;
    double new_y = this->y + this->directionVector[1] * this->velocity * delta_t / 1000.0;

    this->setCorners(new_x, new_y);

    if (new_x > Game::SCREEN_WIDTH - 10 || new_x < 0)
    {
        this->reachedBorder = true;

        if (new_x > Game::SCREEN_WIDTH - 10)
            Game::scoreLeft += 1;

        if (new_x < 0)
            Game::scoreRight += 1;

        return;
    }

    if (new_y > Game::SCREEN_HEIGHT - 10 || new_y < 0)
    {
        this->directionVector[1] *= -1;
        return;
    }

    if (this->collide(player1, player2))
        return;

    this->x = new_x;
    this->y = new_y;

    this->pos.x = round(this->x);
    this->pos.y = round(this->y);
}

bool Ball::collide(Object *player1, Object *player2)
{
    // Check for player1 collision
    for (double *corner : this->corners)
    {
        if (corner[0] >= player1->x && corner[0] <= player1->x + 10)
        {
            if (corner[1] >= player1->y && corner[1] <= player1->y + 100)
            {
                this->directionVector[0] *= -1;
                // this->directionVector[1] *= -1;

                this->x = player1->x + 10;
                this->pos.x = round(this->x);

                return true;
            }
        }
    }

    // Check for player2 collision
    for (double *corner : this->corners)
    {
        if (corner[0] >= player2->x && corner[0] <= player2->x + 10)
        {
            if (corner[1] >= player2->y && corner[1] <= player2->y + 100)
            {
                this->directionVector[0] *= -1;
                // this->directionVector[1] *= -1;

                this->x = player2->x - 10;
                this->pos.x = round(this->x);

                return true;
            }
        }
    }

    return false;
}

void Ball::setCorners(double x, double y)
{
    this->corners[0][0] = x;
    this->corners[0][1] = y;

    this->corners[1][0] = x + 10;
    this->corners[1][1] = y;

    this->corners[2][0] = x + 10;
    this->corners[2][1] = y + 10;

    this->corners[3][0] = x;
    this->corners[3][1] = y + 10;
}