#pragma once
#include <SDL.h>
#include <iostream>
#include "Object.h"
#include <SDL_image.h>

class Player:public Object 
{
private:
public:
    void Render(SDL_Renderer* ren, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest);
};