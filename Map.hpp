#ifndef MAP_HPP
#define MAP_HPP

#include "Game.hpp"

using namespace std;

class Map {
public:
    Map();
    ~Map();

    void LoadMap(string path, int sizeX, int sizeY);

private:

};

#endif /* Map_hpp */