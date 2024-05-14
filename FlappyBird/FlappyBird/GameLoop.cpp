#include "GameLoop.h"

GameLoop::GameLoop()
{
	window = NULL;
	renderer = NULL;

}

void GameLoop::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	if (window)
	{
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			cout << "Sukces!" << endl;
		}
		else {
			cout << "Nie udalo sie! :(" << endl;
		}
	}
	else {
		cout << "Window not Created!" << endl;
	}
}

void GameLoop::Render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

}

void GameLoop::Clear()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}