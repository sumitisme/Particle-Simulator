#include "window.h"
#include "SDL2/SDL_video.h"
#include "definitions.h"
#include <iostream>

Window::Window() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL\n";
        exit(-1);
    }

    else {
        std::cout << "SDL video has been initialized\n";
    }

    window = SDL_CreateWindow("Particle Simulator", 
                           SDL_WINDOWPOS_UNDEFINED, 
                           SDL_WINDOWPOS_UNDEFINED, 
                           SCREEN_WIDTH, 
                           SCREEN_HEIGHT, 
                           SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(window == NULL) {
        std::cout << "Window failed to create\n";
    }
    else {
        std::cout << "Window has been created\n";
    }
    
    context = SDL_GL_CreateContext(window);

    if(context == NULL) {
        std::cout << "GL context failed to be created\n";
    }
    else {
        std::cout << "GL context has been created\n";
    }

    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "Glad failed to load\n";
        exit(-1);
    }

    else {
        std::cout << "Glad has been initialized\n";
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
