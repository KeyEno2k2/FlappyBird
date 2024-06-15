#include "Pipe.h"
#include "TextureManager.h"

Pipe::Pipe(SDL_Renderer* renderer, int x, int y) : renderer(renderer) {
    texture = TextureManager::Texture("Image/pipe-green.png", renderer);

    topRect.w = bottomRect.w = 52; // Szerokość rury
    topRect.h = bottomRect.h = 320; // Wysokość rury

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
    SDL_RenderCopy(renderer, texture, NULL, &topRect);
    SDL_RenderCopy(renderer, texture, NULL, &bottomRect);
}

SDL_Rect& Pipe::GetTopRect() {
    return topRect;
}

SDL_Rect& Pipe::GetBottomRect() {
    return bottomRect;
}
