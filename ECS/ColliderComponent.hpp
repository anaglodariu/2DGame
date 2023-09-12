#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include <string>
#include "SDL2/SDL.h"
#include "Components.hpp"

using namespace std;

class ColliderComponent : public Component
{
    // represent an area that is collidable
    SDL_Rect collider;
    string tag; // what tag to attach to the collider

    PositionComponent* transform;

    void init() override {

    }

};

#endif /* ColliderComponent_hpp */