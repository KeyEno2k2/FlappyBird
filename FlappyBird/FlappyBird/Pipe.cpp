#include "Pipe.h"
#include "TextureManager.h"

Pipe::Pipe(SDL_Renderer* renderer, int x, int y) : renderer(renderer) {
    texture = TextureManager::Texture("Image/pipe-greenv2.png", renderer);

    topRect.w = bottomRect.w = 52; // Szerokość rury
    topRect.h = bottomRect.h = 751; // Wysokość rury

    topRect.x = bottomRect.x = x;
    topRect.y = y - topRect.h;
    bottomRect.y = y + 150; // Przestrzeń między rurami
}

Pipe::~Pipe() {
    SDL_DestroyTexture(texture);
}

void Pipe::Update() {
    topRect.x -= 2;
    bottomRect.x -= 2;
}

void Pipe::Render() {
    SDL_RenderCopyEx(renderer, texture, NULL, &topRect, 180, NULL, SDL_FLIP_NONE);
    SDL_RenderCopy(renderer, texture, NULL, &bottomRect);
}

SDL_Rect& Pipe::GetTopRect() {
    return topRect;
}

SDL_Rect& Pipe::GetBottomRect() {
    return bottomRect;
}

int Pipe::GetX() const
{
    return topRect.x;
}

int Pipe::GetWidth() const{
    return topRect.w;
}