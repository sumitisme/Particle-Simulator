#include "entity.h"
#include "glad/glad.h"

#include <iostream>

Entity::Entity() {
    std::cout << "Entity created\n";
    position.x = 0;
    position.y = 0;
    position.z = 0;

    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
}

void Entity::SetPos(float a, float b) {
    // Only working with 2d atp
    position.x = a;
    position.y = b;
}

void Entity::SetVelocity(float a, float b) {
    velocity.x = a;
    velocity.y = b;
}

void Entity::Move() {
    // Only looking at 2d again
    position.x += velocity.x;
    position.y += velocity.y;

    if(position.x < -1.0f) {
        position.x += 2.0f;
    }
    if(position.x >= 1.0f) {
        position.x -= 2.0f;
    }
    if(position.y < -1.0f) {
        position.y += 2.0f;
    }
    if(position.y >= 1.0f) {
        position.y -= 2.0f;
    }
}

void Entity::ShowPos() {
    std::cout << "x : " << position.x << std::endl;
    std::cout << "y : " << position.y << std::endl;
    std::cout << "z : " << position.z << std::endl;
}

void Entity::SetEntity(GLuint ShaderProgram, char* location) {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(position.x, position.y, position.z)); // Swizzeling (?) is allowed

    unsigned int TransformLoc = glGetUniformLocation(ShaderProgram, "transform");
    glUniformMatrix4fv(TransformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

Entity::~Entity() {
    std::cout << "Entity Destroyed\n";
}
