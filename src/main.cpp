#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>

#include "entity.h"
#include "window.h"
#include "pipeline.h"
#include "definitions.h"

#include <glad/glad.h>

#include <iostream>

bool IsRunning = true;

void MainLoop(Window &, Pipeline &);
void PreDraw(Pipeline &);

int main(int argv, char** args) {
    Window window; // Creating window

    Pipeline gp; // Graphics Pipeline

    MainLoop(window, gp);

    return 0;
}

void MainLoop(Window &win, Pipeline &gp) {
    int quantity = NO_OF_PARTICLES;

    // std::cout << "Enter the number of entities:\n";
    // std::cin >> quantity;

    Entity *entity;
    entity = new Entity[quantity];

    // Initialization
    for(int i = 0; i < quantity; i++) {
        entity[i].SetPos(-0.95f + (float) i / 10, 0.2f);
        entity[i].ShowPos();
        entity[i].SetVelocity(0.0f, 0.0f);
    }
    float fmx = 0.0f, fmy = 0.0f; // Normalized values
    int mx = 0, my = 0;

    while(IsRunning) {
        SDL_Event event;
        Uint32 buttons;
        glm::vec3 MousePos;

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                std::cout << "Window has been closed\n";
                IsRunning = false;
            }
            if(event.button.button == SDL_BUTTON_LEFT) {
                buttons = SDL_GetMouseState(&mx, &my);
                fmx = -1.0 + 2.0 * mx / SCREEN_WIDTH;
                fmy = 1.0 - 2.0 * my / SCREEN_HEIGHT;
            }
        }

        MousePos = glm::vec3(fmx, fmy, 0.0f);

        PreDraw(gp);

        for(int i = 0; i < NO_OF_PARTICLES; i++) {
            entity[i].Attract(MousePos);
            entity[i].DoFriction(0.99);
            entity[i].Move();
        }

        glUseProgram(gp.ShaderProgram);

        for(int i = 0; i < quantity; i++) {
            entity[i].SetEntity(gp.ShaderProgram, (char*) "transform");
            entity[i].DrawEntity();
        }

        SDL_GL_SwapWindow(win.window);
    }

    delete []entity;
}

void PreDraw(Pipeline &gp) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
