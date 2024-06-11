#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"
using namespace std;

class GameLoop
{
private:
	const int HEIGHT = 640;
	const int WIDTH = 800;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event1;

	bool GameState;

	SDL_Texture *player;
	SDL_Rect srcPlayer, destPlayer;
	SDL_Texture* background;

public:
	GameLoop();
	bool getGameState();
	void Update();
	void Initialize();
	void Event();
	void Render();
	void Clear();
};