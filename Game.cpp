#include "Game.hpp"
#include "TextureManager.hpp"
// #include "GameObject.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

using namespace std;

// GameObject* player;
Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event; // one instance of the event by making it static
vector<ColliderComponent*> Game::colliders;

SDL_Rect Game::camera = {0, 0, 800, 640};

bool Game::isRunning = false;

// create a reference to the new player entity
auto& newPlayer(manager.addEntity());
// auto& youShallNotPassWall(manager.addEntity());

// where the map file is located
const char *mapFile = "assets/terrain_ss.png";


// clearly defining our groups with labels
enum groupLabels : size_t {
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

// a reference to all the tiles in the specified group
auto& tiles(manager.getGroup(groupMap));
// a reference to all the players in the specified group
auto& players(manager.getGroup(groupPlayers));
// a reference to all the enemies in the specified group
auto& enemies(manager.getGroup(groupEnemies));

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

    Map::LoadMap("assets/map.map", 25, 20);


    // introduce our main player
    newPlayer.addComponent<PositionComponent>(4);
    newPlayer.addComponent<SpriteComponent>("assets/player_anims.png", true);
    newPlayer.addComponent<KeyboardController>();
    //newPlayer.getComponent<PositionComponent>().setPos(500, 200);
    newPlayer.addComponent<ColliderComponent>("player");
    // add entity to a group
    newPlayer.addGroup(groupPlayers);

    // // introduce our wall to the player
    // youShallNotPassWall.addComponent<PositionComponent>(300.0f, 300.0f, 20, 300, 1);
    // youShallNotPassWall.addComponent<SpriteComponent>("assets/dirt.png");
    // youShallNotPassWall.addComponent<ColliderComponent>("wall");
    // // add entity to a group
    // youShallNotPassWall.addGroup(groupMap);

}

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
    // player->update();
    manager.refresh();
    manager.update();

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
    
    for (auto& p : players) 
        p->draw();
    
    for (auto& e : enemies) 
        e->draw();

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


void Game::addTile(int srcX, int srcY, int x, int y) {
    // tile is not a copy of the returned entity but is directly referring to 
    // the same entity returned by the addEntity() function
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, x, y, mapFile);
    // add tile to a group
    tile.addGroup(groupMap);
}

// Path: Game.cpp