#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "SDL2/SDL.h"

class Collision
{

public:
    // a AABB collision method that takes in two SDL_Rects and returns a boolean
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);

};




#endif /* Collision_hpp */