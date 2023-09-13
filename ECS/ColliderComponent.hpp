#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include <string>
#include "SDL2/SDL.h"
#include "Components.hpp"

using namespace std;

class ColliderComponent : public Component
{
public:
    // represent an area that is collidable
    SDL_Rect collider;
    string tag; // what tag to attach to the collider

    PositionComponent* transform;

    ColliderComponent(string t) {
        tag = t;
    }

    void init() override {
        // we make sure we have a position component
        if (!entity->hasComponent<PositionComponent>()) {
            entity->addComponent<PositionComponent>();
        }
        transform = &entity->getComponent<PositionComponent>();
        Game::colliders.push_back(this);
    }

    void update() override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }



};

#endif /* ColliderComponent_hpp */