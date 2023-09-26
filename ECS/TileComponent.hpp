#ifndef TILECOMPONENT_HPP
#define TILECOMPONENT_HPP

#include "Components.hpp"
#include "SDL2/SDL.h"

class TileComponent : public Component
{
public:
    
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;

    TileComponent() = default;

    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int srcX, int srcY, int x, int y, const char *path) {
        texture = TextureManager::LoadTexture(path);

        // initial position of our tile, not where they are being rendered
        position.x = x;
        position.y = y;

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = 32;

        destRect.x = x;
        destRect.y = y;
        destRect.w = destRect.h = 64;
    }

    void update() override {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};

#endif /* TileComponent_hpp */