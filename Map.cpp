#include <fstream>
#include "Map.hpp"
#include "ECS/Components.hpp"

extern Manager manager;

Map::Map(const char *mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts) {
    scaledSize = ms * ts;  
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
            // get a character and store it in tile
            mapFile.get(tile);
            // convert the character to an integer and multiply by 32
            srcY = atoi(&tile) * tileSize;
            // get a character and store it in tile
            mapFile.get(tile);
            // convert the character to an integer and multiply by 32
            srcX = atoi(&tile) * tileSize;
            AddTile(srcX, srcY, x * (tileSize * mapScale), y * (tileSize * mapScale)); // add the tile to the game
            mapFile.ignore(); // ignore the comma
        }
    }

    // ignore the blank line
    mapFile.ignore();

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            // character 1 is a collider
            if (tile == '1') {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int x, int y) {
    // tile is not a copy of the returned entity but is directly referring to 
    // the same entity returned by the addEntity() function
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, x, y, tileSize, mapScale, mapFilePath);
    // add tile to a group
    tile.addGroup(Game::groupMap);
}
