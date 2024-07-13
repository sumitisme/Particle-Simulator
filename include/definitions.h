#pragma once

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600 

#include <glm/glm.hpp>

struct Object {
    glm::vec3 Position;
    glm::vec3 Velocity;
    glm::vec3 Force;
    float Time;
    float Mass;
};

const float vertices[] = {
    // position         // color
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 1.0f,
};

const unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

const int ParticleCount = 100;
