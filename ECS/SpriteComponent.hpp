#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP
#include "Components.hpp"
#include "../TextureManager.hpp"
#include "SDL2/SDL.h"
#include "Animation.hpp"
#include <map>


// class for drawing to the screen
class SpriteComponent : public Component 
{
private:
    // reference to the position
    PositionComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    // delay between sprite frames in ms
    int speed = 100; // in ms

public:
    int animIndex = 0; // the rows of the sprite sheet

    // it maps a string(name) to an animation
    std::map<const char*, Animation> animations; // holds our animations

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    // path to the texture that we use
    SpriteComponent(const char* path) {
        // load the texture
        setTexture(path);
    }

    // when this constructor is called we'll know that we want an animated sprite
    SpriteComponent(const char* path, bool isAnimated) {
        animated = isAnimated;

        Animation idle = Animation(0, 3, 100);
        Animation walk = Animation(1, 8, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);

        // frames = nFrames;
        // speed = mSpeed;

        play("Idle");

        setTexture(path);
    }

    // destructor
    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    // if we want to change the texture
    void setTexture(const char* path) {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {
        // initialize our rectangles
        // we get the position component by getting the reference to the entity 
        // and then getting the component
        transform = &entity->getComponent<PositionComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
        // destRect.w = destRect.h = 2 * srcRect.w;
    }

    void update() override {
        if (animated == true) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            // this way we'll get one of the 4 frames  
        }

        srcRect.y = animIndex * transform->height;

        // update the position of the sprite
        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;

    }

    void draw() override {
        // draw the sprite
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    // set the structure variables for a specific animation
    void play(const char* animName) {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};

#endif /* SpriteComponent_hpp */