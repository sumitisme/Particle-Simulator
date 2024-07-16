#pragma once
#include <glad/glad.h>

class Pipeline {
    GLuint VertexShader;
    GLuint FragmentShader;
public:
    GLuint ShaderProgram;
    
    Pipeline();
    ~Pipeline();
};
