#pragma once

#include <glad/glad.h>

class VertexSpec {
public:
    GLuint VertexArrayObject;
    GLuint VertexBufferObject;
    GLuint ElementBufferObject;

    VertexSpec();
    ~VertexSpec();
};
