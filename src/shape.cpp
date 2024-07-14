#include "shape.h"
#include <iostream>

Rectangle::Rectangle(float w, float h) {
    width = w;
    height = h;
}

Rectangle::~Rectangle() {
    std::cout << "Rectangle destroyed\n";
}

Circle::Circle(float r) {
    radius = r;
    std::cout << "Circle has been made\n";
}

Circle::~Circle() {
    std::cout << "Circle Destroyed\n";
}
