#ifndef POSITIONCOMPONENT_HPP
#define POSITIONCOMPONENT_HPP
#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"

// everything in a struct is public by default
// evrything in a class is private by default
// so PositionComponent could be made in a struct
class PositionComponent : public Component 
{
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 3;

    PositionComponent() {
        position.zero();
    }

    PositionComponent(int sc) {
        // position.zero();
        // put the player in the middle of the screen
        position.x = 400;
        position.y = 320;
        scale = sc;
    }


    PositionComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    PositionComponent(float x, float y, int w, int h, int sc) {
        position.x = x;
        position.y = y;
        width = w;
        height = h;
        scale = sc;
    }

    void init() override {

        // at the beginning the velocity is 0
        velocity.zero();
    }

    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};

#endif /* PositionComponent_hpp */