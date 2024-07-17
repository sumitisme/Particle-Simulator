#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

class Entity {
    static int count;
    int ObjectNumber;

    glm::vec3 velocity;
    // glm::vec3 color; // Might not do this one idk
    
    GLuint VertexArrayObject;
    GLuint VertexBufferObject;
    GLuint ElementBufferObject;
    unsigned int TransformLoc;

    double grav = 0.0000981f;

    float vertices[24] = {
         0.01f,  0.01f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.01f, -0.01f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.01f, -0.01f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.01f,  0.01f, 0.0f,  1.0f, 0.0f, 1.0f
    };
    unsigned int indices[6] = {
        0, 1, 3,
        1, 2, 3
    };

public:
    glm::vec3 position;

    Entity();

    void VertexSpec();

    void SetPos(float, float);

    void SetVelocity(float, float);

    float GetDist(glm::vec3);

    glm::vec3 GetNormal(glm::vec3);

    void Move();

    void Gravity();

    void Attract(glm::vec3);
    
    void DoFriction(float);

    void ShowPos();

    void SetEntity(GLuint, char*);

    void DrawEntity();

    void VertexSpecCleanup();

    ~Entity();
};
