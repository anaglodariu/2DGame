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

    int speed = 3;

    PositionComponent() {
        position.x = 0.0f;
        position.y = 0.0f;
    }


    PositionComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void init() override {

        // at the beginning the velocity is 0
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};

#endif /* PositionComponent_hpp */