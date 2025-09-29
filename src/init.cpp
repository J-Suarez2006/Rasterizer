#include "../include/init.hpp"
#include "../include/rast.hpp"

bool init(SDL_Window*& w, SDL_Renderer*& r)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Could not initialize video! SDL error: %s\n", SDL_GetError());
        return false;
    }

    w = SDL_CreateWindow(
        "Rasterizer",
        RAST::SCREEN_WIDTH,
        RAST::SCREEN_HEIGHT,
        0
    );

    if (w == nullptr)
    {
        SDL_Log("Could not initialize window! SDL error: %s\n", SDL_GetError());
        return false;
    }

    r = SDL_CreateRenderer(w, NULL);

    if (r == nullptr)
    {
        SDL_Log("Could not initialize SDL renderer! SDL error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close(SDL_Window*& w, SDL_Renderer*& r)
{
    SDL_DestroyRenderer(r);
    r = nullptr;

    SDL_DestroyWindowSurface(w);
    w = nullptr;

    SDL_Quit();
}