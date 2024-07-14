#pragma once

#include "definitions.h"
#include <glad/glad.h>

class Entity {
    Object *foo;
    GLuint ShaderProgram;

public:
    Entity(float x = 0, float y = 0);

    virtual void SetPos(float &x, float &y);
    virtual float getDist(glm::vec3);
    virtual glm::vec3 getNormal(glm::vec3 otherPos);

    virtual void Attract(glm::vec3 PosToAttract, float multiplier);
    virtual void Friction(float amount);
    virtual void Move();
    virtual void SetEntity(GLuint ShaderProgram, char *location);

    virtual ~Entity();
};
