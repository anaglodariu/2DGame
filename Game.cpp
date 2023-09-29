#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

using namespace std;

// GameObject* player;
Map *maap;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event; // one instance of the event by making it static
// vector<ColliderComponent*> Game::colliders;

SDL_Rect Game::camera = {0, 0, 800, 640};

bool Game::isRunning = false;

// create a reference to the new player entity
auto& newPlayer(manager.addEntity());
// auto& youShallNotPassWall(manager.addEntity());

// where the map file is located
// const char *mapFile = "assets/terrain_ss.png";


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

    maap = new Map("assets/terrain_ss.png", 2, 32);
    maap->LoadMap("assets/map.map", 25, 20);

    // introduce our main player
    newPlayer.addComponent<PositionComponent>(4);
    newPlayer.addComponent<SpriteComponent>("assets/player_anims.png", true);
    newPlayer.addComponent<KeyboardController>();
    //newPlayer.getComponent<PositionComponent>().setPos(500, 200);
    newPlayer.addComponent<ColliderComponent>("player");
    // add entity to a group
    newPlayer.addGroup(groupPlayers);
}

// a reference to all the tiles in the specified group
auto& tiles(manager.getGroup(Game::groupMap));
// a reference to all the players in the specified group
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    SDL_Rect playerCol = newPlayer.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = newPlayer.getComponent<PositionComponent>().position;

    manager.refresh();
    manager.update();

    for (auto& c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol)) {
            // we force the player to the last position he was in
            newPlayer.getComponent<PositionComponent>().position = playerPos;
        }
    }

    camera.x = newPlayer.getComponent<PositionComponent>().position.x - 400;
    camera.y = newPlayer.getComponent<PositionComponent>().position.y - 320;

    // check the bounds of our camera
    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w)
        camera.x = camera.w;
    if (camera.y > camera.h)
        camera.y = camera.h;

    // Vector2D playerVel = newPlayer.getComponent<PositionComponent>().velocity;
    // // how fast we should shift the background
    // int playerSpeed = newPlayer.getComponent<PositionComponent>().speed;

    // for (auto t : tiles) {
    //     t->getComponent<TileComponent>().destRect.x += -(playerVel.x * playerSpeed);
    //     t->getComponent<TileComponent>().destRect.y += -(playerVel.y * playerSpeed);
    // }

    // loop through all colliders
    // for (auto cc : colliders) {
    //     Collision::AABB(newPlayer.getComponent<ColliderComponent>(), *cc);
    // }

    // if (Collision::AABB(newPlayer.getComponent<ColliderComponent>().collider, youShallNotPassWall.getComponent<ColliderComponent>().collider)) {
    //     newPlayer.getComponent<PositionComponent>().velocity * -1;
    //     cout << "You shall not pass!" << endl;
    // }
    
    //ewPlayer.getComponent<PositionComponent>().position.add(Vector2D(0,5));
    cout << newPlayer.getComponent<PositionComponent>().position.x << ", " << newPlayer.getComponent<PositionComponent>().position.y << endl;
   
}


void Game::render() {
    SDL_RenderClear(renderer);
    // map->DrawMap();
    // this is where we would add stuff to render
    // player->render(); // place our dear Gorge on the screen
    // manager.draw();

    // we will render all the entities in the order we want
    for (auto& t : tiles)
        t->draw();
    
    for (auto& c : colliders)
        c->draw();
    
    for (auto& p : players) 
        p->draw();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game cleaned!" << endl;
}

bool Game::running() {
    return isRunning;
}

// Path: Game.cpp