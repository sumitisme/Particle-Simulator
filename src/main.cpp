#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>

// For OpenGL functions
#include <glad/glad.h>

// The functions for mathematical transformation
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include <iostream>
#include <windows.h>

#include "window.h"
#include "entity.h"
#include "shape.h"
#include "definitions.h"

bool IsRunning = true;
GLuint VertexArrayObject = 0;
GLuint VertexBufferObject = 0;
GLuint ElementBufferObject = 0;
GLuint ShaderProgram = 0;
GLuint VertexShader = 0;
GLuint FragmentShader = 0;

void VertexSpecification();
void CreateGraphicsPipeline();
void MainLoop(Window &);
void Draw();
void CleanUp();

const char* VertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec4 position;\n"
    "layout (location = 1) in vec3 vcolor;\n"

    "uniform mat4 transform;\n"

    "out vec3 ourColor;\n"
    "void main() {\n"
    "   gl_Position = transform * vec4(position.x, position.y, position.z, position.w);"
    "   ourColor = vcolor;\n"
    "}\0";

const char* FragmentShaderSource = 
    "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 color;\n"
    "void main() {\n"
    "   color = vec4(ourColor, 1.0f);\n"
    "}\0";

int main(int argc, char** argv) {
    
    Window win;

    VertexSpecification();

    CreateGraphicsPipeline();

    MainLoop(win); // Need to pass this class for buffer swapping

    CleanUp();

    win.cleanup();

    return 0;
}

void VertexSpecification() {

    glGenVertexArrays(1, &VertexArrayObject);
    glGenBuffers(1, &VertexBufferObject);
    glGenBuffers(1, &ElementBufferObject);

    glBindVertexArray(VertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_DYNAMIC_DRAW
    );

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_DYNAMIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void *)0
    );
    glEnableVertexAttribArray(0);

    // IMPORTANT!!!
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void *) (3 * sizeof(float)) // Offset!
    );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinding stuff
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void CreateGraphicsPipeline() {
    ShaderProgram = glCreateProgram();

    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
    glCompileShader(VertexShader);

    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
    glCompileShader(FragmentShader);

    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);

}

void MainLoop(Window &win) {
    
    Entity *entity;
    entity = new Circle[ParticleCount];
    
    while(IsRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                std::cout << "Window has been closed\n";
                IsRunning = false;
            }
        }

        Draw();
        SDL_GL_SwapWindow(win.win);
    }

    delete []entity;
}

// double ypos = 0;
// double motion = 0.0008;

void Draw() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // This is to change the color sinusoidally and stuff
    // START
    // float TimeValue = (double) SDL_GetTicks() / 1000;
    // float GreenValue = abs(sin(TimeValue)); // absolute to remove negative values
    // int VertexColorLocation = glGetUniformLocation(ShaderProgram, "VertexColor");
    // glUniform4f(VertexColorLocation, 0.0f, GreenValue, 0.0f, 1.0f);
    // FIN


    // ypos += motion;
    // if(ypos >= 1.0 || ypos <= -1.0) {
    //     motion = -motion;
    // }
    // glm::mat4 trans = glm::mat4(1.0f); // Identity matrix

    // Don't mess with the order. Atleast, of the translation and rotation
    // trans = glm::translate(trans, glm::vec3(0.0f, ypos, 0.0f));
    // trans = glm::rotate(trans, (float)SDL_GetTicks() / 500, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate about the z-axis
    // trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate about the z-axis
    // trans = glm::scale(trans, glm::vec3(0.1f, 0.1f, 0.1f));


    glUseProgram(ShaderProgram);

    unsigned int TransformLoc = glGetUniformLocation(ShaderProgram, "transform");

    // glUniformMatrix4fv(TransformLoc, 1, GL_FALSE, glm::value_ptr(trans));


    glBindVertexArray(VertexArrayObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void CleanUp() {
    glDeleteVertexArrays(1, &VertexArrayObject);
    glDeleteBuffers(1, &VertexBufferObject);
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}
