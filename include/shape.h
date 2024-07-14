#pragma once

#include "entity.h"

class Rectangle : public Entity {
    float width;
    float height;
public:
    Rectangle(float w = 0.1, float h = 0.1);

    ~Rectangle();
};

class Circle : public Entity {
    float radius;
public:
    Circle(float r = 0.01);

    ~Circle();
};
