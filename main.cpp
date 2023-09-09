#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS; // 16ms
    
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        // this will delay our frames to be at 60 fps
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}