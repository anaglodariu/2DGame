#ifndef MAP_HPP
#define MAP_HPP

#include "Game.hpp"

using namespace std;

class Map {
public:
    Map(const char *mapFilePath, int mapScale, int tileSize); 
    ~Map();

    void AddTile(int srcX, int srcY, int x, int y); // add a tile to the game
    void LoadMap(string path, int sizeX, int sizeY);

private:
    const char *mapFilePath;
    int mapScale;
    int tileSize;
    int scaledSize;
};

#endif /* Map_hpp */