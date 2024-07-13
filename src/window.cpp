#include <SDL2/SDL.h>
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_video.h"

#include <iostream>
#include <glad/glad.h>

#include "window.h"

Window::Window(int scrw, int scrh) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL Video. SDL_Error : " << SDL_GetError();
    }

    win = SDL_CreateWindow("Particle Simulator", 
                           SDL_WINDOWPOS_UNDEFINED, 
                           SDL_WINDOWPOS_UNDEFINED, 
                           scrw, 
                           scrh, 
                           SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(win == NULL) {
        std::cout << "Failed to initialize SDL window\n";
        exit(-1);
    }
    else {
        std::cout << "Window initialized\n";
    }
    
    context = SDL_GL_CreateContext(win);

    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize glad\n";
        exit(-1);
    }
    else {
        std::cout << "Glad initialized\n";
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Window::cleanup() {
    SDL_DestroyWindow(win);
}
