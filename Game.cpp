#include "Game.hpp"
#include "TextureManager.hpp"
// #include "GameObject.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"

// GameObject* player;
Map* map;


SDL_Renderer* Game::renderer = nullptr;
Manager manager;
// create a reference to the new player entity
auto& newPlayer(manager.addEntity());

Game::Game() 
{

}

Game::~Game() 
{

}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsystems initialized!..." << endl;
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (window) {
            cout << "Window created!" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created!" << endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    // player = new GameObject("assets/gorge.png", 0, 0);
    map = new Map();


    newPlayer.addComponent<PositionComponent>(100,500);
    newPlayer.addComponent<SpriteComponent>("assets/gorge.png");
    //newPlayer.getComponent<PositionComponent>().setPos(500, 200);

}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }

}

void Game::update()
{
    // player->update();
    manager.refresh();
    manager.update();
    

    cout << newPlayer.getComponent<PositionComponent>().getXpos() 
    << ", " << newPlayer.getComponent<PositionComponent>().getYpos() << endl;

}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    // this is where we would add stuff to render
    // player->render(); // place our dear Gorge on the screen
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game cleaned!" << endl;
}

bool Game::running()
{
    return isRunning;
}

// Path: Game.cpp