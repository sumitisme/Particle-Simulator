#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL.h>

#include "entity.h"
#include "vertex.h"
#include "window.h"
#include "pipeline.h"
#include "definitions.h"

#include <glad/glad.h>

#include <iostream>

bool IsRunning = true;

void MainLoop(Window &, Pipeline &, VertexSpec &);
void PreDraw(Pipeline &);
void Draw(Pipeline &, VertexSpec &);

int main(int argv, char** args) {
    Window window; // Creating window

    VertexSpec VertexSpecification; // Creating Vertex Specification

    Pipeline gp; // Graphics Pipeline

    MainLoop(window, gp, VertexSpecification);

    return 0;
}

void MainLoop(Window &win, Pipeline &gp, VertexSpec &vs) {
    Entity entity;

    entity.ShowPos();
    entity.SetPos(0.4f, 0.2f);
    entity.SetVelocity(0.0f, -0.001f);

    while(IsRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                std::cout << "Window has been closed\n";
                IsRunning = false;
            }
        }
        PreDraw(gp);

        entity.Move();

        entity.SetEntity(gp.ShaderProgram, (char*) "transform");

        Draw(gp, vs);

        SDL_GL_SwapWindow(win.window);
    }
}

void PreDraw(Pipeline &gp) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Draw(Pipeline &gp, VertexSpec &vs) {
    glUseProgram(gp.ShaderProgram);

    glBindVertexArray(vs.VertexArrayObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vs.ElementBufferObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
