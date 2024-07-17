#include "entity.h"
#include "glad/glad.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "definitions.h"

#include <iostream>
#include <math.h>

int Entity::count = -1;

Entity::Entity() {
    count++;
    ObjectNumber = count;
    
    std::cout << "Entity created\nNumber: " << ObjectNumber << std::endl;
    position.x = 0;
    position.y = 0;
    position.z = 0;

    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;

    VertexSpec();
}

void Entity::VertexSpec() {

    std::cout << ObjectNumber << " Vertex Specified\n";
    glCreateVertexArrays(1, &VertexArrayObject);
    glCreateBuffers(1, &VertexBufferObject);
    glCreateBuffers(1, &ElementBufferObject);

    glBindVertexArray(VertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);

    // Keeping the initial value for all entities same
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_DYNAMIC_DRAW
    );

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_DYNAMIC_DRAW
    );

    // ALL OF THE DATA
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*) 0
    );

    glEnableVertexAttribArray(0);

    // COLOR DATA
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*) (3 * sizeof(float)) // OFFSET
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);

    glDisableVertexAttribArray(1);

}

void Entity::SetPos(float a = 0, float b = 0) {
    // Only working with 2d atp
    position.x = a;
    position.y = b;
}

void Entity::SetVelocity(float a = 0, float b = 0) {
    velocity.x = a;
    velocity.y = b;
}

float Entity::GetDist(glm::vec3 OtherPos) {
    float dx = position.x - OtherPos.x;
    float dy = position.y - OtherPos.y;

    return sqrt((dx * dx) + (dy * dy));
}

glm::vec3 Entity::GetNormal(glm::vec3 OtherPos) {
    float dist = GetDist(OtherPos);
    if (dist == 0.0f) {
        dist = (float)2 / SCREEN_WIDTH;
    }
    
    float dx = OtherPos.x - position.x;
    float dy = OtherPos.y - position.y;

    glm::vec3 normal = glm::vec3(dx * (1 / dist), dy * (1 / dist), 0.0f); // The unit vector in the given direction
    return normal;
}

void Entity::Attract(glm::vec3 PosToAttract) {
    // I CANT GET THIS TO WORK!!!!
    float dist = GetDist(PosToAttract); // Need to verify this one
    glm::vec3 normal = GetNormal(PosToAttract);

    if (dist == 0.0f) {
        dist = (float)2 / SCREEN_WIDTH;
    }

    float tempx, tempy;
    tempx = dist * 2.0f * SCREEN_WIDTH;
    tempy = dist * 2.0f * SCREEN_HEIGHT;

    velocity.x += normal.x * 1 / (tempx * 1.5f);
    velocity.y += normal.y * 1 / (tempy * 1.5f);
}

void Entity::Gravity() {
    velocity.y -= grav;
}

void Entity::Move() {
    // Only looking at 2d again
    position.x += velocity.x;
    position.y += velocity.y;

    if(position.x <= -1.414f) {
        position.x = -1.414f;
    }
    if(position.x >= 1.414f) {
        position.x = 1.414f;
    }
    if(position.y <= -1.414f) {
        position.y = -1.414f;
    }
    if(position.y >= 1.414f) {
        position.y = 1.414f;
    }
}

void Entity::DoFriction(float amount) {
    velocity.x *= amount;
    velocity.y *= amount;
}

void Entity::ShowPos() {
    std::cout << ObjectNumber << " Initial Position: " << std::endl;
    std::cout << "x : " << position.x << std::endl;
    std::cout << "y : " << position.y << std::endl;
    std::cout << "z : " << position.z << std::endl;
}

void Entity::SetEntity(GLuint ShaderProgram, char* location) {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(position)); // Swizzeling (?) is allowed
    trans = glm::scale(trans, glm::vec3(0.3f, 0.3f, 1.0f));

    TransformLoc = glGetUniformLocation(ShaderProgram, "transform");
    glUniformMatrix4fv(TransformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void Entity::DrawEntity() {
    glBindVertexArray(VertexArrayObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Entity::VertexSpecCleanup() {
    std::cout << ObjectNumber << " Vertex data Cleaned up\n";

    glDeleteVertexArrays(1, &VertexArrayObject);
    glDeleteBuffers(1, &VertexBufferObject);
    glDeleteBuffers(1, &ElementBufferObject);
}

Entity::~Entity() {
    std::cout << ObjectNumber << " Entity Destroyed\n";
    VertexSpecCleanup();
}
