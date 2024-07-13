#pragma once

#include <SDL2/SDL.h>
#include "SDL2/SDL_video.h"
#include "definitions.h"

class Window {
    SDL_GLContext context;
public:
    SDL_Window* win; // This needs to be public for buffer swapping reasons
    Window(int scrw = SCREEN_WIDTH, int scrh = SCREEN_HEIGHT);

    void cleanup();
};
