#include <SDL3/SDL.h>

#include "include/init.hpp"
#include "include/math.hpp"
#include "include/camera.hpp"
#include "include/rast.hpp"
#include "include/geometry.hpp"
#include "include/renderer.hpp"
#include "include/parseobj.hpp"

#include <memory>
#include <cstdint>
#include <array>
#include <iostream>
#include <vector>

#include <algorithm>


int main()
{
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};

    if(!init(window, renderer))
    {
        SDL_Log("Could not initialize! SDL Error: %s\n", SDL_GetError());
    }

    bool running {true};
    SDL_Event e;

    Camera camera (
        Vector3(0,0,0),
        80.0f,
        RAST::SCREEN_WIDTH/(float)RAST::SCREEN_HEIGHT
    );

    Mesh mesh {getMeshFromObj("OBJ format/grenade-b.obj")};
    Renderable renderable{
        &mesh, 
        Transform(
            Vector3(5, 0, 2),
            Vector3(2, 2, 2),
            fromAxisAngle(Vector3(1, 2, 3), 60)
        )
    };

    Renderer m_renderer(window, renderer, &camera);

    while (running)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        const bool *keyStates = SDL_GetKeyboardState(nullptr);

        if (keyStates[SDL_SCANCODE_B])
        {
            Quaternion yawQ {fromAxisAngle(Vector3(0, 1, 0), .5f)};
            renderable.transform.rotation = (renderable.transform.rotation * yawQ).normalize();
        }
        takeInput(keyStates, camera);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        m_renderer.RenderObject(renderable);

        SDL_RenderPresent(renderer);
    }

    close(window, renderer);
}