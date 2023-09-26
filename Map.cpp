#include "Map.hpp"
#include "Game.hpp"
#include <fstream>


Map::Map() {
    
}

Map::~Map() {
    
}

void Map::LoadMap(string path, int sizeX, int sizeY) {
    char tile; // read file character by character
    fstream mapFile; // object to store the file we load
    mapFile.open(path);

    int srcX, srcY;

    // make a tile for each single character
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            /* the source coordinates of the tiles used is a 2 digit number */
            mapFile.get(tile); // get the character and store it in tile
            srcY = atoi(&tile) * 32; // convert the character to an integer and multiply by 32
            mapFile.get(tile); // get the character and store it in tile
            srcX = atoi(&tile) * 32; // convert the character to an integer and multiply by 32
            Game::addTile(srcX, srcY, x * 64, y * 64); // add the tile to the game
            mapFile.ignore(); // ignore the comma
        }
    }

    mapFile.close();
}
