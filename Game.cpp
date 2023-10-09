#include "Game.h"

Game::Game()
{
    Game::SCREEN_WIDTH = 1280;
    Game::SCREEN_WIDTH = 720;
}

Game::Game(int w, int h)
{
    Game::SCREEN_WIDTH = w;
    Game::SCREEN_HEIGHT = h;
}

int Game::init()
{
    // Initialize SDL and Guarding
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Cannot initialize SDL: " << SDL_GetError() << '\n';
        return -1;
    }

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "Cannot initialize image loader: " << IMG_GetError() << '\n';
        return -1;
    }

    // Initialize TTF
    if (TTF_Init() < 0)
    {
        std::cout << "Cannot initialize SDL_ttf: " << TTF_GetError() << '\n';
        return -1;
    }

    // Create window
    this->window = SDL_CreateWindow(
        "Pong 180fps",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Game::SCREEN_WIDTH,
        Game::SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (!window)
    {
        std::cout << "Cannot create window" << '\n';
        return -1;
    }

    // Create font
    font = TTF_OpenFont("./font.ttf", 24);
    if (!font)
    {
        std::cout << "Cannot load font: " << TTF_GetError() << '\n';
        return -1;
    }

    this->textLeft = TTF_RenderText_Solid(font, "0", {0xff, 0xff, 0xff});
    this->textRight = TTF_RenderText_Solid(font, "0", {0xff, 0xff, 0xff});

    // Get window surface and fill
    this->surface = SDL_GetWindowSurface(this->window);
    SDL_FillRect(this->surface, NULL, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0));
    SDL_UpdateWindowSurface(this->window);

    // Load background
    this->background = new Object(this->surface->format, "./background.png", 0, 0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT);

    // Load image and set positon
    this->player1 = new Object(this->surface->format, 0, Game::SCREEN_HEIGHT / 2 - 50, 10, 100);
    this->player2 = new Object(this->surface->format, Game::SCREEN_WIDTH - 10, Game::SCREEN_HEIGHT / 2 - 50, 10, 100);
    this->ball = new Ball(this->surface->format);

    return 0;
}

void Game::loop()
{
    try
    {
        // Main loop
        SDL_Event e;
        bool quit = false;
        uint64_t time = SDL_GetTicks64();
        uint64_t pauseTime = 0;

        while (!quit)
        {
            uint64_t currentTime = SDL_GetTicks64();
            uint64_t delta_t = currentTime - time;

            while (SDL_PollEvent(&e))
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    quit = true;
                }
            }

            if (pauseTime != 0 && currentTime - pauseTime > 100)
                pauseTime = 0;

            if (pauseTime == 0)
            {
                const Uint8 *keys = SDL_GetKeyboardState(NULL);

                if (keys[SDL_SCANCODE_UP])
                    this->player2->updatePos(this->player2->x, this->player2->y - this->player2->velocity * delta_t / 1000.0);
                if (keys[SDL_SCANCODE_DOWN])
                    this->player2->updatePos(this->player2->x, this->player2->y + this->player2->velocity * delta_t / 1000.0);
                if (keys[SDL_SCANCODE_W])
                    this->player1->updatePos(this->player1->x, this->player1->y - this->player1->velocity * delta_t / 1000.0);
                if (keys[SDL_SCANCODE_S])
                    this->player1->updatePos(this->player1->x, this->player1->y + this->player1->velocity * delta_t / 1000.0);

                this->ball->update(delta_t, this->player1, this->player2);
                this->update(delta_t);

                if (this->ball->reachedBorder)
                {
                    delete this->ball;
                    this->player1->updatePos(0, Game::SCREEN_HEIGHT / 2 - 50);
                    this->player2->updatePos(Game::SCREEN_WIDTH - 10, Game::SCREEN_HEIGHT / 2 - 50);
                    this->update(delta_t);

                    this->ball = new Ball(this->surface->format);
                    pauseTime = currentTime;
                }
            }

            time = currentTime;
        }
    }
    catch (const char *error)
    {
        std::cout << error << '\n';
    }
}

void Game::update(int delta_t)
{
    // Clear everything
    // SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format, 0x0, 0x0, 0x0));
    SDL_BlitScaled(this->background->surface, NULL, this->surface, &(this->background->pos));

    // Do something here
    SDL_BlitScaled(this->player1->surface, NULL, this->surface, &(this->player1->pos));
    SDL_BlitScaled(this->player2->surface, NULL, this->surface, &(this->player2->pos));

    if (!this->ball->reachedBorder)
        SDL_BlitScaled(this->ball->surface, NULL, this->surface, &(this->ball->pos));

    // Update window
    SDL_UpdateWindowSurface(this->window);
}

Game::~Game()
{
    // End process
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}