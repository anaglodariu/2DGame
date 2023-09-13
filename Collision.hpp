#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "SDL2/SDL.h"

class ColliderComponent; // forward declaration to avoid circular dependency

class Collision
{

public:
    // a AABB collision method that takes in two SDL_Rects and returns a boolean
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    // a AABB collision method that takes in two ColliderComponents and returns a boolean
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

};




#endif /* Collision_hpp */