// FOR COMPILING THE CODE
//
// go to location "project folder\src"
//
// --> make
// --> ..\build\prog


// 3rd party libraries
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_scancode.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_video.h"
#include <SDL2/SDL.h>

// Standard library
#include <math.h>
#include <iostream>

// User-defined libraries
#include "definitions.h"
#include "entity.h"

void initialize() {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL failed to initialize\n";
    }
    else {
        std::cout << "SDL video has initialized\n";
    }
}

void DrawCircle(int h, int k, int r, SDL_Renderer* renderer) {
    float x1, x2, y1, y2;

    float theta = 0;

    x1 = (float) h + r * cos(theta);
    y1 = (float) k + r * sin(theta);

    for(int i = 1; i <= MAX_NUM; i++) {
        x2 = float(h + r * cos((2 * PI) / MAX_NUM * i));
        y2 = float(k + r * sin((2 * PI) / MAX_NUM * i));

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
        SDL_RenderPresent(renderer);

        x1 = x2;
        y1 = y2;
    }
}

int main(int argc, char** argv) { // arrays and pointers are related

    initialize();

    // TODO STUFF: //SDL_Surface* surface = SDL_LoadBMP("../build/image/jpegbrick.bmp");

    SDL_Window* window = SDL_CreateWindow("Physics simulation", 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, // Defined in definitions.h
                                          SCREEN_HEIGHT, 
                                          SDL_WINDOW_SHOWN);

    if(window == NULL) {
        std::cout << "Error creating window. SDL_ERROR: " << SDL_GetError() << std::endl;
    }

    SDL_Renderer* renderer = nullptr;

    renderer = SDL_CreateRenderer(window, 
                                  -1, 
                                  SDL_RENDERER_ACCELERATED);

    // For the point
    float pos_x = (float)SCREEN_WIDTH / 2; // initial position of the point
    float pos_y = 0;
    float pvel = 1.0;

    SDL_Rect rect, rect2;

    float vel = 1.0;
    rect2.w = 25;
    rect2.h = 25;
    rect2.x = (float)SCREEN_WIDTH / 2;
    rect2.y = (float)SCREEN_HEIGHT / 2;

    bool IsRunning = true;
    while(IsRunning) {
        SDL_Event event;

        int mouse_x, mouse_y;

        Uint32 mousePos;

        mousePos = SDL_GetMouseState(&mouse_x, &mouse_y);

        rect.w = 20;
        rect.h = 20;
        rect.x = mouse_x - rect.w / 2;
        rect.y = mouse_y - rect.h / 2;

        SDL_SetRenderDrawColor(renderer, 
                               0, 
                               0, 
                               0, 
                               SDL_ALPHA_OPAQUE);

        SDL_RenderClear(renderer);

        // event loop
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                std::cout << "Window has been closed\n";
                IsRunning = false;
            }

            // This was a test
            // if(event.type == SDL_MOUSEMOTION) {
            //     std::cout << "Mouse has been moved\n";
            // }
            
            if(event.button.button == SDL_BUTTON_LEFT) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                DrawCircle(mouse_x, mouse_y, 10, renderer); // This will render a circle. This will only happen momentarily and this is a test.
            }
        }

        SDL_SetRenderDrawColor(renderer, 
                               255, 
                               255, 
                               255, 
                               SDL_ALPHA_OPAQUE); // Can use 255 here too. This is just something that was recommended by the documentation
        SDL_RenderDrawRect(renderer, &rect);

        if(rect2.y == SCREEN_HEIGHT - 25 && rect2.y > 0) {
            vel = -vel;
        }
        else if(rect2.y <= 0) {
            vel = abs(vel);
        }

        if(pos_y == SCREEN_HEIGHT && pos_y > 0) {
            pvel = -pvel;
        }
        else if(pos_y <= 0) {
            pvel = abs(pvel);
        }

        rect2.y += vel;
        pos_y += pvel;

        SDL_RenderDrawPoint(renderer, pos_x, pos_y);

        SDL_SetRenderDrawColor(renderer,
                               0,   // R
                               180, // G
                               180, // B
                               SDL_ALPHA_OPAQUE /* Opacity */);
        SDL_RenderDrawRect(renderer, &rect2);

        SDL_RenderPresent(renderer);

        SDL_Delay(DELAY);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
