#pragma once // Header files need this. Navaye feri dui choti samma copy paste huna sakxa.

#include <cstdint> // for specific data types
#include "definitions.h" // for the definitions of screen-types and whatnot

class entity {
private:
    float x, y;
    float x_vel;
    float y_vel;
    // int t; // idea of time ; Let this not be implemented yet. I don't think this will work as I think it will.

    // Color values 
    uint8_t r;
    uint8_t g;
    uint8_t b;
public:
    entity() : x((float)SCREEN_WIDTH / 2), y((float)SCREEN_HEIGHT / 2), y_vel(1), x_vel(0), r(255), g(255), b(255) {}

    entity(float a, float b) : x(a), y(b), x_vel(0), y_vel(1), r(255), g(255), b(255) {}

    void showpos(); // To print the position.
    void showvel(); // To print the current velocity. Here, the idea of acceleration will be introduced as well. Later maybe.
    void profile(float a, float x, float v, float r, float g, float b); // This will be to change the fundamental values at some point after initialization.
    void xvincr(float acc); // This entire thing is a test. This portion increments the value of velocity
    void yvincr(float acc);

    void xinc();
    void yinc();
    void chkcol(); // To check collisions hopefully.

    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getBlue();

    ~entity() {}

    // TODO : Try to "feed" the value of r, g and b externally. And also do something that helps extract that value. (Suraj le garda hunxa hai yo. Maile try garney vaney last tira garxu.)

    // TODO : Try to implement "idea of time". Each entity will have a different "time". Vannale, entity A could have time 2 while entity B could have time 3. This is done for consistency.
};
