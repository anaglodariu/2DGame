#include "Game.hpp"
#include "TextureManager.hpp"
// #include "GameObject.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

// GameObject* player;
Map* map;

SDL_Renderer* Game::renderer = nullptr;
Manager manager;
// create a reference to the new player entity
auto& newPlayer(manager.addEntity());
auto& youShallNotPassWall(manager.addEntity());

// auto& tile0(manager.addEntity());
// auto& tile1(manager.addEntity());
// auto& tile2(manager.addEntity());

SDL_Event Game::event; // one instance of the event by making it static
vector<ColliderComponent*> Game::colliders;

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

    // tile0.addComponent<TileComponent>(200, 200, 32, 32, 0); //dirt
    // tile1.addComponent<TileComponent>(250, 250, 32, 32, 1); //grass
    // tile2.addComponent<TileComponent>(200, 250, 32, 32, 2); //water

    // tile0.addComponent<ColliderComponent>("dirt");
    // tile1.addComponent<ColliderComponent>("grass");
    Map::LoadMap("assets/tiles16x16.map", 16, 16);


    // introduce our main player
    newPlayer.addComponent<PositionComponent>(2);
    newPlayer.addComponent<SpriteComponent>("assets/gorge.png");
    newPlayer.addComponent<KeyboardController>();
    //newPlayer.getComponent<PositionComponent>().setPos(500, 200);
    newPlayer.addComponent<ColliderComponent>("player");

    // introduce our wall to the player
    youShallNotPassWall.addComponent<PositionComponent>(300.0f, 300.0f, 20, 300, 1);
    youShallNotPassWall.addComponent<SpriteComponent>("assets/dirt.png");
    youShallNotPassWall.addComponent<ColliderComponent>("wall");

}


void Game::handleEvents()
{
    
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

    // loop through all colliders
    for (auto cc : colliders) {
        Collision::AABB(newPlayer.getComponent<ColliderComponent>(), *cc);
    }

    if (Collision::AABB(newPlayer.getComponent<ColliderComponent>().collider, youShallNotPassWall.getComponent<ColliderComponent>().collider)) {
        newPlayer.getComponent<PositionComponent>().velocity * -1;
        cout << "You shall not pass!" << endl;
    }
    
    //ewPlayer.getComponent<PositionComponent>().position.add(Vector2D(0,5));
    cout << newPlayer.getComponent<PositionComponent>().position.x << ", " << newPlayer.getComponent<PositionComponent>().position.y << endl;
   
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // map->DrawMap();
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


void Game::addTile(int id, int x, int y) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
}

// Path: Game.cpp