#include <iostream>

#include "pipeline.h"
#include "glad/glad.h"

const char* VertexShaderSource = 
    "#version 410 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"

    "uniform mat4 transform;\n"

    "out vec3 OurCol;\n"
    "void main() {\n"
    "   gl_Position = transform * vec4(position.x, position.y, position.z, 1.0f);\n"
    "   OurCol = color;\n"
    "}\0";

const char* FragmentShaderSource = 
    "#version 410 core\n"
    "in vec3 OurCol;\n"
    "out vec4 color;\n"

    "void main() {\n"
    "   color = vec4(OurCol.x, OurCol.y, OurCol.z, 1.0f);\n"
    "}\0";

Pipeline::Pipeline() {
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

Pipeline::~Pipeline() {
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    glDeleteProgram(ShaderProgram);
}
