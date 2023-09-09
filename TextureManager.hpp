#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "Game.hpp"

using namespace std;

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);

};

#endif /* TextureManager_hpp */