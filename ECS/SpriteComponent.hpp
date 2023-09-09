#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP
#include "Components.hpp"
#include "SDL2/SDL.h"

// class for drawing to the screen
class SpriteComponent : public Component 
{
private:
    // reference to the position
    PositionComponent* position;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
public:
    SpriteComponent() = default;
    // path to the twxture that we use
    SpriteComponent(const char* path) {
        // load the texture
        setTexture(path);
    }

    // if we want to change the texture
    void setTexture(const char* path) {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {
        // initialize our rectangles
        // we get the position component by getting the reference to the entity 
        // and then getting the component
        position = &entity->getComponent<PositionComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = srcRect.h = 32;
        destRect.w = destRect.h = 2 * srcRect.w;


    }

    void update() override {
        // update the position of the sprite
        destRect.x = position->getXpos();
        destRect.y = position->getYpos();

    }

    void draw() override {
        // draw the sprite
        TextureManager::Draw(texture, srcRect, destRect);
    }
};

#endif /* SpriteComponent_hpp */