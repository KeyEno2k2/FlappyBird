#ifndef PIPE_H
#define PIPE_H

#include <SDL.h>

class Pipe {
public:
    Pipe(SDL_Renderer* renderer, int x, int y);
    ~Pipe();

    void Update();
    void Render();
    SDL_Rect& GetTopRect();
    SDL_Rect& GetBottomRect();

    int GetX() const;
    int GetWidth() const;

private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect topRect;
    SDL_Rect bottomRect;
};

#endif
