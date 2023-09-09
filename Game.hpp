#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;


class Game {

public:
    Game(); // constructor
    ~Game(); // destructor

    void init(const char* title, int x, int y, int width, int height, bool fullscreen); // initialize game window
    
    void handleEvents(); // handle game events
    void update(); // update game window
    void render(); // render game window
    void clean(); // clean game window

    bool running(); // check if game is running

    static SDL_Renderer* renderer;


private:
    int cnt = 0;
    bool isRunning;
    SDL_Window* window;
};

#endif /* Game_hpp */