#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

class Object
{
private:
    SDL_Rect src, dest;
    SDL_Texture* Tex;

public:
    Object();
    void setSource(int x, int y, int w, int h);
    void setDest(int x, int y, int w, int h);
    SDL_Texture* getTexture();
    SDL_Rect& getSrc();
    SDL_Rect& getDest();
    void CreateTexture(const char* address, SDL_Renderer* ren, SDL_Texture* Tex);
    void virtual Render(SDL_Renderer* ren, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest) = 0;

};