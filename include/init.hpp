#ifndef INIT_HPP
#define INIT_HPP

#include <SDL3/SDL.h>

bool init(SDL_Window*& w, SDL_Renderer*& r);
void close(SDL_Window*& w, SDL_Renderer*& r);

#endif