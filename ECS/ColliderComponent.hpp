#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include <string>
#include "SDL2/SDL.h"
#include "Components.hpp"
#include "../TextureManager.hpp"

using namespace std;

class ColliderComponent : public Component
{
public:
    // represent an area that is collidable
    SDL_Rect collider;
    string tag; // what tag to attach to the collider

    // texture for the collider so we can see it on the map
    SDL_Texture *tex;
    SDL_Rect srcR, destR;

    PositionComponent* transform;

    ColliderComponent(string t) {
        tag = t;
    }

    ColliderComponent(string t, int xpos, int ypos, int size) {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.w = collider.h = size;
    }

    void init() override {
        // we make sure we have a position component
        if (!entity->hasComponent<PositionComponent>()) {
            entity->addComponent<PositionComponent>();
        }
        transform = &entity->getComponent<PositionComponent>();

        tex = TextureManager::LoadTexture("assets/coltex.png");
        srcR = {0, 0, 32, 32};
        destR = {collider.x, collider.y, collider.w, collider.h};
    }

    void update() override {
        // only if the tag is not terrain
        if (tag != "terrain") {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }

        // update the collider's position when the camera moves
        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};

#endif /* ColliderComponent_hpp */