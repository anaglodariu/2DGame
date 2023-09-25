#ifndef KEYBOARDCONTROLLER_HPP
#define KEYBOARDCONTROLLER_HPP

#include "../Game.hpp"
#include "Components.hpp"

class KeyboardController : public Component
{
public:
    PositionComponent* transform;
    SpriteComponent* sprite;

    void init() override {
        transform = &entity->getComponent<PositionComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w: // go up
                transform->velocity.y = -1;
                sprite->play("Walk");
                break;
            case SDLK_a: // go left
                transform->velocity.x = -1;
                sprite->play("Walk");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_s: // go down
                transform->velocity.y = 1;
                sprite->play("Walk");
                break;
            case SDLK_d: // go right
                transform->velocity.x = 1;
                sprite->play("Walk");
                break;
            default:
                break;
            }
            
        }

        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                sprite->play("Idle");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                sprite->play("Idle");
                sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                sprite->play("Idle");
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                sprite->play("Idle");
                break;
            default:
                break;
            }
        }
    }



};

#endif /* KEYBOARDCONTROLLER_HPP */