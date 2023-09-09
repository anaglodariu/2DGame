#ifndef POSITIONCOMPONENT_HPP
#define POSITIONCOMPONENT_HPP
#include "ECS.hpp"
#include "Components.hpp"

class PositionComponent : public Component 
{
private:
    int xpos;
    int ypos;

public:

    PositionComponent() = default;

    PositionComponent(int x, int y) {
        xpos = x;
        ypos = y;
    }

    // to get positions
    int getXpos() { return xpos; }
    int getYpos() { return ypos; }



    //override the virtual functions
    // void init() override {
    //     xpos = 0;
    //     ypos = 0;
    // }

    void update() override {
        xpos++;
        ypos++;
    }

    // to set positions
    void setPos(int x, int y) { xpos = x; ypos = y; }
};

#endif /* PositionComponent_hpp */