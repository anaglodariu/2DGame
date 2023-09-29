// #include "GameObject.hpp"
// #include "TextureManager.hpp"

// GameObject::GameObject(const char* texturesheet, int Initx, int Inity)
// {
//     objTexture = TextureManager::LoadTexture(texturesheet);

//     Xpos = Initx;
//     Ypos = Inity;
// }

// void GameObject::update()
// {
//     Xpos++;
//     Ypos++;

//     srcRect.h = 32;
//     srcRect.w = 32;
//     srcRect.x = 0;
//     srcRect.y = 0;

//     destRect.x = Xpos;
//     destRect.y = Ypos;
//     destRect.w = srcRect.w * 2;
//     destRect.h = srcRect.h * 2;
// }

// void GameObject::render()
// {
//     SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
// }