#include "entity.h"
#include "definitions.h"
#include "glm/ext/vector_float3.hpp"

#include <math.h>
// glm has already been declared in entity.h so no need to do it again

Entity::Entity(float x, float y) {
    foo -> Mass = 1.0f;
    foo -> Position = glm::vec3(x, y, 0.0f);
    foo -> Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    foo -> Force = glm::vec3(0.0f, foo -> Mass * -9.81f, 0.0f);
}

float Entity::getDist(glm::vec3 otherPos) {
    const float dx = foo -> Position.x - otherPos.x;
    const float dy = foo -> Position.y - otherPos.y;

    return sqrt((dx * dx) + (dy * dy));
}

glm::vec3 Entity::getNormal(glm::vec3 otherPos) {
    float dist = getDist(otherPos);

    if(dist == 0.0f) {
        dist = 1;
    }

    const float dx = foo -> Position.x - otherPos.x;
    const float dy = foo -> Position.y - otherPos.y;
    glm::vec3 normal = glm::vec3(dx * (1 / dist), dy * (1 / dist), 0);
    return normal;
}

void Entity::Attract(glm::vec3 PosToAttract, float multiplier) {
    float dist = fmax(getDist(PosToAttract), 0.5);
    glm::vec3 normal = getNormal(PosToAttract);

    // Credits to codemaker4(?) for these portions

    foo -> Velocity.x -= normal.x / dist;
    foo -> Velocity.y -= normal.y / dist;

}

void Entity::Friction(float amount) {
    foo -> Velocity.x *= amount;
    foo -> Velocity.y *= amount;
}

void Entity::Move() {
    foo -> Position.x += foo -> Velocity.x;
    foo -> Position.y += foo -> Velocity.y;
    if(foo -> Position.x < 0) {
        foo -> Position.x += SCREEN_WIDTH;
    }
    if(foo -> Position.x >= SCREEN_WIDTH) {
        foo -> Position.x -= SCREEN_WIDTH;
    }
    if(foo -> Position.y < 0) {
        foo -> Position.y += SCREEN_HEIGHT;
    }
    if(foo -> Position.y >= SCREEN_HEIGHT) {
        foo -> Position.y -= SCREEN_HEIGHT;
    }
}

Entity::~Entity() {
    delete foo;
}
