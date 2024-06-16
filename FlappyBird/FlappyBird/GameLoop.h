#ifndef GAMELOOP_H
#define GAMELOOP_H

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"
#include <vector>
#include "Pipe.h"
using namespace std;

class GameLoop
{
private:
	const int HEIGHT = 640;
	const int WIDTH = 800;
	vector<Pipe*> pipes;
	int lastPipeTime;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event1;

	bool GameState;
	int score;

	float birdVelocity;
	float gravity;

	SDL_Texture *player;
	SDL_Rect srcPlayer, destPlayer;
	SDL_Texture* background;

	SDL_Texture* gameOverTexture;
	SDL_Rect gameOverRect;
	bool isGameOver;

public:
	GameLoop();
	~GameLoop();
	bool getGameState();
	void Update();
	void Initialize();
	void Event();
	void Render();
	void Clear();
	void ResetGame();
};

#endif 