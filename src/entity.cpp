// This is for the definitions of all the functions under the class entity
#include <entity.h>
#include <iostream>

void entity::showpos() {
    std::cout << "[x : " << x << ", y : " << y << "]" << std::endl;
}

void entity::showvel() {
    std::cout << "[x_vel : " << x_vel << ", y : " << y << "]" << std::endl;
}

void entity::xvincr(float acc) { // Just increments the value of velocity
    x_vel += acc;
}

void entity::yvincr(float acc) {
    y_vel += acc;
}

void entity::xinc() {
    x += x_vel;
}

void entity::yinc() {
    y += y_vel;
}

uint8_t entity::getRed() {
    return r;
}

uint8_t entity::getGreen() {
    return g;
}

uint8_t entity::getBlue() {
    return b;
}

void chkcol() { // This is the MOST IMPORTANT FUNCTION IN THE BUNCH. It is to check collisions
}


// TODO : Try to implement all of Newton's laws of motions. If, differential formula haru (or maybe series wala thyo, maile ni accedentally dekheko thye, ajja lamo wala xa) use garna sakney ho vaney ni dherai ramro hunxa hai. 

// TODO : Try to figure out the idea of velocity. Yes, each entity will have its own velocity but I feel like this will give some issues soon.

// TODO : Complete this portion and clean up the code. Ajjai milaunai baki xa. At some point more functions may be added. Since I NEED to use these, I have tried to code atleast a portion of it but I will probably not work on it too much. IDK
