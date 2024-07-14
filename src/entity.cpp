#include "entity.h"
#include "SDL2/SDL_timer.h"
#include "definitions.h"

#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <math.h>

// Entity::Entity() {
//  int temppx = rand() % SCREEN_WIDTH;
//  int temppy = rand() % SCREEN_HEIGHT;
//  int tempvx = (rand() % 200) - 100;
//  int tempvy = (rand() % 200) - 100;

//  foo -> Position.x = (float)temppx / SCREEN_WIDTH;
//  foo -> Position.y = (float)temppy / SCREEN_HEIGHT;
//  foo -> Velocity.x = (float)tempvx;
//  foo -> Velocity.y = (float)tempvy;
// }

Entity::Entity(float x, float y) {
    foo -> Mass = 1.0f; // This is currently USELESS
    foo -> Position = glm::vec3(x, y, 0.0f);
    foo -> Velocity = glm::vec3(0.1f, 0.1f, 0.0f);
    foo -> Force = glm::vec3(0.0f, foo -> Mass * -9.81f, 0.0f); // This too is currently USELESS
}

void Entity::SetPos(float &x, float &y) {
    foo -> Position = glm::vec3(x, y, 0.0f);
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
        foo -> Position.x += 1.0f;
    }
    if(foo -> Position.x >= 1.0f) {
        foo -> Position.x -= 1.0f;
    }
    if(foo -> Position.y < 0) {
        foo -> Position.y += 1.0f;
    }
    if(foo -> Position.y >= 1.0f) {
        foo -> Position.y -= 1.0f;
    }
}

void Entity::SetEntity(GLuint ShaderProgram, char* location) {
    glm::mat4 trans = glm::mat4(1.0f); // Identity matrix
    trans = glm::translate(trans, glm::vec3(foo -> Position.x, foo -> Position.y, foo -> Position.z));
    trans = glm::rotate(trans, (float)SDL_GetTicks() / 500, glm::vec3(0.0f, 0.0f, 1.0f)); // Let's not make it rotate for now.
    trans = glm::scale(trans, glm::vec3(0.2f, 0.2f, 0.2f));

    unsigned int TransformLoc = glGetUniformLocation(ShaderProgram, "transform");
    glUniformMatrix4fv(TransformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

Entity::~Entity() {
    delete foo;
}
