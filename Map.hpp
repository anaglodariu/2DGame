#ifndef MAP_HPP
#define MAP_HPP

#include "Game.hpp"

class Map {
public:
    Map();
    ~Map();

    void LoadMap(int arr[20][25]);
    void DrawMap();


private:
    SDL_Rect src, dest;

    SDL_Texture* stinkyDirt;
    SDL_Texture* prettyGrass;
    SDL_Texture* clearWater;

    int map[20][25];


};

#endif /* Map_hpp */