#pragma once

#include "entity.h"

class Rectangle : public Entity {
    float width;
    float height;
public:
    Rectangle(float w = 0.1f, float h = 0.1f);

    ~Rectangle();
};

class Circle : public Entity {
    float radius;
public:
    Circle(float r = 0.01f);

    ~Circle();
};
