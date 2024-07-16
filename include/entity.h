#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

class Entity {
    glm::vec3 position;
    glm::vec3 velocity;
    // glm::vec3 color; // Might not do this one idk
public:
    Entity();

    void SetPos(float a, float b);

    void SetVelocity(float a, float b);

    float GetDist(glm::vec3 OtherPos);

    void Move();

    void ShowPos();

    void SetEntity(GLuint ShaderProgram, char* location);

    ~Entity();
};
