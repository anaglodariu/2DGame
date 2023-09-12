#ifndef KEYBOARDCONTROLLER_HPP
#define KEYBOARDCONTROLLER_HPP

#include "../Game.hpp"
#include "Components.hpp"

class KeyboardController : public Component
{
public:
    PositionComponent* transform;

    void init() override {
        transform = &entity->getComponent<PositionComponent>();
    }

    void update() override {
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w: // go up
                transform->velocity.y = -1;
                break;
            case SDLK_a: // go left
                transform->velocity.x = -1;
                break;
            case SDLK_s: // go down
                transform->velocity.y = 1;
                break;
            case SDLK_d: // go right
                transform->velocity.x = 1;
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
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                break;
            default:
                break;
            }
        }
    }



};

#endif /* KEYBOARDCONTROLLER_HPP */