#pragma once

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700

#define PI 3.1514

const float vertices[] = {
     0.1f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.1f, -0.1f, 0.0f,  0.0f, 1.0f, 0.0f,
    -0.1f, -0.1f, 0.0f,  0.0f, 0.0f, 1.0f,
    -0.1f,  0.1f, 0.0f,  1.0f, 0.0f, 1.0f
};

const unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};
