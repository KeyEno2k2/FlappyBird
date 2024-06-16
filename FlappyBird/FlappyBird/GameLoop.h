#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <iostream>
#include <SDL.h>
#include <vector>
#include "Pipe.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

class GameLoop
{
public:
    GameLoop();
    ~GameLoop();

    bool getGameState();
    void Initialize();
    void Event();
    void Update();
    void Render();
    void Clear();
    void ResetGame();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event1;
    bool GameState;
    SDL_Texture* player;
    SDL_Rect srcPlayer, destPlayer;
    float birdVelocity;
    float gravity;
    std::vector<Pipe*> pipes;
    Uint32 lastPipeTime;
    bool isGameOver;
    SDL_Texture* background;
    SDL_Texture* gameOverTexture;
    SDL_Rect gameOverRect;
    SDL_Texture* numberTextures[10];
    SDL_Rect numberRects[10];
    int score; 
    SDL_Texture* birdTextures[3]; // Tekstury ptaka
    int currentFrame; // Aktualna ramka animacji
    Uint32 lastFrameTime; // Czas ostatniej zmiany ramki
    void LoadNumberTextures();
    void RenderScore();
    void LoadBirdTextures();
    void UpdateBirdAnimation();
};

#endif
