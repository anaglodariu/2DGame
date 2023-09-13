#ifndef TILECOMPONENT_HPP
#define TILECOMPONENT_HPP

#include "Components.hpp"
#include "SDL2/SDL.h"

class TileComponent : public Component
{
public:
    PositionComponent* transform;
    SpriteComponent* sprite;

    SDL_Rect tileRect;
    int tileID;
    char *path; // for the texture loader

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id) {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        // depending on the id we load a different texture
        switch (tileID)
        {
        case 0:
            path = "assets/dirt.png";
            break;
        case 1:
            path = "assets/grass.png";
            break;
        case 2:
            path = "assets/water.png";
            break;
        default:
            break;
        }
    }

    void init() override {
        entity->addComponent<PositionComponent>(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), tileRect.w, tileRect.h, 1);
        transform = &entity->getComponent<PositionComponent>(); // reference to the position component

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>(); // reference to the sprite component
    }

};

#endif /* TileComponent_hpp */