#include "TextureManager.h"
#include <SDL_image.h>

SDL_Texture* TextureManager::Texture(const char* filelocation, SDL_Renderer* ren)
{
    SDL_Surface* surface = IMG_Load(filelocation);
    if (!surface) {
        cout << "IMG_Load Error: " << IMG_GetError() << endl;
        return nullptr;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    if (!tex) {
        cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    }
    return tex;
}
