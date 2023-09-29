#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class ColliderComponent; // forward declaration to avoid circular dependency

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
    static SDL_Event event;
    // static vector<ColliderComponent*> colliders;
    static bool isRunning;
    static SDL_Rect camera;

    // clearly defining our groups with labels
    enum groupLabels : size_t {
        groupMap,
        groupPlayers,
        groupColliders
    };

private:
    int cnt = 0;
    SDL_Window* window;
};

#endif /* Game_hpp */