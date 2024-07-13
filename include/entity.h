#pragma once

#include "definitions.h"

class Entity {
    Object *foo;

public:
    Entity(float x = 0, float y = 0);

    virtual float getDist(glm::vec3);
    virtual glm::vec3 getNormal(glm::vec3 otherPos);

    virtual void Attract(glm::vec3 PosToAttract, float multiplier);
    virtual void Friction(float amount);
    virtual void Move();

    virtual ~Entity();
};
