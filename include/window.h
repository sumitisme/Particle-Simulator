#pragma once

#include "SDL2/SDL_video.h"
#include <SDL2/SDL.h>

#include <glad/glad.h>

class Window {
    SDL_GLContext context;
public:
    SDL_Window* window; 
    Window();
    ~Window();
};
